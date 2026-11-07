/* SPDX-License-Identifier: GPL-3.0-only */
/* KNOB MACROS in the user presets (upreset.c up_tail_t: a tail after the bank's payload, storage.c st_tail): SAVE
 * stores the selected track's targets with its sound, the bank's other slots keep theirs; LOAD gives them to the track
 * (each checked, the positions at 0); ERASE and the editor's UP_PUT clear the slot's; a bank of an older SLOOP (no
 * tail), a damaged tail, a save by an older SLOOP: the presets load, without macros. Real storage.c / upreset.c /
 * project.c / editor.c on the RAM image of the NOR (tests/editor_host.c). Exit status: failed checks. */
#include "editor_host.c"
static int fails;
static void check(int c, const char *what) { printf("up_kmac: %-78s %s\n", what, c ? "ok" : "FAIL"); fails += !c; }

static void cmd(uint32_t c, const uint8_t *a, uint32_t na)    /* an editor frame */
{
    uint8_t f[700];
    f[0] = ED_HDR0, f[1] = ED_HDR1, f[2] = ED_HDR2, f[3] = (uint8_t)c;
    memcpy(f + 4, a, na);
    ed_inject(f, 4 + na);
}
static int km_is(uint32_t t, uint32_t k, uint32_t s, uint32_t id, int32_t amt)
{
    return kmac_id[t][k * 2u + s] == id && kmac_amt[t][k * 2u + s] == amt;
}
static int km_none(uint32_t t)
{
    uint32_t i;
    for (i = 0; i < KM_N * 2u; i++)
        if (kmac_id[t][i] != KMAC_OFF || kmac_amt[t][i])
            return 0;
    return 1;
}
static int pos_zero(uint32_t t)
{
    uint32_t k;
    for (k = 0; k < KM_N; k++)
        if (kmac_pos[t][k])
            return 0;
    return 1;
}
static int slot_empty(const up_tail_t *tl, uint32_t k)
{
    static const kmac_rec_t z;
    return tl && !memcmp(&tl->s[k % UP_PER_BANK], &z, sizeof z);
}
static uint8_t *tail_bytes(uint32_t b)                        /* the current copy's tail in the NOR image */
{
    st_hdr_t h;
    int c = st_current(OBJ_UPRESET0 + b, &h);
    return c < 0 ? 0 : nor + st_sector(OBJ_UPRESET0 + b, (uint32_t)c) + ST_TAIL_OFF;
}
static void old_save(uint32_t b)                              /* the bank saved again as an older SLOOP does: no tail */
{
    static up_bank_t raw;
    memcpy(&raw, up_bank_xip[b], sizeof raw);
    st_save(OBJ_UPRESET0 + b, &raw, sizeof raw);
    up_bank_find(b);
}

