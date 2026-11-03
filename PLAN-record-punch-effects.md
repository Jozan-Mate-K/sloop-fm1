# Record punch-in FX into the loop (+ a flush/clear effect)

## Context

SLOOP's punch-in FX ([punch.c](firmware/src/punch.c)) are a Pocket-Operator-style performance tool: hold **FX**, press a key, and the whole mix runs through that effect while the key is held. Today they are **purely live** — `punch.req` is set from a key press and consumed the same audio block; nothing is remembered.

The user wants to **record the punch FX they play into the loop** so the performance replays each time the loop comes around (overdub-style), plus a **new "flush" effect** that removes every recorded effect when played — exactly like the Pocket Operator's FX 16. The engine already enforces *one effect at a time, no stacking* (a single `punch.req`/`punch.cur`), so that constraint is free.

This is a genuinely new subsystem: a per-section **FX automation lane** keyed to loop position, written while recording and read back on playback by driving the existing `punch.req` seam — the same seam `midi_fx` already uses to steer FX programmatically.

## Design

**One effect per 1/16 cell, latched by filling cells.** A lane is an array of 1/16-note cells over the section loop. While recording, as the transport playhead crosses each cell, the effect the player is currently holding is written into that cell. On playback, each crossed cell drives `punch.req`. A held effect naturally fills the span of cells it covers; replaying those cells reproduces it. No separate on/off list, no run-time allocation — ISR-friendly integer indexing.

**Cell values (`uint8_t`):**
- `0..26` — a punch effect id (`PX_LOOP4`..`PX_FADE`) active at this cell.
- `FXA_EMPTY` (`0xFE`) — never written; on an overdub pass it is left untouched; on playback it means "no effect".
- `FXA_CLEAR` (`0xFF`) — the flush: "effects off here"; distinct from EMPTY so it **overwrites** prior recorded effects (erases) rather than leaving them.

**The flush/clear effect = FX held + REC (per the chosen trigger).** While FX and REC are both held it behaves like any other punch effect, except it means *no effect*: live, it drops the mix to dry; while recording, it writes `FXA_CLEAR` into each crossed cell. Hold it across the whole loop and it wipes every recorded effect ("removes every effect"); tap it to clear a point. It is implemented as a **gesture + lane sentinel, not a 28th keyboard tile** — this avoids touching the key↔fx tables, the keyboard-shaped tile grid, and `keys_lit`, all of which assume 27 keys (flagged as the breakage point during exploration).

