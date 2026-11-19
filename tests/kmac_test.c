/* SPDX-License-Identifier: GPL-3.0-only */
/* KNOB MACROS (fx.c kmac_apply / kmac_restore, seq.c kmac_ok / lock_next / kmac_sync, params.c kmac_label):
 *   render   a macro at position 0 leaves the render bit for bit; LEVEL / FILT moved change it; p[] is the value set
 *            after every block; the same with every split of the units over the two cores (cpu1_units 0, 15, -1)
 *   overlay  two targets on one id summed, clamped once; an engine's values left alone while a preset fades
 *   fade     a preset's fade sounds with the macros (kmac_mv into p_old), an engine's too (pe_old)
 *   targets  kmac_ok's exclusions (note-on only, per engine, the drum track's few); lock_next's ring (OFF
 *            in it); ALGORITHM's walk (lock_next, no flag) as 2.4's; the labels distinct
 * Each render in a fresh fork()ed child (the same start every time, as tests/mix_split_test.c).
 * Exit status: the number of failed checks. */
#define main hostsim_main
#include "hostsim.c"
#undef main

static int fails;
static void check(int ok, const char *what)
{
    printf("kmac: %-92s %s\n", what, ok ? "ok" : "FAIL");
    fails += !ok;
}

#define BLOCKS 600u
typedef struct { uint64_t hash; double rms; uint32_t moved, jobs; } res_t;
enum { M_NONE, M_POS0, M_LEVEL, M_FILT, M_SPLIT };

static void scene(uint32_t mode)                         /* parts 1 and 3 hold a chord, the macros of the mode */
{
    uint32_t k;
    host_tracks_init();
    for (k = 0; k < NTRK; k++)
        trk[k].p[P_LEVEL] = 100, trk[k].p[P_REV] = 20;
    host_preset(&trk[0], 0, 0);
    host_preset(&trk[2], 1, 2);
    song.playing = 0;
    song.master_q12 = 2048;
    trk_note_on(&trk[0], 45, 100);
    trk_note_on(&trk[0], 52, 90);
    trk_note_on(&trk[2], 60, 100);
    if (mode == M_POS0) {                                /* targets and amounts, every position at 0 */
        kmac_set(0, 0, 0, P_LEVEL, -64);
        kmac_set(0, 0, 1, P_TFLT, 50);
        kmac_set(2, 3, 0, P_LRATE, 63);
    } else if (mode == M_LEVEL) {
        kmac_set(0, 1, 0, P_LEVEL, -64);
        kmac_pos_set(0, 1, 127);
    } else if (mode == M_FILT) {
        kmac_set(0, 2, 1, P_TFLT, 63);                  /* the track's filter to a high-pass */
        kmac_pos_set(0, 2, 100);
    } else if (mode == M_SPLIT) {                       /* on both cores' parts and the drums */
        kmac_set(0, 0, 0, P_TFLT, -40), kmac_pos_set(0, 0, 90);
        kmac_set(2, 0, 0, P_LEVEL, -30), kmac_set(2, 0, 1, P_LRATE, 50), kmac_pos_set(2, 0, 127);
        kmac_set(2, 1, 0, P_REV, 63), kmac_pos_set(2, 1, 64);
        kmac_set(TRK_DRUM, 0, 0, P_PAN, 40), kmac_set(TRK_DRUM, 0, 1, P_TFLT, -50), kmac_pos_set(TRK_DRUM, 0, 127);
    }
}

