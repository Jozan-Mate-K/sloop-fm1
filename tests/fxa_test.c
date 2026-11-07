/* SPDX-License-Identifier: GPL-3.0-only */
/* PUNCH-IN FX AUTOMATION (punch.c fx_live / fx_slot, seq.c punch_fx_auto): the FX you play while REC is on are written
 * into 1/16 cells of the loop and replayed each pass; FX + REC (the flush) writes "effects off" and keeps the mix dry;
 * an overdub pass leaves cells you do not play over; a live key always wins over the lane; a tap is recorded in its
 * nearest cell and a release early in a cell does not stretch the effect over it; STOP and a section without a lane
 * let go of a replayed effect; the lane goes with the loop (stored with a section, recalled with it, put aside by song
 * mode); its length follows the patterns. The flash side: tests/fxa_persist_test.c. */
#define FELUCCA_ARRANGER 1
#define main hostsim_main
#include "hostsim.c"
#undef main
#include <assert.h>
#define PROJ_HOST 1
static uint32_t trk_def_engine(uint32_t i) { return i < NPART ? i : 0; }
#include "../firmware/src/project.c"
static struct { uint8_t force; } ui;
static uint8_t sync_reload;
#include "../firmware/src/arranger_scene.c"

#define CU (BEAT_U / 4u)                          /* a cell, in clock units */

/* put the transport q quarters into 1/16 cell c (of the lane), then run one lane step */
static void at_q(uint32_t c, uint32_t q)
{
    clk_beat = c / 4u;
    clk_pos = (c % 4u) * CU + q * (CU / 4u);
    punch_fx_auto();
}
static void at_cell(uint32_t c) { at_q(c, 0u); }

static void loop_bars(uint32_t steps)             /* every track: `steps` 1/16 steps (16: one bar) */
{
    uint32_t k;
    for (k = 0; k < NTRK; k++) {
        trk[k].p[P_SLEN] = 16;
        trk[k].p[P_SDIV] = 2;                     /* 1/16 */
    }
    trk[0].p[P_SLEN] = (int16_t)steps;
}

static void reset_lane(void)
{
    song.playing = 1;
    song.g[G_BPM] = 120;
    song.rec = 0;
    punch.live = 0;
    punch.clear = 0;
    punch.req = -1;
    punch.keybit = 0;
    fxa.on = 0;
    fxa.slot_on = 0;
    fxa.drove = 0;
    fxa.gest = FXA_NONE;
    fxa.wcell = -1;
    fxa.last_cell = -1;
    loop_bars(16u);
    memset(fx_live, 0, sizeof fx_live);           /* (garbage: the first record must start an empty lane) */
}

static void hold(int fx) { punch.live = 1; punch.req = (int8_t)fx; }
static void let_go(void) { punch.live = 0; punch.req = -1; }

/* hold effect `fx` across cells [a, b) while recording, let go at the start of b */
static void record_span(int fx, uint32_t a, uint32_t b)
{
    uint32_t c;
    song.rec = 1;
    hold(fx);
    for (c = a; c < b; c++)
        at_cell(c);
    let_go();
    at_cell(b % 16u);
    song.rec = 0;
}

static void pass(void) { fxa.last_cell = -1; }   /* a fresh pass over the loop */