**Loop basis (chosen): the whole section.** Lane length = `section_bars(live_sec) * 16` cells, capped at `FXA_MAX = 64` (4 bars). In loop mode `clk_beat` counts up monotonically within a section and only resets on a section change ([seq.c:2571](firmware/src/seq.c#L2571)), so the current cell is:
`cell = (clk_beat % loop_beats) * 4 + clk_pos / (BEAT_U/4)`, with `loop_beats = len/4`.

**Per section (A–D).** Each section is its own `project_t` in `proj_slot[4]` (resident in `.noinit` RAM, [project.c:154](firmware/src/project.c#L154)). A parallel `fx_auto[4][FXA_MAX]` lane array lives the same way; the live lane is `fx_auto[live_sec]`. This matches the section-length choice and lets each section carry its own FX automation.

**Precedence.** A live key the player is holding (`punch.keybit != 0`, or MIDI `mfx_key`) always wins over lane playback — the lane only writes `punch.req` when nothing live is held. This mirrors `midi_fx`'s existing "no keybit ⇒ a key release doesn't end it" convention.

**Scope note:** REV/ECHO *throws* and the knob-FX (DUST/DUCK) are separate from `punch.req` and are **not** recorded. FREEZE is `PX_FREEZE` (part of `punch.req`) and records like any effect.

## Implementation

### 1. Lane state + helpers — new section near the top of [punch.c](firmware/src/punch.c)
Add after the `punch` struct:
```c
#define FXA_MAX   64u          /* 1/16 cells, up to 4 bars */
#define FXA_EMPTY 0xFEu
#define FXA_CLEAR 0xFFu
static uint8_t fx_auto[4][FXA_MAX] __attribute__((section(".noinit")));  /* per section A..D */
static struct { volatile uint8_t clear; int32_t last_cell; uint8_t dirty; } fxa;
```
- `fxa.clear` — set by the UI while FX+REC held (read in the ISR).
- `fxa.last_cell` — the last cell the ISR acted on (−1 = none); reset on stop/section change.
- `fxa.dirty` per **section** (make it `uint8_t dirty[4]`): playback only runs for a section whose lane has content, so projects that never use the feature behave exactly as today.

Helpers (ISR context; `live_sec`, `section_bars`, `clk_beat`, `clk_pos`, `BEAT_U` all available):
- `fxa_len()` → `clamp(section_bars(live_sec)*16, 16, FXA_MAX)`.
- `fxa_cell()` → current cell per the formula above.
- `fxa_block()` → the record/playback step (below). Called once per block.

`fxa_block()` logic:
```
if (!song.playing || live_sec < 0) { fxa.last_cell = -1; return; }
cell = fxa_cell();
if (cell == fxa.last_cell) return;         /* still in the same cell */
fxa.last_cell = cell;
lane = fx_auto[live_sec];
/* RECORD (any track armed) */
if (song.rec) {
    if (fxa.clear)                 { lane[cell] = FXA_CLEAR; fxa.dirty[live_sec] = 1; }
    else if (punch.keybit || mfx_key) { lane[cell] = (uint8_t)punch.req; fxa.dirty[live_sec] = 1; }
    /* else: nothing held -> leave the cell (overdub-safe) */
}
/* PLAYBACK (lane drives FX unless a live key or the clear gesture is active) */
if (fxa.dirty[live_sec] && !punch.keybit && !mfx_key && !fxa.clear) {
    uint8_t v = lane[cell];
    punch.req = (v <= PX_FADE) ? (int8_t)v : -1;   /* EMPTY/CLEAR -> off */
}
```
Note `mfx_key` is `static` in [seq.c](firmware/src/seq.c#L2175); since `punch.c` is `#include`d into `fx.c` (not seq.c), expose the live-held state through a small accessor or a shared flag (e.g. have `midi_fx`/`key_down`/`key_up` maintain a `punch.live` bit alongside `keybit`) rather than referencing `mfx_key` directly across translation units. Simplest: add `volatile uint8_t live` to the `punch` struct, set it in the three `punch.req` writers in seq.c and clear it on release, and test `punch.live` in `fxa_block`.

### 2. Drive it from the transport — [events_block()](firmware/src/seq.c#L3310)
Call the FX-lane step once per block, after the clock advances ([seq.c:3603-3609](firmware/src/seq.c#L3603)). Since `fxa_block` lives in `punch.c` (compiled inside fx.c) and `events_block` is in seq.c, call it through the same path `punch_process` is reached, or add a tiny forward-declared hook `punch_auto_block()` that seq.c calls. Reset `fxa.last_cell = -1` in [seq_reset_tracks()](firmware/src/seq.c#L2556) (section change) and on STOP ([seq.c:3340](firmware/src/seq.c#L3340)) so the cell tracking restarts cleanly.

### 3. The flush gesture (FX + REC) — [holds_input()](firmware/src/ui_input.c#L1022)
At the top of the REC-press branch ([ui_input.c:1031](firmware/src/ui_input.c#L1031)), intercept when FX is held:
```c
if (pressed & rb) {
    if (fx_held()) {                 /* FX button down: this REC is the flush, not rec_toggle */
        /* engage clear while REC is down; don't arm/disarm recording */
        ... skip rec_toggle for this press ...
    } else { /* existing rec_toggle path */ }
}
```
Maintain `punch.clear` from the button state each UI frame right where `punch.hold` is set ([ui_input.c:899](firmware/src/ui_input.c#L899)):
`punch.clear = fx_held() && (fm1_in.buttons & (1u<<panel.btn[B_REC]))`. Use the real button state (`fm1_in.buttons`) rather than relying on event edges so hold/release is robust. While `punch.clear` is set, also have `fxa_block`/`punch_process` force the live mix dry (treat it as `punch.req = -1` for the live path). Ensure the 700 ms "hold REC = clear track" path and the song-page "REC stores a section" path are **not** triggered while FX is held (guard those branches with `!fx_held()`).

### 4. Reset on NEW / load / section wipe
- **NEW / clear project** ([project.c:624](firmware/src/project.c#L624), [:1098](firmware/src/project.c#L1098)): `memset(fx_auto[slot], FXA_EMPTY, FXA_MAX); fxa.dirty[slot] = 0;`.
- Initialize all lanes to `FXA_EMPTY` at boot (they're `.noinit`, so set them in the project/boot init path alongside `proj_slot`).

### 5. Persistence via the side-record — [project.c](firmware/src/project.c)
Reuse the exact settings pattern ([project.c:967-970](firmware/src/project.c#L967)): a side record rides in bytes 64..256 of each flash copy (`ST_SIDE_MAX = 192`, [storage.c:160](firmware/src/storage.c#L160)), invisible to older firmware. The 64-byte lane fits with room for a small `{magic, ver, len}` header.
- **Save a section** ([project_save](firmware/src/project.c#L586), and the dirty-section save at [:1153](firmware/src/project.c#L1153)): before `st_save(OBJ_PROJECT0+slot, ...)`, set `st_side = &fx_side[slot]; st_side_len = sizeof fx_side[slot];` then clear `st_side = 0` after (mirroring settings_write). Pack `fx_auto[slot]` + a magic into `fx_side`.
- **Autosave** ([:724](firmware/src/project.c#L724), [:1172](firmware/src/project.c#L1172)): same, for the live section’s lane.
- **Load** ([st_load paths :576](firmware/src/project.c#L576), [:739](firmware/src/project.c#L739), [:853](firmware/src/project.c#L853)): after loading a slot, `st_side_load(OBJ_PROJECT0+slot, &fx_side, …)`; if the magic validates, copy into `fx_auto[slot]` and set `dirty`, else `memset(FXA_EMPTY)` + `dirty=0`. A project saved by older firmware simply has no side record → empty lane (clean forward/backward compatibility, no format bump, no touching the 3840-byte `project_t` wall).

### 6. UI feedback (minimal, mostly free)
- During playback the lane writes `punch.req`, so the lit FX key already follows the automation via [keys_lit()](firmware/src/ui_input.c#L109) and the FX-layer tile highlight ([ui_layers.c:734](firmware/src/ui_layers.c#L734)) — no change needed.
- While `punch.clear` is engaged, briefly show `ui_say("FX", "FLUSH")` (or similar) so the flush is legible. Optional: dim/blank the lit key during flush.

### 7. Docs — [GUIDE.md](GUIDE.md)
Update the **Punch-in effects** section (and the §26 cheat sheet) to document: FX performance is recorded while REC is active and replays each loop (overdub); **FX + REC = flush** (removes recorded effects for as long as it's held); automation is per section and saved with the project.

## Files to modify
- [firmware/src/punch.c](firmware/src/punch.c) — lane state, helpers, `fxa_block`, `punch.live`/`punch.clear` fields, flush-dry in the live path.
- [firmware/src/seq.c](firmware/src/seq.c) — call the lane step in `events_block`; set `punch.live` in the three `punch.req` writers (`key_down` 2208, `key_up` 2331, `midi_fx` 2186); reset `fxa.last_cell` in `seq_reset_tracks`/stop.
- [firmware/src/ui_input.c](firmware/src/ui_input.c) — FX+REC flush interception in `holds_input`; maintain `punch.clear`; guard the REC-hold/song-page paths with `!fx_held()`.
- [firmware/src/project.c](firmware/src/project.c) — per-section lane init/reset; side-record save/load for projects and autosave.
- [GUIDE.md](GUIDE.md) — document the feature.
- [tests/punch_test.c](tests/punch_test.c) (extend) or a new `tests/fxa_test.c` registered in [tests/run_tests.sh](tests/run_tests.sh).

## Verification
1. **Unit test (host):** extend [tests/punch_test.c](tests/punch_test.c) or add `fxa_test.c` to cover: `fxa_cell()` math across tempos/bar-lengths and the loop wrap; a record→playback round-trip (write an effect across a span, confirm playback drives `punch.req` on those cells and `-1` elsewhere); overdub leaves untouched cells; flush writes `FXA_CLEAR` and erases a prior effect; live key takes precedence over the lane.
2. **Persistence test:** save a section with a recorded lane, reload via `st_side_load`, confirm the lane round-trips; confirm a project with no side record loads an empty lane (older-firmware compatibility).
3. **Build + full suite:** run `./tests/run_tests.sh` **without piping through `tail`** (piping masks the exit code and which stage failed — see memory). The editor protocol is fuzzed under ASan+UBSan; keep that green.
4. **Known-noise:** `tests/target_budget.py` can fail locally due to a toolchain mismatch against the committed baseline — that's not a real regression (see memory); confirm the flash/RAM budget is still sane but don't block on a local target_budget delta.
5. **On-device (via the `run` skill if desired):** record a few FX over a 2-bar loop, confirm they replay each pass; hold FX+REC across the loop and confirm it wipes them; save, power-cycle (or reload the project), confirm the automation persisted.