static res_t render(uint32_t mode, int32_t units)
{
    static int16_t base[NTRK][P_COUNT];
    res_t r = {0xcbf29ce484222325ull, 0, 0, 0};
    double e = 0;
    uint32_t b, i, k;
    cpu1_host_mode();
    cpu1_units = units;
    scene(mode);
    for (b = 0; b < BLOCKS; b++) {
        int32_t o[2 * CTL];
        for (k = 0; k < NTRK; k++)
            memcpy(base[k], trk[k].p, sizeof base[k]);
        mix_block(o, CTL);
        for (k = 0; k < NTRK; k++)
            r.moved += memcmp(base[k], trk[k].p, sizeof base[k]) != 0;
        for (i = 0; i < 2u * CTL; i++) {
            uint32_t u = (uint32_t)o[i];
            for (k = 0; k < 4u; k++) {
                r.hash ^= (u >> (8u * k)) & 0xFFu;
                r.hash *= 0x100000001B3ull;
            }
            if (b >= 100u)
                e += (double)o[i] * o[i];
        }
    }
    r.rms = sqrt(e / (double)((BLOCKS - 100u) * 2u * CTL));
    r.jobs = cpu1_host_jobs();
    return r;
}

static res_t child(uint32_t mode, int32_t units)        /* the render in a fresh process (hash 0: it crashed) */
{
    int p[2], st = 0;
    pid_t pid;
    res_t r = {0, 0, 0, 0};
    if (pipe(p))
        return r;
    fflush(stdout);
    if (!(pid = fork())) {
        res_t c = render(mode, units);
        close(p[0]);
        _exit(write(p[1], &c, sizeof c) == (ssize_t)sizeof c ? 0 : 1);
    }
    close(p[1]);
    if (read(p[0], &r, sizeof r) != (ssize_t)sizeof r)
        r.hash = 0;
    close(p[0]);
    waitpid(pid, &st, 0);
    if (!WIFEXITED(st) || WEXITSTATUS(st))
        r.hash = 0;
    return r;
}

static void t_render(void)
{
    res_t r0 = child(M_NONE, 0), r1 = child(M_POS0, 0), rl = child(M_LEVEL, 0), rf = child(M_FILT, 0);
    printf("  none rms %.0f, pos 0 rms %.0f, LEVEL -100 %% rms %.0f, FILT +100 %% x 100/127 rms %.0f\n", r0.rms, r1.rms,
           rl.rms, rf.rms);
    check(r0.hash && r0.rms > 100.0, "the scene sounds");
    check(r1.hash == r0.hash, "targets set, every position at 0: the render bit for bit as without");
    check(rl.hash && rl.hash != r0.hash && rl.rms < r0.rms * 0.8, "LEVEL -100 % at position 127: the part quieter");
    check(rf.hash && rf.hash != r0.hash, "FILT +100 % at position 100: the render changes");
    check(!r0.moved && !r1.moved && !rl.moved && !rf.moved, "p[] after every block: the values set (none moved)");
}

static void t_split(void)
{
    res_t r0 = child(M_SPLIT, 0), r15 = child(M_SPLIT, 15), rd = child(M_SPLIT, -1), rn = child(M_NONE, 0);
    printf("  split: units 0 %016llx, 15 %016llx (jobs %u), -1 %016llx (jobs %u)\n", (unsigned long long)r0.hash,
           (unsigned long long)r15.hash, r15.jobs, (unsigned long long)rd.hash, rd.jobs);
    check(r0.hash && r0.hash != rn.hash, "macros on parts 1, 3 and the drums change the render");
    check(r15.hash == r0.hash && rd.hash == r0.hash, "the same output whatever the split of the units (0, 15, -1)");
    check(r15.jobs > 0u, "units 15: jobs handed to core 1");
    check(!r0.moved && !r15.moved && !rd.moved, "p[] after every block: the values set, with every split");
}

