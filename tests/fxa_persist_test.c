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
    memset(kmac_slot, 0, sizeof kmac_slot);              /* (the sections' KNOB MACROS: not .noinit either) */
}
static void power_on(void)                                /* .noinit is garbage after a power-off */
{
    memset(proj_slot, 0, sizeof proj_slot);
    sec_dirty = 0;
    lanes_lost();
    for (uint32_t t = 0; t < NTRK; t++)
        kmac_clear(t);                                    /* (the working macros: as at a boot) */
    persist_boot();
    autosave_resume();
}
/* KNOB MACROS (punch.c kmac_slot, project.c kmside_t): the working ones as set */
static int km_is(uint32_t t, uint32_t k, uint32_t s, uint32_t id, int32_t amt)
{
    return kmac_id[t][k * 2u + s] == id && kmac_amt[t][k * 2u + s] == amt;
}
static int km_none(void)
{
    uint32_t i;
    for (i = 0; i < sizeof kmac_id; i++)
        if ((&kmac_id[0][0])[i] != KMAC_OFF)
            return 0;
    return 1;
}
static int slot_none(uint32_t s)
{
    static const kmac_tab_t z;
    return !memcmp(&kmac_slot[s], &z, sizeof z);
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

    {   /* 7. KNOB MACROS go with the sections and the autosave as the lanes do (project.c kmside_t after the lane) */
        uint32_t te = KMAC_OFF, i;
        projside_t raw;
        for (i = P_E0; i < P_COUNT && te == KMAC_OFF; i++)
            if (kmac_ok(&trk[0], i))
                te = i;                                   /* an engine value (a code of its own: ML_E0 + k) */
        check(te != KMAC_OFF && kmac_ok(&trk[0], P_TFLT) && kmac_ok(&trk[TRK_DRUM], P_PAN), "macros: the targets used here");
        for (i = 0; i < NTRK; i++)
            kmac_clear(i);
        fxa.on = 0;
        kmac_set(0, 1, 0, te, 40);
        kmac_set(0, 1, 1, P_TFLT, -30);
        kmac_set(TRK_DRUM, 3, 0, P_PAN, -64);
        kmac_pos_set(0, 1, 90);
        section_store(3);                                 /* no lane, macros: the record with the lane's magic 0 */
        sections_write();
        check(st_load(OBJ_PROJECT0 + 3, &proj_tmp, sizeof proj_tmp) == (int)sizeof(project_t),
              "macros: a section with macros, its payload the project alone");
        check(side_get(OBJ_PROJECT0 + 3, &raw) == 2u && raw.fx.magic == 0u, "macros, no lane: the lane's magic 0, macros");
        for (i = 0; i < NTRK; i++)
            kmac_clear(i);
        power_on();
        check(!(fxa.slot_on & 8u) && !slot_none(3), "macros, power-on: section D has its macros, no lane");
        kmac_set(0, 1, 0, P_TFLT, 10);                    /* (the working ones, then the section loaded over them) */
        kmac_pos_set(0, 1, 77);
        section_load(3);
        transport_req = 0;
        check(km_is(0, 1, 0, te, 40) && km_is(0, 1, 1, P_TFLT, -30) && km_is(TRK_DRUM, 3, 0, P_PAN, -64) &&
              km_is(0, 0, 0, KMAC_OFF, 0), "macros: section D loaded, its macros (an engine value's code too)");
        check(kmac_pos[0][1] == 77u, "macros: a section loaded keeps the positions");
        check(kmac_on[0] && kmac_d[0][2] != 0, "macros: loaded, the deltas made (kmac_sync)");

        /* the autosave: the working macros and their positions */
        kmac_pos_set(0, 1, 101);
        persist_flush_now();
        check(!autosave_changed(), "macros: autosaved, nothing changed");
        kmac_pos_set(0, 1, 102);
        check(autosave_changed(), "macros: a position change alone is a change");
        kmac_pos_set(0, 1, 101);
        persist_flush_now();
        power_on();
        check(km_is(0, 1, 0, te, 40) && km_is(TRK_DRUM, 3, 0, P_PAN, -64) && kmac_pos[0][1] == 101u,
              "macros, power-on: the working ones and their positions, from the autosave");
        check(!autosave_changed(), "macros, power-on: nothing to autosave again");

        /* song mode's keep: the loop's macros aside and back, the positions as they are */
        fxa_keep();
        kmac_clear(0);
        kmac_pos[0][1] = 5u;
        fxa_unkeep();
        check(km_is(0, 1, 0, te, 40) && kmac_pos[0][1] == 5u, "macros: song mode's keep, back at STOP (positions kept)");

        /* ERASE */
        project_erase(3);
        check(slot_none(3), "macros: ERASE D, its macros go");
        power_on();
        check(slot_none(3), "macros: ERASE D, power-on: none");

        /* a 2.8.5 record (the lane's 72 bytes alone): the lane, no macros */
        {
            fxside_t f;
            f.magic = FXSIDE_MAGIC;
            lane_fill(f.cells, PX_REV, 2u, 6u);
            f.sum = fxside_sum(&f);
            kmac_slot[1].t[0].c[0] = 9u;             /* (stale: the record must clear it) */
            st_side = &f;
            st_side_len = sizeof f;
            st_save(OBJ_PROJECT0 + 1, &proj_slot[1], sizeof proj_slot[1]);
            st_side = 0;
            st_side_len = 0;
            fx_side_read(1);
            check((fxa.slot_on & 2u) && !memcmp(fx_slot[1], f.cells, FXA_MAX) && slot_none(1),
                  "macros: a 2.8.5 side record (72 bytes): its lane, no macros");
        }
        /* a damaged macro part: none; the lane still read */
        kmac_set(1, 0, 0, P_TFLT, 20);
        record(PX_GATE, 0u, 3u);
        section_store(1);
        sections_write();
        check(side_get(OBJ_PROJECT0 + 1, &raw) == 3u, "macros + lane: both in the record");
        {
            st_hdr_t h;
            uint32_t off = st_sector(OBJ_PROJECT0 + 1, (uint32_t)st_current(OBJ_PROJECT0 + 1, &h)) + ST_SIDE_OFF +
                           (uint32_t)__builtin_offsetof(projside_t, km.m.t[1].c[0]);
            nor[off] &= (uint8_t)(nor[off] - 1u);         /* (a bit dropped in the flash: the code is not 0) */
        }
        power_on();
        check((fxa.slot_on & 2u) && slot_none(1), "macros: a damaged macro part reads as none, the lane still there");

        /* codes this firmware refuses: none (kmac_get checks each one when played) */
        memset(&kmac_slot[2], 0, sizeof kmac_slot[2]);
        kmac_slot[2].t[0].c[0] = (uint8_t)(ML_E0 + 9u), kmac_slot[2].t[0].a[0] = 10;   /* no such code */
        kmac_slot[2].t[0].c[1] = (uint8_t)(P_TFLT + 1u), kmac_slot[2].t[0].a[1] = 64;  /* amount out of range */
        kmac_slot[2].t[0].c[2] = (uint8_t)(P_SGATE + 1u), kmac_slot[2].t[0].a[2] = 5; /* not a macro's target */
        kmac_slot[2].t[TRK_DRUM].c[0] = (uint8_t)(ML_E0 + 1u), kmac_slot[2].t[TRK_DRUM].a[0] = 5;   /* drums: no E */
        kmac_slot[2].t[0].c[5] = (uint8_t)(P_TFLT + 1u), kmac_slot[2].t[0].a[5] = -64;  /* this one is fine */
        proj_slot[2] = proj_slot[1];
        fm1_irq_off();
        fxa_recall(2);
        fm1_irq_on();
        check(km_is(0, 0, 0, KMAC_OFF, 0) && km_is(0, 0, 1, KMAC_OFF, 0) && km_is(0, 1, 0, KMAC_OFF, 0) &&
              km_is(TRK_DRUM, 0, 0, KMAC_OFF, 0) && km_is(0, 2, 1, P_TFLT, -64), "macros: unknown / refused targets: off");

        /* a factory sound (and INIT, an engine change) clears the track's; NEW the drum track's too */
        apply_preset_to(&trk[0], 1);
        check(km_is(0, 2, 1, KMAC_OFF, 0) && kmac_pos[0][2] == 0u, "macros: a factory preset clears the track's");
        kmac_set(TRK_DRUM, 0, 0, P_PAN, 12);
        project_new();
        transport_req = 0;
        check(km_none(), "macros: NEW clears them all, the drum track's too");

        /* none set, no lane: nothing attached (the object as before) */
        fxa.on = 0;
        section_store(0);
        sections_write();
        {
            uint8_t b[ST_SIDE_MAX], ff = 0xFFu;
            st_side_load(OBJ_PROJECT0, b, sizeof b);
            for (i = 0; i < sizeof b; i++)
                ff &= b[i];
            check(ff == 0xFFu, "no macros, no lane: no side record");
        }
    }

    printf("fxa_persist: %d failed\n", fails);
    return fails;
}
