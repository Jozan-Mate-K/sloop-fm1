/* SPDX-License-Identifier: GPL-3.0-only */
/* PUNCH-IN FX AUTOMATION in the flash (project.c st_save_fx, fx_side_read, autosave): a section's lane rides in the side
 * record of its object, the working one in the autosave's; both come back at a power-on, and at a warm reset (an
 * update: the sections still in RAM, their lanes not) without a section written again losing its lane; a section
 * saved without a lane (or by an older SLOOP) has none, and its payload is the project alone; a lane change alone is
 * autosaved. Real storage.c / project.c on the RAM image of the NOR (tests/editor_host.c). Exit status: failed checks. */
#include "editor_host.c"
static int fails;
static void check(int c, const char *what) { printf("fxa_persist: %-78s %s\n", what, c ? "ok" : "FAIL"); fails += !c; }

static void lane_fill(uint8_t *cells, uint8_t fx, uint32_t a, uint32_t b)
{
    uint32_t i;
    memset(cells, FXA_EMPTY, FXA_MAX);
    for (i = a; i < b; i++)
        cells[i] = fx;
}
static void record(uint8_t fx, uint32_t a, uint32_t b)    /* the working lane, as a take leaves it */
{
    lane_fill(fx_live, fx, a, b);
    fxa.on = 1;
    fxa.rev++;
}
static void lanes_lost(void)                              /* what a reset does to the lanes (not .noinit) */
{
    memset(fx_slot, 0, sizeof fx_slot);
    memset(fx_live, 0, sizeof fx_live);
    fxa.slot_on = 0;
    fxa.on = 0;
}
static void power_on(void)                                /* .noinit is garbage after a power-off */
{
    memset(proj_slot, 0, sizeof proj_slot);
    sec_dirty = 0;
    lanes_lost();
    persist_boot();
    autosave_resume();
}

int main(void)
{
    uint8_t want[FXA_MAX], want_live[FXA_MAX];
    harness_init();
    song.playing = 0;
    transport_req = 0;

    /* 1. a lane stored with section B, another in the working project: both back after a power-on */
    record(PX_REV, 4u, 12u);
    memcpy(want, fx_live, FXA_MAX);
    section_store(1);
    sections_write();
    record(PX_GATE, 0u, 3u);
    memcpy(want_live, fx_live, FXA_MAX);
    persist_flush_now();
    check(st_load(OBJ_PROJECT0 + 1, &proj_tmp, sizeof proj_tmp) == (int)sizeof(project_t),
          "a section with a lane: its payload is the project alone (older SLOOP reads it)");
    power_on();
    check(proj_ok(&proj_slot[1]) && (fxa.slot_on & 2u) && !memcmp(fx_slot[1], want, FXA_MAX),
          "power-on: section B's lane, as stored");
    check(fxa.on && !memcmp(fx_live, want_live, FXA_MAX), "power-on: the working lane, from the autosave");
    check(!(fxa.slot_on & ~2u), "power-on: the other sections have none");

    /* 2. a warm reset (an update): the sections stay in RAM, the lanes do not; B marked to be written again keeps its */
    lanes_lost();
    proj_slot[1].sel ^= 1u;                               /* (B in RAM differs from the flash: written when quiet) */
    proj_slot[1].sum = proj_sum(&proj_slot[1]);
    persist_boot();
    check((sec_dirty & 2u) && (fxa.slot_on & 2u) && !memcmp(fx_slot[1], want, FXA_MAX),
          "warm reset: section B's lane read again from the flash");
    sections_write();
    power_on();
    check((fxa.slot_on & 2u) && !memcmp(fx_slot[1], want, FXA_MAX), "warm reset, B written again: its lane still there");

    /* 3. SAVE to a slot takes the working lane; LOAD brings it back as the working one */
    record(PX_LPF, 16u, 20u);
    memcpy(want, fx_live, FXA_MAX);
    project_save(2);
    fxa.on = 0;
    project_load(1);
    transport_req = 0;                                    /* (the stop it asked for) */
    check(fxa.on && fx_live[5] == (uint8_t)PX_REV, "LOAD B: B's lane is the working one");
    power_on();
    project_load(2);
    transport_req = 0;
    check(fxa.on && !memcmp(fx_live, want, FXA_MAX), "SAVE C, power-on, LOAD C: the lane recorded before the save");

    /* 4. a section saved without a lane (as an older SLOOP writes it): none, even where one was */
    st_save(OBJ_PROJECT0 + 1, &proj_slot[1], sizeof proj_slot[1]);
    power_on();
    check(proj_ok(&proj_slot[1]) && !(fxa.slot_on & 2u), "a section written with no side record: no lane");
    project_erase(2);
    power_on();
    check(!(fxa.slot_on & 4u), "ERASE C: its lane goes too");

    /* 5. a lane change alone is autosaved */
    persist_flush_now();
    check(!autosave_changed(), "autosave: nothing changed after a save");
    record(PX_HPF, 1u, 2u);
    check(autosave_changed(), "autosave: an FX lane change alone is a change");
    memcpy(want_live, fx_live, FXA_MAX);
    persist_flush_now();
    power_on();
    check(fxa.on && !memcmp(fx_live, want_live, FXA_MAX), "autosave: the changed lane back after a power-on");

    {   /* 6. the buttons (ui_input.c holds_input): the flush is the FX button + REC, not the FX layer locked open */
        uint32_t rb = 1u << panel.btn[B_REC], t = 100000u;
        song.rec = 0;
        rec_wait = 0;
        punch.hold = 1;                                   /* the FX layer locked open, its button up */
        fm1_in.buttons = rb;
        holds_input(rb, t);
        check(!punch.clear && (song.rec || rec_wait), "FX locked open: REC arms recording, no flush");
        fm1_in.buttons = 0;
        holds_input(0, t += 50u);
        song.rec = 0;
        rec_wait = 0;
        fm1_in.buttons = rb | ly_bit[LY_FX];              /* the FX button held: REC is the flush */
        holds_input(rb, t += 50u);
        check(punch.clear && !song.rec && !rec_wait, "FX + REC: the flush, recording not armed");
        fm1_in.buttons = 0;
        holds_input(0, t += 50u);
        check(!punch.clear, "FX + REC let go: the flush ends");
        song.playing = 1;                                 /* recording, REC first (it ends the take), then FX */
        song.rec = 1;
        fm1_in.buttons = rb;
        holds_input(rb, t += 50u);
        fm1_in.buttons = rb | ly_bit[LY_FX];
        holds_input(0, t += 50u);
        check(punch.clear && song.rec, "REC then FX while recording: the take goes on, the flush records");
        fm1_in.buttons = 0;
        holds_input(0, t += 50u);
        song.playing = 0;
        song.rec = 0;
        punch.hold = 0;
    }

    printf("fxa_persist: %d failed\n", fails);
    return fails;
}