int main(void)
{
    uint32_t c;
    host_tracks_init();

    /* 0. the lane is as long as the loop's longest pattern (16 cells a bar), four bars at most */
    reset_lane();
    assert(fxa_len() == 16u);
    loop_bars(32u);
    assert(fxa_len() == 32u);
    loop_bars(24u);                               /* 1.5 bars: the pattern takes two */
    assert(fxa_len() == 32u);
    trk[1].p[P_SLEN] = 64; trk[1].p[P_SDIV] = 0;  /* 64 x 1/4: 16 bars, the lane repeats every four */
    assert(fxa_len() == FXA_MAX);
    reset_lane();

    /* 1. record a held effect over cells 4..7, then replay the whole bar */
    record_span(PX_REV, 4u, 8u);
    assert(fxa.on);
    for (c = 4u; c < 8u; c++)
        assert(fx_live[c] == (uint8_t)PX_REV);
    assert(fx_live[3] == FXA_EMPTY && fx_live[8] == FXA_EMPTY && fx_live[0] == FXA_EMPTY);
    pass();
    for (c = 0u; c < 16u; c++) {
        at_cell(c);
        assert(punch.req == (c >= 4u && c < 8u ? (int8_t)PX_REV : -1));
    }

    /* 2. the flush (FX + REC) erases a span and keeps the mix dry while held */
    reset_lane();
    record_span(PX_REV, 0u, 16u);                 /* a bar of REVERSE */
    pass();
    at_cell(0);
    assert(punch.req == (int8_t)PX_REV);
    song.rec = 1;
    punch.clear = 1;
    for (c = 4u; c < 12u; c++) {
        at_cell(c);
        assert(punch_want() == -1);               /* dry while the flush is held */
        assert(fx_live[c] == FXA_CLEAR);
    }
    punch.clear = 0;
    song.rec = 0;
    pass();                                       /* replay: the cleared cells are off, the rest still REVERSE */
    for (c = 0u; c < 16u; c++) {
        at_cell(c);
        assert(punch.req == (c >= 4u && c < 12u ? -1 : (int8_t)PX_REV));
    }

    /* 3. an overdub pass (nothing held) leaves recorded cells untouched */
    reset_lane();
    record_span(PX_GATE, 2u, 5u);
    song.rec = 1;
    pass();
    for (c = 0u; c < 16u; c++)
        at_cell(c);
    song.rec = 0;
    for (c = 2u; c < 5u; c++)
        assert(fx_live[c] == (uint8_t)PX_GATE);

    /* 4. a live key wins over the lane (the lane never overwrites a held effect) */
    reset_lane();
    record_span(PX_REV, 6u, 10u);
    hold(PX_LPF);
    pass();
    for (c = 0u; c < 16u; c++) {
        at_cell(c);
        assert(punch.req == (int8_t)PX_LPF);
    }
    let_go();
    at_q(7u, 2u);                                 /* let go mid-cell: the lane takes over at once */
    assert(punch.req == (int8_t)PX_REV);

    /* 5. a clean (never-recorded) lane drives nothing: behaves exactly as before the feature */
    reset_lane();
    pass();
    for (c = 0u; c < 16u; c++) {
        at_cell(c);
        assert(punch.req == -1);
    }

    /* 6. STOP lets go of an effect the lane was playing; a key held over the stop keeps its own */
    reset_lane();
    record_span(PX_STUT, 0u, 16u);
    pass();
    at_cell(3);
    assert(punch.req == (int8_t)PX_STUT);
    song.playing = 0;
    punch_fx_auto();
    assert(punch.req == -1);
    song.playing = 1;
    pass();
    at_cell(3);
    hold(PX_LPF);
    song.playing = 0;
    punch_fx_auto();
    assert(punch.req == (int8_t)PX_LPF);

    /* 7. the lane goes with the loop: stored with a section, a section without one lets go, recalled it plays again */
    reset_lane();
    record_span(PX_FLANGE, 0u, 16u);
    fxa_store(1);                                 /* (section_store / project_save) */
    assert(fxa.slot_on == 2u && fx_slot[1][5] == (uint8_t)PX_FLANGE);
    pass();
    at_cell(5);
    assert(punch.req == (int8_t)PX_FLANGE);
    fxa_recall(2);                                /* a jump to C: no lane */
    assert(!fxa.on && punch.req == -1 && fxa.last_cell == -1);
    for (c = 0u; c < 16u; c++) {
        at_cell(c);
        assert(punch.req == -1);
    }
    fxa_store(3);                                 /* storing C's (empty) loop as D: D has none */
    assert(fxa.slot_on == 2u);
    fxa_recall(1);                                /* back to B */
    at_cell(0);                                   /* (its cell 0 is entered again, whatever the step saw last) */
    assert(fxa.on && punch.req == (int8_t)PX_FLANGE);

    /* 8. song mode puts the working lane aside and brings it back at the end */
    reset_lane();
    record_span(PX_GATE, 8u, 12u);
    fxa_keep();
    fxa_recall(0);                                /* the song plays section A (no lane) */
    assert(!fxa.on);
    fxa_unkeep();
    assert(fxa.on && fx_live[9] == (uint8_t)PX_GATE && fx_live[7] == FXA_EMPTY);

    /* 9. a section change re-enters cell 0 (seq_reset_tracks), even if the step had acted on cell 0 last */
    reset_lane();
    record_span(PX_REV, 0u, 1u);
    pass();
    at_cell(0);
    punch.req = -1;                               /* (something else let go of it) */
    seq_reset_tracks(0);
    at_cell(0);
    assert(punch.req == (int8_t)PX_REV);

    /* 10. timing: a tap inside a cell is recorded in it; one in the second half of a cell, in the next; a release
     * early in a cell the effect filled on entering gives the cell back, a late one keeps it */
    reset_lane();
    song.rec = 1;
    at_q(5u, 0u);
    hold(PX_GATE);
    at_q(5u, 1u);                                 /* a tap from 1/4 to 1/2 of cell 5 */
    let_go();
    at_q(5u, 2u);
    assert(fx_live[5] == (uint8_t)PX_GATE && fx_live[4] == FXA_EMPTY && fx_live[6] == FXA_EMPTY);
    at_q(8u, 2u);
    hold(PX_HPF);
    at_q(8u, 3u);                                 /* pressed 3/4 into cell 8 */
    at_q(9u, 0u);
    let_go();
    at_q(9u, 1u);                                 /* let go 1/4 into cell 9 */
    assert(fx_live[8] == FXA_EMPTY && fx_live[9] == (uint8_t)PX_HPF && fx_live[10] == FXA_EMPTY);
    hold(PX_LPF);
    at_q(12u, 0u);
    at_q(13u, 0u);
    let_go();
    at_q(13u, 1u);                                /* held over 12, let go early in 13 */
    assert(fx_live[12] == (uint8_t)PX_LPF && fx_live[13] == FXA_EMPTY);
    hold(PX_LPF);
    at_q(14u, 0u);
    at_q(15u, 0u);
    let_go();
    at_q(15u, 3u);                                /* held over 14, let go late in 15 */
    assert(fx_live[14] == (uint8_t)PX_LPF && fx_live[15] == (uint8_t)PX_LPF);
    song.rec = 0;

    /* 11. the flush over a held key: dry and "off" recorded while it is held, the key's effect back after it */
    reset_lane();
    song.rec = 1;
    hold(PX_LPF);
    at_cell(1);
    punch.clear = 1;
    at_cell(2);
    at_cell(3);
    assert(punch_want() == -1 && punch.req == (int8_t)PX_LPF);
    assert(fx_live[1] == (uint8_t)PX_LPF && fx_live[2] == FXA_CLEAR && fx_live[3] == FXA_CLEAR);
    punch.clear = 0;
    at_q(3u, 1u);                                 /* the flush let go, the key still held */
    at_cell(4);
    assert(punch_want() == (int8_t)PX_LPF && fx_live[4] == (uint8_t)PX_LPF);
    song.rec = 0;

    printf("fxa_test: OK\n");
    return 0;
}