int main(void)
{
    uint32_t eid = KMAC_OFF, i, rev;
    const up_tail_t *tl;
    harness_init();
    song.playing = 0;
    transport_req = 0;
    song.sel = 0;
    check(flash_ok, "the flash is there");
    for (i = P_E0; i <= P_E7 && eid == KMAC_OFF; i++)          /* an engine value of track 1's engine */
        if (kmac_ok(&trk[0], i))
            eid = i;
    check(eid != KMAC_OFF, "track 1's engine has a value a macro takes");

    /* 1. a bank never written with a tail: an older SLOOP's (the preset loads, no macros) */
    check(up_store(2, "PLAIN") == 0, "SAVE slot 3");
    old_save(0);
    check(up_used(2) && !up_tail_of(0), "a bank saved by an older SLOOP: the preset there, no tail");
    kmac_set(1, 1, 0, P_PAN, 10);
    kmac_pos_set(1, 1, 50);
    check(km_is(1, 1, 0, P_PAN, 10), "track 2 has a macro of its own");
    check(up_load_to(&trk[1], 2) == 0 && km_none(1) && pos_zero(1), "LOAD it: the track's macros gone, positions 0");

    /* 2. SAVE writes the track's macros in the tail; LOAD gives them to another track, the positions at 0 */
    kmac_set(0, 0, 0, P_TFLT, 40);
    kmac_set(0, 2, 1, eid, -30);
    kmac_pos_set(0, 0, 100);
    check(up_store(3, "MAC") == 0, "SAVE slot 4 with macros");
    tl = up_tail_of(0);
    check(tl && tl->s[3].c[0] == ml_code(P_TFLT) && tl->s[3].a[0] == 40 && tl->s[3].c[5] == ml_code(eid) &&
              tl->s[3].a[5] == -30 && slot_empty(tl, 2) && slot_empty(tl, 4),
          "the tail: slot 4's targets as codes, the others none");
    check(st_load(OBJ_UPRESET0, &proj_tmp, sizeof proj_tmp) == (int)sizeof(up_bank_t),
          "the payload stays the bank alone (3080 B: older SLOOP reads it)");
    kmac_pos_set(1, 3, 90);
    rev = fxa.rev;
    check(up_load_to(&trk[1], 3) == 0 && trk[1].eng_req == trk[0].eng_req, "LOAD slot 4 into track 2");
    check(km_is(1, 0, 0, P_TFLT, 40) && km_is(1, 2, 1, eid, -30) && km_is(1, 1, 0, KMAC_OFF, 0),
          "... its macros, as stored");
    check(pos_zero(1) && fxa.rev != rev, "... the positions at 0, the autosave told");
    audio_blocks(4);
    check(trk[1].p[P_TFLT] == trk[0].p[P_TFLT], "... at position 0 the sound is the preset's");

    /* 3. another SAVE keeps the other slots' macros */
    kmac_clear(0);
    kmac_set(0, 3, 0, P_PAN, -20);
    check(up_store(4, "TWO") == 0, "SAVE slot 5 with another macro");
    tl = up_tail_of(0);
    check(tl && tl->s[3].c[0] == ml_code(P_TFLT) && tl->s[3].a[5] == -30 && tl->s[4].c[6] == ml_code(P_PAN) &&
              tl->s[4].a[6] == -20,
          "... slot 4's kept, slot 5's there");
    {   /* (through the editor: UP_STORE takes the selected track's too) */
        uint8_t a[8] = {7, 'E', 'D', 0};
        cmd(ED_UP_STORE, a, 4);
        tl = up_tail_of(0);
        check(up_used(7) && tl && tl->s[7].c[6] == ml_code(P_PAN) && tl->s[3].c[0] == ml_code(P_TFLT),
              "the editor's UP_STORE: the macros too, the others kept");
    }

    /* 4. ERASE and the editor's UP_PUT clear that slot's */
    {
        uint8_t a[700];
        uint32_t n = 0;
        a[0] = 3;
        cmd(ED_UP_ERASE, a, 1);
        tl = up_tail_of(0);
        check(!up_used(3) && slot_empty(tl, 3) && tl->s[4].c[6] == ml_code(P_PAN), "ERASE slot 4: its macros gone, 5's kept");
        a[n++] = 4;
        a[n++] = (uint8_t)trk[0].eng_req;
        a[n++] = 'P', a[n++] = 'U', a[n++] = 'T', a[n++] = 0;
        for (i = 0; i < P_COUNT; i++)
            a[n++] = 0, a[n++] = 64;                              /* v14 0 */
        for (i = 0; i < 32u; i++)
            a[n++] = 0;
        cmd(ED_UP_PUT, a, n);
        tl = up_tail_of(0);
        check(up_used(4) && slot_empty(tl, 4) && tl->s[7].c[6] == ml_code(P_PAN), "UP_PUT slot 5: its macros gone, 8's kept");
        kmac_set(1, 0, 0, P_PAN, 5);
        check(up_load_to(&trk[1], 4) == 0 && km_none(1), "... it loads without macros");
    }

    /* 5. a damaged tail: none in the bank, the presets load */
    kmac_clear(0);
    kmac_set(0, 1, 1, P_TFLT, -64);
    check(up_store(5, "ROT") == 0 && up_tail_of(0), "SAVE slot 6 with a macro");
    tail_bytes(0)[4 + 5 * sizeof(kmac_rec_t) + 8 + 3] ^= 0x01;    /* bit rot in slot 6's amounts */
    check(!up_tail_of(0), "a tail with a bad CRC: none");
    check(up_load_to(&trk[1], 5) == 0 && km_none(1) && up_load_to(&trk[1], 7) == 0 && km_none(1),
          "... slot 6 and slot 8 load, without macros");
    check(up_store(6, "MEND") == 0 && (tl = up_tail_of(0)) && slot_empty(tl, 7) && tl->s[6].c[3] == ml_code(P_TFLT),
          "the next SAVE: a new tail (the damaged one's macros not carried)");

    /* 6. targets checked at the load: a code this firmware does not know, an amount out of range */
    {
        static up_tail_t t;
        static up_bank_t raw;
        memcpy(&t, up_tail_of(0), sizeof t);
        t.s[6].c[0] = 119, t.s[6].a[0] = 10;                   /* (no parameter) */
        t.s[6].c[1] = ml_code(P_PAN), t.s[6].a[1] = 64;         /* (past +63) */
        t.s[6].c[2] = ml_code(P_PAN), t.s[6].a[2] = -12;
        t.crc = st_crc32(&t, sizeof t - 4u);
        memcpy(&raw, up_bank_xip[0], sizeof raw);
        st_tail = &t, st_tail_len = sizeof t;
        st_save(OBJ_UPRESET0, &raw, sizeof raw);
        st_tail = 0, st_tail_len = 0;
        up_bank_find(0);
        check(up_load_to(&trk[1], 6) == 0 && km_is(1, 0, 0, KMAC_OFF, 0) && km_is(1, 0, 1, KMAC_OFF, 0) &&
                  km_is(1, 1, 0, P_PAN, -12) && km_is(1, 1, 1, P_TFLT, -64),
              "a code unknown, an amount out of range: off; the rest as stored");
    }

    /* 7. the bank saved again by an older SLOOP (or the editor's raw bank restore): presets kept, macros gone */
    old_save(0);
    check(!up_tail_of(0) && up_used(6) && up_used(7) && up_load_to(&trk[1], 6) == 0 && km_none(1),
          "an older SLOOP's save: the presets load, without macros");
    check(up_store(8, "AGAIN") == 0 && (tl = up_tail_of(0)) && slot_empty(tl, 6) && tl->s[8].c[3] == ml_code(P_TFLT),
          "SAVE after it: a tail again, only that slot's");

    /* 8. the other bank, and the drum track */
    check(up_store(20, "BANK2") == 0 && (tl = up_tail_of(1)) && tl->s[4].c[3] == ml_code(P_TFLT) &&
              up_tail_of(0)->s[8].c[3] == ml_code(P_TFLT),
          "bank 2 has a tail of its own");
    {   /* 9. the project keeps which user preset a track plays (0x80 | its slot in the preset byte): named again after a
         * load (autosave, a section), not 808 BOOM; a factory sound as before */
        static project_t pj;
        check(up_load_to(&trk[1], 20) == 0 && user_of(&trk[1]) == 20u, "LOAD slot 21 into track 2 (named after it)");
        proj_capture(&pj);
        check(pj.t[1].preset == 0x94u && pj.t[0].preset < 0x80u, "the project: track 2's preset byte 0x80 | slot 20");
        trk[1].user = 0;
        proj_apply(&pj, 1);
        check(trk[1].user == 21u && user_of(&trk[1]) == 20u && trk[1].preset == 0u && !trk[0].user,
              "loaded back: track 2 named after user preset 21 again, track 1 a factory sound");
        pj.t[1].preset = 0x80u + 31u;                   /* an empty slot: no name (a factory one, as before) */
        proj_apply(&pj, 1);
        check(!up_used(31) && user_of(&trk[1]) == UP_SLOTS, "an empty slot: the factory name, as before");
    }
    song.sel = TRK_DRUM;
    check(up_store(9, "DRUM") == 1 && up_load_to(TDRUM, 8) == 1, "the drum track: no store, no load");
    song.sel = 0;
    printf("up_kmac: %s\n", fails ? "FAILED" : "passed");
    return fails;
}