static void t_overlay(void)
{
    track_t *t = &trk[0];
    host_tracks_init();
    host_preset(t, 0, 0);
    kmac_clear(0);
    t->p[P_LEVEL] = 100;
    kmac_set(0, 0, 0, P_LEVEL, 63), kmac_pos_set(0, 0, 127);    /* +125 */
    kmac_set(0, 1, 1, P_LEVEL, -64), kmac_pos_set(0, 1, 127);   /* -127 */
    kmac_apply();
    check(t->p[P_LEVEL] == 98 && kmac_svn == 1u, "LEVEL +125 and -127 on one id: summed, then clamped once (98, one save)");
    kmac_restore();
    check(t->p[P_LEVEL] == 100 && !kmac_svn, "restored: the value set");
    kmac_set(0, 1, 1, P_LEVEL, 63);
    kmac_apply();
    check(t->p[P_LEVEL] == 127, "LEVEL +125 twice: clamped to the range's top");
    kmac_restore();
    kmac_set(0, 1, 1, P_REV, -64);
    t->p[P_REV] = 30;
    kmac_set(0, 2, 0, P_E4, 63), kmac_pos_set(0, 2, 64);       /* ANALOG's CUT */
    t->p[P_E4] = 20;
    t->pold = 1;                                               /* a preset fading: the engine values left alone */
    kmac_apply();
    check(t->p[P_LEVEL] == 127 && t->p[P_REV] == 0 && t->p[P_E4] == 20,
          "a preset fading: LEVEL and REV moved, the engine's CUT not");
    kmac_restore();
    t->pold = 0;
    kmac_apply();
    check(t->p[P_E4] == 83, "the fade over: CUT moved (+63)");
    kmac_restore();
    check(t->p[P_LEVEL] == 100 && t->p[P_REV] == 30 && t->p[P_E4] == 20, "every value back, last first");
    kmac_set(0, 0, 0, P_LEVEL, 0);
    check(kmac_d[0][0] == 0, "amount 0: no delta");
    kmac_set(0, 3, 0, P_SGATE, 50);
    check(kmac_id[0][6] == KMAC_OFF && kmac_amt[0][6] == 0, "a target kmac_ok refuses: set off");
    kmac_clear(0);
    check(!kmac_on[0] && kmac_id[0][3] == KMAC_OFF && !kmac_pos[0][1] && !kmac_amt[0][4],
          "kmac_clear: no target, positions and amounts 0");
    kmac_apply();
    check(!kmac_svn && t->p[P_LEVEL] == 100, "cleared: nothing moves");
    {
        uint8_t r = (uint8_t)fxa.rev;
        kmac_pos_set(0, 0, 10);
        check((uint8_t)(fxa.rev - r) == 1u, "a position set bumps fxa.rev (the autosave)");
    }
}

/* a preset's fade (voice.c sound_change, fx.c kmac_mv) and an engine's (pe_old) sound with the macros as heard */
static double blk_rms(void)
{
    int32_t o[2 * CTL];
    double e = 0;
    uint32_t i;
    mix_block(o, CTL);
    for (i = 0; i < 2u * CTL; i++)
        e += (double)o[i] * o[i];
    return sqrt(e / (2.0 * CTL));
}
static void t_fade(void)
{
    track_t *t = &trk[0];
    double mx = 0, r;
    uint32_t b, k;
    cpu1_host_mode();
    cpu1_units = 0;
    host_tracks_init();
    for (k = 0; k < NTRK; k++)
        kmac_clear(k);
    host_preset(t, 0, 0);
    t->p[P_LEVEL] = 110, t->p[P_SUS] = 127, t->p[P_REL] = 100;
    song.master_q12 = 4096;
    kmac_set(0, 0, 0, P_LEVEL, -64), kmac_pos_set(0, 0, 127);   /* LEVEL held at 0 by the macro */
    trk_note_on(t, 48, 110), trk_note_on(t, 55, 110);
    for (b = 0; b < 200u; b++)
        r = blk_rms();
    sound_change(t), panic_req |= 1u, kmac_clear(0);            /* a preset loads (ui.c apply_preset_to) */
    for (b = 0; b < XF_BLOCKS + 2u; b++)
        if ((r = blk_rms()) > mx)
            mx = r;
    printf("  a preset over a part the macro holds silent: the fade's loudest block rms %.0f\n", mx);
    check(mx < 50.0, "a preset's fade: the old sound with its macros (silent stays silent, no burst)");
    host_preset(t, 0, 0);
    t->p[P_E4] = 20;
    kmac_set(0, 2, 0, P_E4, 63), kmac_pos_set(0, 2, 64);       /* ANALOG's CUT +63 */
    blk_rms();
    check(t->pe_old[4] == 83 && t->p[P_E4] == 20, "an engine's value moved: in pe_old too (an engine fade's), p[] kept");
    kmac_clear(0);
}

/* 2.4's ALGORITHM walk (ui_layers.c lock_par_step before lock_next) */
static uint32_t old_step(const track_t *t, uint32_t id, int32_t s)
{
    uint32_t guard = P_COUNT;
    do {
        id = (id + (uint32_t)P_COUNT + (uint32_t)(s > 0 ? 1 : -1)) % P_COUNT;
    } while (guard-- && (!p_lockable(id) || lock_desc(t, id)->max <= lock_desc(t, id)->min ||
                         (is_drum(t) && id > P_E0 && id <= P_E7)));
    return id;
}

static void t_targets(void)
{
    static const uint8_t NEVER[] = {P_SGATE, P_DETUNE, P_LPHASE, P_GLIDE, P_AMODE, P_VOICE, P_SLEN, P_MUTE, P_ITYPE};
    track_t *t = &trk[0], *d = TDRUM;
    uint32_t i, id, ok = 1, n, e, same = 1;
    host_tracks_init();
    host_preset(t, 0, 0);
    for (i = 0; i < sizeof NEVER; i++)
        ok &= !kmac_ok(t, NEVER[i]) && !kmac_ok(d, NEVER[i]);
    check(ok, "never a target: GATE, DETUNE, the LFO's PHASE, GLIDE, nor what does not lock");
    check(kmac_ok(t, P_LEVEL) && kmac_ok(t, P_TFLT) && kmac_ok(t, P_REV) && kmac_ok(t, P_LD_FLT) && kmac_ok(t, P_IMIX) &&
              kmac_ok(t, P_E0) && kmac_ok(t, P_E7),
          "a part: LEVEL, FILT, REV, LFO DEST, the INSERT's MIX, ANALOG's E0..E7");
    t->engine = t->eng_req = 4;                                /* SAMPLE */
    check(!kmac_ok(t, P_E0) && kmac_ok(t, P_E1), "SAMPLE: not SET (E0), TUNE yes");
    t->engine = t->eng_req = ENGI_GRAIN;
    check(!kmac_ok(t, P_E0) && kmac_ok(t, P_E1), "GRAIN: not SRC (E0)");
    t->engine = t->eng_req = ENGI_PHYS;
    check(!kmac_ok(t, P_E0) && kmac_ok(t, P_E1), "PHYS: not MODEL (E0)");
    t->engine = t->eng_req = ENGI_FM6;
    check(!kmac_ok(t, P_E3) && !kmac_ok(t, P_E5) && !kmac_ok(t, P_E7) && (kmac_ok(t, P_E1) || kmac_ok(t, P_E2)),
          "FM6: not E3, E5 (note-on), E7 (the patch)");
#if FELUCCA_SLICE
    t->engine = t->eng_req = ENGI_SLICE;
    check(!kmac_ok(t, P_E0) && !kmac_ok(t, P_E1) && !kmac_ok(t, P_E2) && !kmac_ok(t, P_E5), "SLICE: not E0, E1, E2, E5");
#endif
    t->engine = 0;                                             /* (a section loaded: FM6 coming, ANALOG fading out) */
    check(!kmac_ok(t, P_E7) && kmac_ok(t, P_E1), "an engine fading: the one coming (eng_req) judges its values");
    t->eng_req = 0;
    for (id = 0, ok = 1, n = 0; id < P_COUNT; id++)
        if (kmac_ok(d, id)) {
            n++;
            ok &= id == P_PAN || id == P_TFLT || (id >= P_SLCR && id <= P_SLDEPTH) || (id >= P_IA && id <= P_IMIX);
        }
    check(ok && n >= 3u && kmac_ok(d, P_PAN) && kmac_ok(d, P_TFLT) && !kmac_ok(d, P_LEVEL) && !kmac_ok(d, P_E0) &&
              !kmac_ok(d, P_REV),
          "the drum track: PAN, FILT, the SLICER, the INSERT only");
    /* lock_next: the ring */
    check(lock_next(t, KMAC_OFF, 1, 1) == P_LEVEL && lock_next(t, P_LEVEL, -1, 1) == KMAC_OFF,
          "OFF -> LVL -> back to OFF");
    for (id = KMAC_OFF, n = 0, ok = 1; n < 2u * P_COUNT; n++) {
        id = lock_next(t, id, 1, 1);
        if (id == KMAC_OFF)
            break;
        ok &= kmac_ok(t, id);
    }
    for (e = 0, i = 0; i < P_COUNT; i++)
        e += (uint32_t)kmac_ok(t, i);
    check(ok && id == KMAC_OFF && n == e, "up from OFF: every target once, then OFF again");
    for (id = KMAC_OFF, n = 0; n < 2u * P_COUNT && (id = lock_next(t, id, -1, 1)) != KMAC_OFF; n++)
        ;
    check(n == e, "down from OFF: the same count");
    for (id = KMAC_OFF, ok = 1, n = 0; n < 40u && (id = lock_next(d, id, 1, 1)) != KMAC_OFF; n++)
        ok &= kmac_ok(d, id);
    check(ok && n >= 3u && n < 40u, "the drum track's ring: its few targets");
    for (e = 0; e < NENGINES; e++) {
        t->engine = t->eng_req = (uint8_t)e;
        for (id = 0; id < P_COUNT; id++)
            same &= lock_next(t, id, 1, 0) == old_step(t, id, 1) && lock_next(t, id, -1, 0) == old_step(t, id, -1);
    }
    for (id = 0; id < P_COUNT; id++)
        same &= lock_next(d, id, 1, 0) == old_step(d, id, 1) && lock_next(d, id, -1, 0) == old_step(d, id, -1);
    t->engine = t->eng_req = 0;
    check(same, "ALGORITHM's walk (lock_next, no flag): 2.4's order, every engine and the drum track");
    /* the labels */
    {
        uint32_t a, b, dist = 1;
        char la[8];
        for (e = 0; e <= NENGINES; e++) {               /* every engine, then the drum track */
            track_t *u = e < NENGINES ? t : d;
            if (e < NENGINES)
                t->engine = t->eng_req = (uint8_t)e;
            for (a = 0; a < P_COUNT; a++)
                for (b = a + 1u; b < P_COUNT; b++)
                    if (kmac_ok(u, a) && kmac_ok(u, b)) {
                        str_cpy(la, kmac_label(u, a), sizeof la);   /* (one static buffer) */
                        if (!strcmp(la, kmac_label(u, b)))
                            printf("  same label: eng %u: %u %u %s\n", e, a, b, la), dist = 0;
                    }
        }
        t->engine = t->eng_req = 0;
        check(dist, "the targets' labels: distinct, every engine and the drum track");
    }
    check(!strcmp(kmac_label(t, P_ED_FLT), "EFLT") && !strcmp(kmac_label(t, P_LD_FLT), "LFLT") &&
              !strcmp(kmac_label(t, P_SLDEPTH), "SDPTH") && !strcmp(kmac_label(t, P_SLRATE), "SRATE") &&
              !strcmp(kmac_label(t, P_LRATE), "LRATE") && !strcmp(kmac_label(t, P_IA), "INS A") &&
              !strcmp(kmac_label(t, P_LEVEL), "LVL"),
          "labels: EFLT, LFLT, SDPTH, SRATE, LRATE, INS A, LVL");
}

int main(void)
{
    setvbuf(stdout, 0, _IONBF, 0);
    t_render();
    t_split();
    t_overlay();
    t_targets();
    t_fade();
    printf("kmac: %s\n", fails ? "FAILED" : "all checks ok");
    return fails;
}
