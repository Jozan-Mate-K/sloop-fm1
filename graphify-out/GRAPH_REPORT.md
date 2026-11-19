# Graph Report - sloop-fm1  (2026-11-08)

## Corpus Check
- 208 files · ~811,869 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 21 file(s) not represented in the graph (top: .S 5, (none) 4, .bat 2)

## Summary
- 4357 nodes · 12467 edges · 213 communities (173 shown, 40 thin omitted)
- Extraction: 74% EXTRACTED · 26% INFERRED · 0% AMBIGUOUS · INFERRED: 3225 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `8b887172`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Track State Struct
- editor_host.c
- ed_handle
- UI Drawing Primitives
- Sequencer v2 Tests
- Main UI Step Editing
- renderSamples
- Web Editor LIVE Strip
- Sample Pack Tooling
- Web Editor Sound & Mixer
- seq.c
- Project Capture & Apply
- fm1_install.py
- main.c
- Studio Layer & Drum Screens
- Web Editor Shell & Builds
- FM6 Operator Core (msfa)
- UI Pages Tests
- trk_note_off
- Firmware Build & Packaging
- HAL IRQ/Audio/Timer Headers
- Hip-Hop Pack Generator
- Mix Bus & Effects DSP
- track_t
- Golden Renders & CPU Budgets
- Note Length Tests
- load
- Site & Webfont Tooling
- main
- Engine Dispatch & Sample/Noise
- PHYS Physical Modelling
- Host Regression Suite
- upreset.c
- Web Editor Step & Drum Grid
- LocalPreview
- Wave/Drumkit Table Generators
- Web Editor LIVE Pro (LVX)
- cpu1.c
- Hold Layers UI
- drums.c
- Web Editor E2E Tests
- req (request builders)
- fm1_input.h
- FX 2.5.1 Tests
- Guide: Layers & Recording
- Slice Engine
- Punch-in FX Engine
- target_budget.py
- Hold-Record Tests
- main
- OTA Update Session
- hostsim.c
- editor_fuzz.c
- preview.c
- host_tracks_init
- System Startup & Loader HAL
- crc32
- console.c
- ed_bk_commit
- Flash Driver HAL
- FM6 Engine Tests
- Song Screen UI
- Menus & Panel Palette
- usb.c
- Arp & Scale Logic
- Visualiser Animations
- Slicer Track
- The drum track (track 4)
- The HOME menu
- Step Recording
- Flash Storage & CRC
- Screens 2.6 Overview
- Bootloader Package Reader
- GRAIN Engine
- Guide: Sound Bank & Presets
- Loader Wire Tests
- gen_samples.py
- Sample Credits & Licences
- Live Tracks Screenshot
- Installer Page Updater
- Guide: Punch-in FX & Signal Path
- Song Arm Tests
- OTA JS Updater
- Screens Overview (classic)
- Screens 2.3 Overview
- load_package
- Preview Worklet Tests
- Sloop Screens Overview
- OTA Wire Tests
- Web Editor SYN Drum Kits
- LCD Driver
- voice_t
- Logo Generator
- Installer Page & Fonts
- main
- rn
- fm1ota.js
- Editor Sound Screenshot
- Live Grid Screenshot
- Screens 2.5 Overview
- Drum Synth Voices
- main
- Project Format Tests
- UI Stress & Bench Tests
- INFO command (version discovery)
- Drum Synth Editor Screenshot
- TRIO Engine
- main
- kmac_test.c
- MIDI & Texture Screenshot
- Installer Package Template
- The web editor
- Guide: MIDI & Sync
- Guide: Song Mode & Sections
- Quickguide PDF Generator
- Piano Roll Screenshot
- Punch Layer Screenshot
- Editor Preview Client
- eng_fm6.c
- is_drum
- Project Overview & Engines
- Layer System Overview
- Cartridge Import Screenshot
- recovery_test.c
- PWA Tests
- Release Notes 2.6-2.8
- FM6 Patch Generator
- Parameter Icon Atlas
- Backup Screenshot
- Chop Editor Screenshot
- Drum Sequencer Screenshot
- Preview AudioWorklet
- MidoBackend
- SEL layer (key and chords)
- Editor Protocol & Preview Docs
- Font Rendering Tests
- SLOOP Brand Identity
- Dual-Core & RAM Branches
- param_desc_t
- Bitmap Font Generator
- fm1pkg_make.py
- MIDI Link (mido)
- FM1 Package Validation
- FM6 module (6-op voice pack/unpack, SysEx, bank)
- Build & Install Docs
- noise32
- Release Notes 2.0-2.3
- sample_pitch_test.c
- Web Editor Drum Panel
- Steps Layer Screenshot
- Dual-Core Render Units
- InstallError
- midi_uart_test.c
- Protocol v9-v12 Features
- gen_drumkits.py
- mix_block
- User Kit Tests
- eq
- main
- SLOOP quickstart (FR)
- Core-1 HAL & Credits
- Guide: ENV & LFO
- Chop Attack Tests
- midi_uart.c
- msfa Apache-2.0 license notice
- drum_steal_test.c
- run()
- run_tests.sh
- build.sh
- webapp/sw.js
- cpu1_modes.sh
- render
- web/sw.js
- Mock-mode local audio preview keys
- package.json
- CC0 instrument samples (SAMPLE engine)
- CLAUDE.md graphify instructions
- applyLang()
- Going back (to earlier SLOOP / official 
- Latency-compensated recording
- editor_fuzz.sh script
- run_preview_tests.sh
- get_toolchain.sh
- LVX.midiKey()
- Core 0 stack painting/measurement
- klattsch (VOICE formant reference)
- Lights (button/key glow)
- felucca-patch JSON file save/load
- PWA offline service worker and install p
- KIT constants
- SMP constants
- ui_frame
- eng_sample.c
- SLOOP 2.4
- fm6_sync
- FakeFM1
- events_block
- run
- core.h
- .find
- branch-context.sh

## God Nodes (most connected - your core abstractions)
1. `track_t` - 262 edges
2. `clamp()` - 140 edges
3. `main()` - 96 edges
4. `track` - 94 edges
5. `is_drum()` - 81 edges
6. `mix_block()` - 78 edges
7. `host_tracks_init()` - 70 edges
8. `trk_note_on()` - 64 edges
9. `memset()` - 61 edges
10. `ui_input()` - 61 edges

## Surprising Connections (you probably didn't know these)
- `keptIds()` --semantically_similar_to--> `param_kept()`  [INFERRED] [semantically similar]
  web/editor.html → firmware/src/ui.c
- `ARR (song order codec)` --semantically_similar_to--> `arr_valid()`  [INFERRED] [semantically similar]
  web/editor.html → firmware/src/arranger.h
- `FM6 module (6-op voice pack/unpack, SysEx, bank)` --semantically_similar_to--> `fm6_unpack()`  [INFERRED] [semantically similar]
  web/editor.html → firmware/src/eng_fm6.c
- `FM6 module (6-op voice pack/unpack, SysEx, bank)` --semantically_similar_to--> `fm6_pack()`  [INFERRED] [semantically similar]
  web/editor.html → firmware/src/eng_fm6.c
- `THEME (theme_t codec, readability)` --semantically_similar_to--> `theme_apart()`  [INFERRED] [semantically similar]
  web/editor.html → firmware/src/gfx.c

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Dual-core render split flow** — dualcore_render_units, dualcore_cpu1_h_api, dualcore_accumulator_set, dualcore_units_split, dualcore_8ms_timeout_fallback [EXTRACTED 0.80]
- **GPL + assets section-7 combination** — licensing_gpl3, licensing_felucca_assets, licensing_section7_permission [EXTRACTED 0.80]
- **Firmware build toolchain stack** — building_build_sh, building_jieli_toolchain, building_ac79_sdk, building_docker, building_fwsc_package [EXTRACTED 0.85]
- **Piano roll note editing flow** — assets_screens_editor_pianoroll_piano_roll_view, assets_screens_editor_pianoroll_note_length_selector, assets_screens_editor_pianoroll_note_ties, assets_screens_editor_pianoroll_four_note_chord_limit, assets_screens_editor_pianoroll_octave_range [EXTRACTED 1.00]
- **Punch layer continuous knobs (filter, dust, duck)** — assets_screens_layer_punch_on_filter_knob, assets_screens_layer_punch_on_dust_knob, assets_screens_layer_punch_on_duck_knob [EXTRACTED 1.00]
- **Punch FX effect categories (one per grid row)** — assets_screens_layer_punch_on_loop_repeat_effects, assets_screens_layer_punch_on_time_effects, assets_screens_layer_punch_on_filter_effects, assets_screens_layer_punch_on_texture_effects [EXTRACTED 1.00]
- **Four encoder-mapped track parameters** — assets_screens_live_tracks_swing_param, assets_screens_live_tracks_level_param, assets_screens_live_tracks_steps_param, assets_screens_live_tracks_pan_param [EXTRACTED 1.00]
- **Four colour-coded tracks sharing one row layout** — assets_screens_live_tracks_track_1_808_boom_analog, assets_screens_live_tracks_track_2_rhodes_digital, assets_screens_live_tracks_track_3_lofi_flute_sample, assets_screens_live_tracks_track_4_808_drums [EXTRACTED 1.00]
- **Four per-track synth engines (wheel, digital, analog, drums)** — assets_screens_sloop_2_3_screens_tonewheel_organ_engine, assets_screens_sloop_2_3_screens_digital_piano_engine, assets_screens_sloop_2_3_screens_analog_pad_engine, assets_screens_sloop_2_3_screens_drums_engine [EXTRACTED 1.00]
- **Pages sharing the 4-param engine layout** — assets_screens_sloop_2_5_screens_phys_screen, assets_screens_sloop_2_5_screens_noise_screen, assets_screens_sloop_2_5_screens_glo_drums_screen, assets_screens_sloop_2_5_screens_engine_page_layout [EXTRACTED 1.00]
- **GLO global settings pages** — assets_screens_sloop_2_6_screens_glo_texture_screen, assets_screens_sloop_2_6_screens_glo_midi_screen, assets_screens_sloop_2_6_screens_glo_midi2_screen [EXTRACTED 1.00]
- **PWA build features stripped from the standalone offline build** — docs_webapp_editor_index_pwa_manifest, docs_webapp_editor_index_service_worker_registration, docs_webapp_editor_index_pwa_install_button [EXTRACTED 1.00]
- **Contents of an FM-1 full backup file** — assets_screens_editor_backup_full_device_backup, assets_screens_editor_backup_project_concept, assets_screens_editor_backup_user_presets, assets_screens_editor_backup_user_samples_usr1_3, assets_screens_editor_backup_device_settings [EXTRACTED 1.00]
- **FM-1 two-step USB-MIDI firmware update flow** — docs_webapp_installer_index_updater_install, docs_webapp_installer_index_handshake, docs_webapp_installer_index_updater_serve, docs_webapp_installer_index_parserequest, docs_webapp_installer_index_response, docs_webapp_installer_index_updater_write, docs_webapp_installer_index_logicalimage [EXTRACTED 1.00]
- **Free (CC0/CC BY) sample sourcing for SLOOP sounds** — assets_samples_cc0_attribution_vsco_2_ce, assets_samples_cc0_attribution_vcsl, assets_samples_cc0_attribution_sonic_pi_sample_set, assets_samples_cc0_credits_sample_engine, assets_hiphop_pack_credits_sloop_hiphop_pack, assets_hiphop_pack_credits_greg_sullivan_wurlitzer_ep200 [EXTRACTED 1.00]
- **Master bus chain (texture, DUST, punch-ins, FILT, limiter)** — guide_texture, guide_dust, guide_punch_in_effects, guide_filt, guide_limiter [EXTRACTED 1.00]
- **The seven hold-layers** — guide_fx_layer, guide_edit_layer, guide_arp_layer, guide_seq_layer, guide_sel_layer, guide_glo_layer, guide_save_layer [EXTRACTED 1.00]
- **The twelve synth engines** — guide_engine_analog, guide_engine_digital, guide_engine_phase, guide_engine_lofi, guide_engine_sample, guide_engine_voice, guide_engine_trio, guide_engine_wheel, guide_engine_grain, guide_engine_fm6, guide_engine_phys, guide_engine_noise [EXTRACTED 1.00]
- **Hold-a-button layer performance system** — sloop_layer_system, sloop_fx_layer, sloop_edit_layer, sloop_seq_layer, sloop_sel_layer, sloop_glo_layer, sloop_save_layer [EXTRACTED 1.00]
- **msfa provenance and licensing chain** — licenses_apache_2_0_msfa_dexed, licenses_apache_2_0_msfa_msfa, licenses_apache_2_0_msfa_fm6_core_c_port, licenses_apache_2_0_msfa_apache_license_2_0, licenses_apache_2_0_msfa_gpl_combination, guide_felucca [EXTRACTED 1.00]
- **Protocol version evolution via INFO byte** — web_editor_protocol_info_command, web_editor_protocol_v3_tracks, web_editor_protocol_v5_drum_lanes, web_editor_protocol_v9_fm6_patches, web_editor_protocol_v12_live [EXTRACTED 1.00]
- **Engines sharing per-track state area (no extra memory)** — sloop_shared_engine_memory, sloop_fm6_engine, sloop_phys_engine, sloop_noise_engine [EXTRACTED 1.00]
- **Held-key layer screens (SEQ/GLO/SAVE/SEL)** — assets_screens_sloop_screens_seq_layer_screen, assets_screens_sloop_screens_glo_layer_screen, assets_screens_sloop_screens_save_layer_screen, assets_screens_sloop_screens_sel_layer_screen [EXTRACTED 1.00]
- **Tempo-Synced Parameters** — assets_screens_editor_sound_slicer_section, assets_screens_editor_sound_delay_section, assets_screens_editor_sound_lfo_panel, assets_screens_editor_sound_tempo_sync [EXTRACTED 1.00]
- **Editor SysEx protocol stack (framing, codecs, request/response link)** — web_editor_frame, web_editor_unframe, web_editor_reader, web_editor_parse, web_editor_req, web_editor_replymatches, web_editor_link, web_editor_pack7, web_editor_unpack7 [EXTRACTED 1.00]
- **Live recording state shown across header and armed track** — assets_screens_live_tracks_global_record_indicator, assets_screens_live_tracks_track_rec_badge, assets_screens_live_tracks_transport_position, assets_screens_live_tracks_playhead_marker [INFERRED 0.75]
- **Sound Editor Modulation Sources & Targets** — assets_screens_editor_sound_env_destinations, assets_screens_editor_sound_lfo_destinations, assets_screens_editor_sound_filter_section, assets_screens_editor_sound_adsr_envelope [INFERRED 0.75]
- **Synth parameter glyph families in the icon atlas** — assets_icons_envelope_icons, assets_icons_filter_icons, assets_icons_oscillator_icons, assets_icons_effect_icons, assets_icons_sequencer_icons, assets_icons_lfo_waveform_icons, assets_icons_engine_icons [INFERRED 0.85]
- **Cartridge import -> select -> store-in-bank flow** — assets_screens_editor_cartridge_syx_drop_import, assets_screens_editor_cartridge_cartridge_voice_grid, assets_screens_editor_cartridge_bank_slot_mapping, assets_screens_editor_cartridge_store_cartridge_in_bank, assets_screens_editor_cartridge_user_presets_option [INFERRED 0.85]
- **Sample chop workflow: load, slice, select, trim, export** — assets_screens_editor_chop_open_a_sound, assets_screens_editor_chop_chop_waveform_strip, assets_screens_editor_chop_keep_selection, assets_screens_editor_chop_chop_length_trim, assets_screens_editor_chop_send_to_usr_slot, assets_screens_editor_chop_download_wavs [INFERRED 0.85]
- **Texture Layer Parameters** — assets_screens_editor_midi_texture_texture_source, assets_screens_editor_midi_texture_texture_tone_filter, assets_screens_editor_midi_texture_texture_move, assets_screens_editor_midi_texture_texture_when, assets_screens_editor_midi_texture_texture_duck [INFERRED 0.85]
- **Ways to enter a step sequence** — assets_screens_editor_pianoroll_text_note_entry, assets_screens_editor_pianoroll_piano_roll_view, assets_screens_editor_pianoroll_midi_export_import [INFERRED 0.85]
- **4x4 grid mode screens (PUNCH/STEPS/KEY/ERASE/kit)** — assets_screens_screens_punch_screen, assets_screens_screens_steps_screen, assets_screens_screens_key_screen, assets_screens_screens_erase_screen, assets_screens_screens_drum_kit_screen, assets_screens_screens_four_by_four_pad_grid [INFERRED 0.85]
- **Track-colored screens (overview/mix/record)** — assets_screens_screens_track_overview_screen, assets_screens_screens_mix_screen, assets_screens_screens_loop_record_screen, assets_screens_screens_track_color_coding [INFERRED 0.85]
- **Loop recording UI flow: tracks -> rec ready -> count-in** — assets_screens_sloop_2_3_screens_tracks_screen, assets_screens_sloop_2_3_screens_rec_ready_screen, assets_screens_sloop_2_3_screens_count_in_screen, assets_screens_sloop_2_3_screens_loop_recording_flow [INFERRED 0.85]
- **Sloop sound engines shown in UI** — assets_screens_sloop_2_5_screens_phys_engine, assets_screens_sloop_2_5_screens_noise_engine, assets_screens_sloop_2_5_screens_fm6_engine, assets_screens_sloop_2_5_screens_synthesised_drum_kit [INFERRED 0.85]
- **MIDI configuration flow** — assets_screens_sloop_2_6_screens_glo_midi_screen, assets_screens_sloop_2_6_screens_glo_midi2_screen, assets_screens_sloop_2_6_screens_midi_learn_screen, assets_screens_sloop_2_6_screens_midi_learn_shortcut [INFERRED 0.85]
- **Shared page chrome (status bar, 4-param layout, footer)** — assets_screens_sloop_2_6_screens_status_bar, assets_screens_sloop_2_6_screens_four_param_page_layout, assets_screens_sloop_2_6_screens_page_footer_breadcrumb, assets_screens_sloop_2_6_screens_track_color_coding [INFERRED 0.85]
- **Per-step drum hit attributes (voice, level, roll)** — assets_screens_editor_drums_drum_step_grid, assets_screens_editor_drums_hit_velocity_levels, assets_screens_editor_drums_roll_ratchet, assets_screens_editor_drums_white_key_drum_mapping [INFERRED 0.85]
- **Drum voice synthesis signal chain** — assets_screens_editor_drumsynth_tone_section, assets_screens_editor_drumsynth_noise_section, assets_screens_editor_drumsynth_filter_section, assets_screens_editor_drumsynth_out_section [INFERRED 0.85]
- **Per-step edit via four encoders (sound/step/hit/level) on the grid cursor** — assets_screens_live_grid_sound_param, assets_screens_live_grid_step_param, assets_screens_live_grid_hit_param, assets_screens_live_grid_level_param, assets_screens_live_grid_step_cursor [INFERRED 0.85]
- **PWA Web App Icon Set** — docs_webapp_icon_192_icon_192, docs_webapp_icon_512_icon_512, docs_webapp_icon_maskable_512_icon_maskable_512, web_icon_192_icon_192, web_icon_512_icon_512 [INFERRED 0.85]
- **Shared screen chrome: 4x4 key grid + four colour-coded encoders** — assets_screens_sloop_screens_drums_grid_screen, assets_screens_sloop_screens_drums_kit_screen, assets_screens_sloop_screens_seq_layer_screen, assets_screens_sloop_screens_glo_layer_screen, assets_screens_sloop_screens_sel_layer_screen [INFERRED 0.85]
- **Step sequencer timing controls (div, swing, length)** — assets_screens_layer_steps_div_param, assets_screens_layer_steps_swing_param, assets_screens_layer_steps_steps_length_param [INFERRED 0.85]
- **Synth kit persistence/transfer actions** — assets_screens_editor_drumsynth_store_on_fm1, assets_screens_editor_drumsynth_use_on_drum_track, assets_screens_editor_drumsynth_save_open_file, assets_screens_editor_drumsynth_synth_kits_syn1_syn4 [INFERRED 0.85]
- **Backup-object transfer over BK_LIST/BK_GET/BK_PUT** — web_editor_backupcapture, web_editor_backuprestore, web_editor_bkreadobj, web_editor_bkwriteobj, web_editor_songcapture, web_editor_songload, web_editor_fm6cartwrite [INFERRED 0.85]
- **LIVE pro scene capture, recall and morph** — web_editor_lvxnow, web_editor_lvxstore, web_editor_lvxrecall, web_editor_lvxcross, web_editor_lvxsend, web_editor_lvx [INFERRED 0.85]
- **Live device sync: pushes, keep-alive, polling and reload** — web_editor_onpush, web_editor_keepalive, web_editor_maybereload, web_editor_aftersoundchange, web_editor_refreshstep, web_editor_selfload, web_editor_startwatch [INFERRED 0.85]
- **User sample pipeline (WAV -> 22050 Hz IMA ADPCM slot)** — web_editor_parsewav, web_editor_resample, web_editor_normalize, web_editor_matchgains, web_editor_withgain, web_editor_imaencode, web_editor_buildslot, web_editor_crc32, web_editor_chopzones, web_editor_kitzones [INFERRED 0.85]
- **Regression baselines: golden hashes, host CPU, target budget** — tests_golden_golden_renders, tests_cpu_baseline_host_cpu_baseline, tests_target_budget_felucca_target_cost_budget [INFERRED 0.95]
- **SLOOP Logo Master Assets** — assets_logo_sloop_icon_sloop_icon, assets_logo_sloop_logo_sloop_logo, assets_logo_sloop_splash_sloop_splash [INFERRED 0.95]
- **Samples/Kit/CHOP -> USR slot upload pipeline** — web_editor_smpsendpage, web_editor_kitsend, web_editor_chopsend, web_editor_smpupload, web_editor_buildslot, web_editor_smpinfo [INFERRED 0.95]

## Communities (213 total, 40 thin omitted)

### Community 0 - "Track State Struct"
Cohesion: 0.02
Nodes (91): track, aholdp, armp, arp_abs, arp_ch, arp_den, arp_idx, arp_new (+83 more)

### Community 1 - "editor_host.c"
Cohesion: 0.09
Nodes (15): frame(), audio_silence(), ed_inject(), fl_erase4k_quiet(), fl_erase4k_ram(), fl_prog_ram(), fl_read_ram(), fl_write() (+7 more)

### Community 2 - "ed_handle"
Cohesion: 0.14
Nodes (42): ed_dsyn_handle(), ed_dsyn_name(), ed_dsyn_store(), ed_b(), ed_backup(), ed_begin(), ed_bk_obj(), ed_bk_r32() (+34 more)

### Community 3 - "UI Drawing Primitives"
Cohesion: 0.11
Nodes (52): cv_text(), rgb565_over(), cv_icon(), engine_icon(), icon_for_label(), param_icon(), fmt_fix(), fmt_int() (+44 more)

### Community 4 - "Sequencer v2 Tests"
Cohesion: 0.12
Nodes (65): dstep_set(), arp_notes(), bar_run(), cc_push(), check(), count_note(), drdly_echo(), gated() (+57 more)

### Community 5 - "Main UI Step Editing"
Cohesion: 0.10
Nodes (66): felucca_init(), page_shown(), ml_code(), apply_preset(), apply_preset_to(), arp_is_sounds(), arp_param(), bank_resolve() (+58 more)

### Community 6 - "renderSamples"
Cohesion: 0.05
Nodes (62): addSmpFiles(), barFill(), CH (CHOP tool state), CHOP constants, chopAdd(), chopAudition(), chopBuffer(), chopChops() (+54 more)

### Community 7 - "Web Editor LIVE Strip"
Cohesion: 0.06
Nodes (63): LIVE computer keyboard shortcuts, LIVE newcomer guide, card help and tips, LIVE page (2.7, protocol v12), LIVE playlist / setlist (.sloopset), drumHear(), livePush(), LV (LIVE page state), LV_FX_GROUPS (LIVE effect pad groups) (+55 more)

### Community 8 - "Sample Pack Tooling"
Cohesion: 0.06
Nodes (21): main(), build(), Link, main(), pack7(), _channel_values(), _diff_np(), _diff_py() (+13 more)

### Community 9 - "Web Editor Sound & Mixer"
Cohesion: 0.06
Nodes (54): afterSoundChange(), buildGroups(), buildStrip(), choosePreset(), Mixer strips (TRACK_MIX / TRACK_PARAM, v3/v4), Sound page (parameter cards per device button), ctl (control map key -> input/out/desc), EXPECT (known P_COUNT/G_COUNT/P_E0 firmware layouts) (+46 more)

### Community 10 - "seq.c"
Cohesion: 0.08
Nodes (59): dstep_mask(), lvl_vel(), punch_fx_of_key(), audition_block(), audition_lane(), audition_req(), chord_mod_of_key(), chord_mods() (+51 more)

### Community 11 - "Project Capture & Apply"
Cohesion: 0.10
Nodes (59): memcmp(), memcpy(), memset(), fm1_main(), arrangement_save(), audio_quiet(), autosave_changed(), autosave_resume() (+51 more)

### Community 12 - "fm1_install.py"
Cohesion: 0.18
Nodes (8): handshake(), Identity, model_of(), pack7(), parse_identity(), parse_request(), response(), unpack7()

### Community 13 - "main.c"
Cohesion: 0.18
Nodes (19): fm1__dbg_lock(), fm1__dbg_unlock(), fm1_guard_enable(), fm1_guard_lock_top(), fm1_guard_pc_open(), fm1_guard_unlock_top(), fm1_sp(), fm1_ssp() (+11 more)

### Community 14 - "Studio Layer & Drum Screens"
Cohesion: 0.12
Nodes (51): dstep_t, drum_kit(), drum_set(), dstep_clr(), dstep_has(), dstep_lvl(), dstep_rat(), lane_of_key() (+43 more)

### Community 15 - "Web Editor Shell & Builds"
Cohesion: 0.06
Nodes (41): SLOOP Editor PWA build (docs/webapp/editor/index.html), Offline download link (sloop-editor-2.8.4.html), PWA install button (beforeinstallprompt handler), PWA manifest/theme/icon links (../sloop.webmanifest, icon-192.png), Service worker registration (../sw.js), SLOOP Editor standalone offline build (docs/webapp/editor/sloop-editor.html), Absolute GitHub Pages links (installer, FUKIAI-LICENSE.txt), Embedded Fukiai icon font (data:font/ttf base64) (+33 more)

### Community 16 - "FM6 Operator Core (msfa)"
Cohesion: 0.16
Nodes (25): fm6_carriers(), fm6_core_render(), fm6_env_advance(), fm6_env_get(), fm6_env_init(), fm6_env_key(), fm6_exp2(), fm6_freq() (+17 more)

### Community 17 - "UI Pages Tests"
Cohesion: 0.04
Nodes (30): swap16(), find_kit_g(), find_preset_g(), load(), main(), open_page(), put(), shot() (+22 more)

### Community 18 - "trk_note_off"
Cohesion: 0.13
Nodes (37): eng_sampled(), engine_block(), env_tick(), esync_coef(), esync_one(), glide_set(), glide_ticks(), lowest_held() (+29 more)

### Community 19 - "Firmware Build & Packaging"
Cohesion: 0.10
Nodes (17): build_app(), build_loader(), check(), crc16(), generate(), ldr_head(), ldr_wrap(), main() (+9 more)

### Community 20 - "HAL IRQ/Audio/Timer Headers"
Cohesion: 0.07
Nodes (29): fm1_adc_init(), fm1_adc_read(), fm1_audio_ack_aux(), fm1_audio_ack_half(), fm1_audio_free_half(), fm1_audio_init(), fm1_audio_pending(), fm1_audio_stop() (+21 more)

### Community 21 - "Hip-Hop Pack Generator"
Cohesion: 0.08
Nodes (27): tools/gen_builtin_hiphop.py (retune/cut/colour), build_pitched(), build_scratch(), detect_midi(), dusty(), fetch(), load(), main() (+19 more)

### Community 22 - "Mix Bus & Effects DSP"
Cohesion: 0.09
Nodes (42): trk_silent(), cpu1_ticks(), mulq16(), softclip(), slice_amp(), soft_knee(), cpu1_units_job(), crush_bits() (+34 more)

### Community 23 - "track_t"
Cohesion: 0.11
Nodes (37): track_t, phys_desc(), phys_note_on(), phys_poly(), phys_reset(), phys_slot_of(), phys_symp_pitches(), phys_render_draws() (+29 more)

### Community 24 - "Golden Renders & CPU Budgets"
Cohesion: 0.08
Nodes (44): BUDGET_UPDATE=1 rewrite flag, SLOOP host CPU baseline (per mille of idle+drums), CPU mix scenarios (idle, idle_drums, 3parts_*), drums/gm_kit golden render, ANALOG engine presets (22), DIGITAL engine presets (22), FM6 engine presets (8), GRAIN engine presets (8) (+36 more)

### Community 25 - "Note Length Tests"
Cohesion: 0.05
Nodes (14): block(), check(), dump(), ed_b(), ed_v(), gated_blocks(), live(), live5() (+6 more)

### Community 26 - "load"
Cohesion: 0.07
Nodes (39): applyLang(), auditionPatch(), bank (user preset bank ops), bankGet(), bankLoad(), buildUI(), FM6 cartridge store (ticked voices -> B1..Bn, optional user presets), Patch library (IndexedDB felucca-editor) (+31 more)

### Community 27 - "Site & Webfont Tooling"
Cohesion: 0.07
Nodes (17): Browser audio preview (Emscripten WASM), main(), fetch(), main(), tree(), main(), load(), main() (+9 more)

### Community 28 - "main"
Cohesion: 0.18
Nodes (18): song_backup(), song_restore(), fxa_end(), fxa_keep(), fxa_reset(), fxa_unkeep(), fxa_len(), fxa_put() (+10 more)

### Community 29 - "Engine Dispatch & Sample/Noise"
Cohesion: 0.08
Nodes (39): vmod_t, click_render(), amp_at(), blep(), mulq15(), osc_pulse(), osc_saw(), osc_sine() (+31 more)

### Community 30 - "PHYS Physical Modelling"
Cohesion: 0.17
Nodes (26): phys_render(), px_atan(), px_atan2t(), px_clamp(), px_csvf_coef(), px_csvf_pass(), px_exp2(), px_fasttan() (+18 more)

### Community 31 - "Host Regression Suite"
Cohesion: 0.13
Nodes (27): add(), blk(), chk_budget(), chk_hang(), chk_keep(), chk_keep_legato(), chk_keep_mono(), chk_keep_unison() (+19 more)

### Community 32 - "upreset.c"
Cohesion: 0.14
Nodes (36): kmac_rec_t, up_arp_of(), up_auto_name(), up_bank_check(), up_bank_find(), up_bank_ok(), up_boot(), up_can_save() (+28 more)

### Community 33 - "Web Editor Step & Drum Grid"
Cohesion: 0.08
Nodes (42): addLock(), bkReport(), Drum track 16-lane grid (v5 DRUM_STEP), MIDI file import/export (.mid), Step nudge, parameter locks and fill conditions (v7/v8), Piano roll view (SLOOP 2.5), Step sequencer (grid + step tables), download() (+34 more)

### Community 34 - "LocalPreview"
Cohesion: 0.17
Nodes (6): playPreview(), previewChanged(), renderPreviewSummary(), startPreview(), stopPreview(), LocalPreview

### Community 35 - "Wave/Drumkit Table Generators"
Cohesion: 0.20
Nodes (18): arr(), fm6_tables(), main(), cycle(), digi(), drum_clap(), drum_cowbell(), drum_cymbal() (+10 more)

### Community 36 - "Web Editor LIVE Pro (LVX)"
Cohesion: 0.08
Nodes (47): LIVE pro (scenes, morph, crossfader, PERFORM, MIDI learn, stage tools), Scenes with morph over bars and A/B crossfader, MIDI learn (data-lvm controls on any controller CC/note), PERFORM card (sound/arp/fx/steps of the target track), Set recording from FM-1 USB audio (AudioWorklet -> WAV), libInit(), LIVE ops table, LIVE page (2.7) (+39 more)

### Community 37 - "cpu1.c"
Cohesion: 0.18
Nodes (14): fm1_c1_mb_t, fm1_cpu1_bar(), fm1_cpu1_hold(), fm1_cpu1_run(), fm1_cpu1_start(), fm1_cpu1_wait(), cpu1_boot(), cpu1_label() (+6 more)

### Community 38 - "Hold Layers UI"
Cohesion: 0.13
Nodes (41): arrangement_ready(), section_bars(), ed_live(), punch_key(), kmac_desc(), kmac_ok(), lock_del(), lock_desc() (+33 more)

### Community 39 - "drums.c"
Cohesion: 0.11
Nodes (26): preview_hit(), expr_gain(), send_thr(), drum_audition_poll(), drum_on(), drum_pick(), drum_synth_on(), drum_tweaked() (+18 more)

### Community 40 - "Web Editor E2E Tests"
Cohesion: 0.14
Nodes (33): attachMock(), chopTests(), E, editor25(), editorBackup(), editorCart(), editorDsyn(), editorIcons() (+25 more)

### Community 41 - "req (request builders)"
Cohesion: 0.08
Nodes (32): ARR (song order codec), CMD command ids, Backup / restore and song file (.sloopsong) (v6), Song page (section order A..D via settings backup object 1), THEME page (firmware v11, backup object 11), getDesc(), getDescOrNull(), getDrumStep() (+24 more)

### Community 42 - "fm1_input.h"
Cohesion: 0.15
Nodes (28): fm1_enc_take(), fm1__frame(), fm1_input_edges(), fm1_input_init(), fm1_input_note_edges(), fm1_input_scan(), fm1_input_tick(), fm1__key() (+20 more)

### Community 43 - "FX 2.5.1 Tests"
Cohesion: 0.19
Nodes (32): lim_block(), esync_idx(), cc_in(), check(), d2_of(), fork_dry(), kick_hits(), main() (+24 more)

### Community 44 - "Guide: Layers & Recording"
Cohesion: 0.10
Nodes (28): CHORD+ (black keys change the chord), Clear track (hold REC), Count-in (REC START = count), Divisions (DIV), Fill (GLO + key 9 / 10), Fill conditions (FILL ONLY / NO FILL), FORCE and accent (synth note dynamics), Free take (loop follows you) (+20 more)

### Community 45 - "Slice Engine"
Cohesion: 0.16
Nodes (26): slc_bounds(), slc_bounds_v(), slc_count(), slc_dec_at(), slc_dec_next(), slc_dec_st(), slc_fill(), slc_fwd() (+18 more)

### Community 46 - "Punch-in FX Engine"
Cohesion: 0.13
Nodes (28): fx_buses(), beat_samples(), clk_samples(), punch_freeze_feed(), punch_key_of_fx(), punch_owns(), punch_process(), punch_ring_fx() (+20 more)

### Community 47 - "target_budget.py"
Cohesion: 0.38
Nodes (3): cost(), functions(), main()

### Community 48 - "Hold-Record Tests"
Cohesion: 0.26
Nodes (22): preview_note(), div_samples(), drum_input(), ft_note_on(), input_off(), input_on(), midi_drum_lane(), steps_clear() (+14 more)

### Community 49 - "main"
Cohesion: 0.54
Nodes (6): bytes_hash(), changed(), enc_of(), main(), snap(), turn()

### Community 50 - "OTA Update Session"
Cohesion: 0.18
Nodes (31): audio_silence(), fl_erase4k_quiet(), ota_erase(), ota_fread(), ota_in_area(), ota_now_ms(), ota_prog(), ota_show() (+23 more)

### Community 51 - "hostsim.c"
Cohesion: 0.10
Nodes (23): c1h_rand(), cpu1_host_init(), cpu1_host_jobs(), cpu1_host_thread(), cpu1_host_timeouts(), cpu1_on(), cpu1_run(), cpu1_wait() (+15 more)

### Community 52 - "editor_fuzz.c"
Cohesion: 0.19
Nodes (27): ep1_take(), after(), aud(), bk_read0(), bk_restore_ok(), boot(), dump(), eng_by_name() (+19 more)

### Community 53 - "preview.c"
Cohesion: 0.09
Nodes (9): cpu1_run(), preview_global(), preview_locks(), preview_param(), preview_render(), preview_sample(), preview_step(), preview_track() (+1 more)

### Community 54 - "host_tracks_init"
Cohesion: 0.17
Nodes (28): preset_extras(), demo(), host_preset(), host_preset_req(), host_tracks_init(), main(), put_step(), rec_test() (+20 more)

### Community 55 - "System Startup & Loader HAL"
Cohesion: 0.18
Nodes (24): fm1_core_reset(), fm1_cpu1_halt(), fm1_enter_uboot(), fm1_enter_update(), fm1_mailbox_clear(), fm1_p33_and(), fm1__p33_cs(), fm1__p33_op() (+16 more)

### Community 56 - "crc32"
Cohesion: 0.12
Nodes (26): Autosave, Backup and restore, b64dec(), b64enc(), backupCapture(), BackupError, backupObjects(), backupRestore() (+18 more)

### Community 57 - "console.c"
Cohesion: 0.37
Nodes (17): fm1_mem_readable(), cdc_task(), con_crash(), con_dbg(), con_dec(), con_exec(), con_flr(), con_hex() (+9 more)

### Community 58 - "ed_bk_commit"
Cohesion: 0.13
Nodes (21): dsu_fix_kit(), dsu_kit(), dsu_valid(), ed_bk_commit(), fm6_bank_boot(), fm6_bank_changed(), fm6_bank_flash(), fm6_bank_get() (+13 more)

### Community 59 - "Flash Driver HAL"
Cohesion: 0.23
Nodes (25): fl_addr(), fl_cache_idle(), fl_cs(), fl_csync(), fl_delay(), fl_enter(), fl_erase4k(), fl_erase4k_ram() (+17 more)

### Community 60 - "FM6 Engine Tests"
Cohesion: 0.27
Nodes (21): fm6_unpack(), algorithms(), ams(), bank(), centroid(), centroid_of(), check(), cost() (+13 more)

### Community 61 - "Song Screen UI"
Cohesion: 0.10
Nodes (6): song_sane(), song_screen_input(), cur_page(), main(), press(), ui_message()

### Community 62 - "Menus & Panel Palette"
Cohesion: 0.20
Nodes (18): fm1_led_key(), theme_shown(), lights_from_word(), lights_word(), panel_btn_of(), panel_enc(), panel_init(), panel_led() (+10 more)

### Community 63 - "usb.c"
Cohesion: 0.09
Nodes (55): fm1_usb_attach(), fm1_usb_ep0_buf(), fm1_usb_ep0_send(), fm1_usb_ep4_send(), fm1_usb_ep4_txbuf(), fm1_usb_ep_enable(), fm1_usb_ep_rxbuf(), fm1_usb_ep_send() (+47 more)

### Community 64 - "Arp & Scale Logic"
Cohesion: 0.14
Nodes (25): div_units(), arp_end(), arp_tick(), clkout_block(), grid_at(), grid_den(), grid_swing(), kh_any() (+17 more)

### Community 65 - "Visualiser Animations"
Cohesion: 0.12
Nodes (43): cv_blit_from(), cv_line(), cv_pset(), cv_rect(), rgb565_ch(), rgb565_scale(), te_gray(), theme_apart() (+35 more)

### Community 66 - "Slicer Track"
Cohesion: 0.23
Nodes (20): sl_enter(), sl_pattern(), sl_seg(), slicer_busy(), slicer_start(), slicer_track(), check(), cost_run() (+12 more)

### Community 67 - "The drum track (track 4)"
Cohesion: 0.21
Nodes (11): Choke (hats cut open hat), DR MAP (MIDI drum mapping), DRUM PREVIEW setting, DRUMS Sound page (per-sound TUNE / DECAY), The drum track (track 4), The DRUMS screen, Four tracks (3 synth, 1 drum), Drum kits (+3 more)

### Community 68 - "The HOME menu"
Cohesion: 0.28
Nodes (8): The HOME menu, KNOB ACCEL (knob acceleration), The lights (button and key LEDs), Master limiter, SPEAKER LOWCUT, Troubleshooting, USB audio (Felucca input), USB RATE

### Community 69 - "Step Recording"
Cohesion: 0.15
Nodes (31): step_t, chain_end(), chain_notes(), cont_notes(), hold_marker_clear(), hold_merge(), hold_only(), hold_restart() (+23 more)

### Community 70 - "Flash Storage & CRC"
Cohesion: 0.16
Nodes (27): st_prog(), st_read(), st_body(), st_crc32(), st_current(), st_head(), st_load(), st_prog_n() (+19 more)

### Community 71 - "Screens 2.6 Overview"
Cohesion: 0.17
Nodes (18): Sloop 2.6 Screens Overview (screenshot grid), Track engine types (ANALOG, DIGITAL, DRUMS), FREEZE punch effect (held), FX -> INSERT Screen (PHASR rate/depth/feedback), GLO -> MIDI 2 Screen (IN/OTHER/OUT/pitch bend range), GLO -> MIDI Screen (per-track MIDI channels), GLO -> TEXTURE Screen (vinyl bed src/level/tone/move), LFO -> LFO 2 Screen (sync/trig/polarity waveform) (+10 more)

### Community 72 - "Bootloader Package Reader"
Cohesion: 0.14
Nodes (21): ldr_chip_key(), ldr_pass(), ldr_records_drop(), ldr_session(), ldr_sfc(), ldr_cstart(), ldr_erase(), ldr_flash_known() (+13 more)

### Community 73 - "GRAIN Engine"
Cohesion: 0.25
Nodes (18): gr_build(), gr_dec(), gr_fill(), gr_find(), gr_nz(), gr_reset(), gr_rnd(), gr_run() (+10 more)

### Community 74 - "Guide: Sound Bank & Presets"
Cohesion: 0.22
Nodes (18): ANALOG FILTER page (LP / BP / HP), ANALOG engine, DIGITAL engine (4-op FM), FM6 engine (6-op FM, DX7), GRAIN engine (granular), LOFI engine (8-bit chip), NOISE engine, PHASE engine (phase distortion) (+10 more)

### Community 75 - "Loader Wire Tests"
Cohesion: 0.11
Nodes (7): check(), load_logical(), main(), ota_wire_send(), pack7(), put_record(), unpack7h()

### Community 76 - "gen_samples.py"
Cohesion: 0.08
Nodes (17): best_loop_start(), break_loop(), Builder, cc0_entries(), gm_kit_entry(), gm_kit_sources(), gm_role(), ima_states() (+9 more)

### Community 77 - "Sample Credits & Licences"
Cohesion: 0.25
Nodes (19): Creative Commons Attribution 3.0, Greg Sullivan Wurlitzer EP200 samples (CC BY 3.0), SLOOP Hip-Hop Pack (USR1..USR3 sounds), User sample slots USR1..USR3, SAMPLE engine built-in sets source map, CC0 1.0 Universal (public domain dedication), Sonic Pi sample set (freesound.org CC0), VCSL - Versilian Community Sample Library (+11 more)

### Community 78 - "Live Tracks Screenshot"
Cohesion: 0.13
Nodes (20): Live Tracks Screen (screenshot), Encoder Parameter Row, Global Record Indicator, Header Bar (BPM / Transport / Record), Level Parameter (81), Pan Parameter (0), Playhead Marker, 16-Step Pattern Strip (+12 more)

### Community 79 - "Installer Page Updater"
Cohesion: 0.20
Nodes (19): fail(), handshake(), Install button click handler, Link (MIDI in/out SysEx queue), Link.read(), Link.send(), parseIdentity(), parseRequest() (+11 more)

### Community 80 - "Guide: Punch-in FX & Signal Path"
Cohesion: 0.16
Nodes (18): Black-key punch-in effects (KILL LOW/MID/HIGH, REWIND, OCT UP, FLANGER, AUTO-PAN, FREEZE, LOOP 8T, MONO, FADE OUT), Chorus, Delay (DLY, global tempo delay), DUCK (sidechain from kick), DUST (master), FILT (master DJ filter), FILTER RESO (per-track filter resonance), FX layer (punch-in) (+10 more)

### Community 81 - "Song Arm Tests"
Cohesion: 0.09
Nodes (12): arr_begin(), arr_defaults(), arr_drop_scene(), arr_elapse(), arr_next(), arr_valid(), arrangement_start(), main() (+4 more)

### Community 82 - "OTA JS Updater"
Cohesion: 0.21
Nodes (6): fail(), handshake(), IS_OTA(), Link, sleep(), Updater

### Community 83 - "Screens Overview (classic)"
Cohesion: 0.15
Nodes (17): Drum Grid Screen (TECHNO pattern grid), Drum Kit Screen (ACOUSTIC kit pads), Drum Voices (kick, kick2, snare, clap, hat, open, pedal, rim, snr2, tom l, tom h, crash, ride, shake, conga, bell), ERASE Screen (per-voice erase, oct-/undo), Felucca (upstream project sloop is based on), FX Send Screen (DST/CHO/DLY/REV), KEY Screen (key/scale/chord/transpose), Loop Record Screen (free take, count-in, bars, rec/play) (+9 more)

### Community 84 - "Screens 2.3 Overview"
Cohesion: 0.14
Nodes (19): SLOOP 2.3 Screens Overview (image), ABOUT Screen (SLOOP 2.3 credits and licenses), Analog engine - WARM PAD, COUNT-IN Screen (one bar of clicks, big countdown digit, rec cancels), Digital engine - M1 PIANO, Drums engine - HOUSE drums, Felucca (upstream firmware SLOOP is based on), Four-Track Engine (wheel organ, digital FM piano, analog pad, drums) (+11 more)

### Community 85 - "load_package"
Cohesion: 0.18
Nodes (6): _crc16(), _dec(), load_package(), logical_image(), package_damage(), product_of()

### Community 86 - "Preview Worklet Tests"
Cohesion: 0.14
Nodes (6): E, html, proto, render(), FirmwareAudio, SloopProcessor

### Community 87 - "Sloop Screens Overview"
Cohesion: 0.21
Nodes (19): Sloop Screens Overview (screenshot sheet), 4x4 Key Grid UI Pattern (16 pads mirror the 16 hardware keys), Drums: Grid Screen (16 lanes, keys are steps; BPM 92, Boombap kit 13, Sound/Step/Hit/Level encoders), Drums: Kit Screen (16 kit sounds: kick..bell; Kit/Level/Reverb/Pan encoders), FM6 Engine Screen (six-operator FM, DX7 patches 'Tine EP': ALG, FB, MLVL, MRAT; OPS 1/4 pages), Four Colour-Coded Encoder Footer (blue/green/yellow/orange knobs mapped to on-screen params), GLO Layer / Mix Screen (mute 1-4, solo 1-4, fill, bar, tap tempo, four track levels), Held-Key Layers (SEQ, GLO, SAVE, SEL) (+11 more)

### Community 88 - "OTA Wire Tests"
Cohesion: 0.14
Nodes (10): area_erased(), check(), host_reply(), main(), ota_wire_send(), pack7(), reset_dev(), unpack7h() (+2 more)

### Community 89 - "Web Editor SYN Drum Kits"
Cohesion: 0.18
Nodes (18): DRUM SYNTH page (firmware v10, SYN1..SYN4), Drum synth page (SYN kits), DS (DRUM SYNTH page state), DS_GROUPS (drum synth parameter groups), dsDefault(), dsDirty(), dsFlush(), dsKnob() (+10 more)

### Community 90 - "LCD Driver"
Cohesion: 0.27
Nodes (16): fm1_lcd_backlight_on(), fm1_lcd_baud(), fm1_lcd_deselect(), fm1_lcd_hw_init(), fm1_lcd_send_cmd(), fm1_lcd_send_data(), fm1_lcd_wait(), lcd_blit() (+8 more)

### Community 91 - "voice_t"
Cohesion: 0.17
Nodes (19): voice_t, analog_spread(), digital_spread(), fm6_done(), fm6_note_of(), fm6_part_of(), fm6_render(), fm6_spread() (+11 more)

### Community 92 - "Logo Generator"
Cohesion: 0.20
Nodes (14): assets(), draw_icon(), draw_word(), cap(), line(), render(), rgb565(), rrect() (+6 more)

### Community 93 - "Installer Page & Fonts"
Cohesion: 0.15
Nodes (16): Dimitar Toshkov Zhekov (Terminus author), retro-vault/font-vault (Terminus source), SIL Open Font License 1.1, Terminus Font (ter-u16n / ter-u16b BDF, 4.48), docs index redirect to webapp/installer/, Fukiai icon font (fukiai.ttf, MIT, Hugelton Instruments), MIT License, Feature summary: 12 engines, 153 sounds, 37 kits, 27 punch-in FX (+8 more)

### Community 94 - "main"
Cohesion: 0.52
Nodes (6): preset_t, bent(), dft(), f0_of(), main(), pitched()

### Community 95 - "rn"
Cohesion: 0.32
Nodes (18): bk_restore(), cmd_rand(), cmdv(), flash_random(), fz_seq_step(), mutate(), pack7(), proj_random() (+10 more)

### Community 96 - "fm1ota.js"
Cohesion: 0.19
Nodes (11): unpack7(), HS_QUERY, OUR_LOADER(), pack7(), parseIdentity(), parseRequest(), response(), unpack7() (+3 more)

### Community 97 - "Editor Sound Screenshot"
Cohesion: 0.19
Nodes (14): Editor Sound Screenshot, ADSR Envelope, Delay Section (DLY), Envelope Destinations, ENV Panel (3 pages), Filter Section (FILT), FX Panel (7 pages), FX Sends (DST/CHO/DLY/REV) (+6 more)

### Community 98 - "Live Grid Screenshot"
Cohesion: 0.17
Nodes (15): Live Grid Screen (screenshot), Encoder Parameter Row, Genre Style Label (hip hop), Hit Parameter (on), Drum Kit Name (808), Level Parameter (soft), Loop Indicator with Bar Meter, Pattern/Slot Number Badge (6) (+7 more)

### Community 99 - "Screens 2.5 Overview"
Cohesion: 0.18
Nodes (14): Sloop 2.5 Screens (UI screenshot sheet), Drum reverb/delay sends, DRUMS: KIT SYN1 screen, DX7 cartridge as user presets, FM6 engine, GLO -> DRUMS page, NOISE engine, NOISE engine page (+6 more)

### Community 100 - "Drum Synth Voices"
Cohesion: 0.23
Nodes (14): preview_kit(), ds_alive(), ds_blocks(), ds_control(), ds_filter(), ds_inc(), ds_k32(), ds_lane() (+6 more)

### Community 101 - "main"
Cohesion: 0.62
Nodes (6): check(), compare(), key_check(), key_note(), main(), pitch_check()

### Community 102 - "Project Format Tests"
Cohesion: 0.30
Nodes (10): pt_get(), check(), fill_old_steps(), fill_v2_track(), fill_v3_track(), main(), oldv(), steps_ok() (+2 more)

### Community 103 - "UI Stress & Bench Tests"
Cohesion: 0.32
Nodes (14): vis_open(), vis_shown(), bench_blocks(), bench_draw(), chord_steps(), font_ref_build(), main(), rn() (+6 more)

### Community 104 - "INFO command (version discovery)"
Cohesion: 0.47
Nodes (6): Drum track (16 sounds), INFO command (version discovery), v2: user presets, v3: four tracks, v4: any track's parameters, v5: drum lanes, levels, ratchets

### Community 105 - "Drum Synth Editor Screenshot"
Cohesion: 0.22
Nodes (14): Drum Synth editor screenshot, Kit CRUSH and S&H Controls, Drum Synth Editor Page, Drum Voice Grid (16 sounds), FILTER Parameters (filter, on, cutoff, res, env), NOISE Parameters (noise, clap, level, hold, decay, HPF, chip), OUT Parameters (drive, level dB), Play / Play on Change Audition (+6 more)

### Community 106 - "TRIO Engine"
Cohesion: 0.33
Nodes (13): osc_tri(), trio_blep(), trio_frac(), trio_inc(), trio_naive(), trio_note_on(), trio_pass(), trio_ps() (+5 more)

### Community 107 - "main"
Cohesion: 0.18
Nodes (16): fx_side_read(), fxside_sum(), kmside_sum(), persist_boot(), side_get(), side_hash(), harness_init(), check() (+8 more)

### Community 108 - "kmac_test.c"
Cohesion: 0.28
Nodes (15): kmac_pos_set(), kmac_set(), kmac_sync(), blk_rms(), check(), child(), main(), old_step() (+7 more)

### Community 109 - "MIDI & Texture Screenshot"
Cohesion: 0.18
Nodes (11): Editor MIDI & Texture Screens Screenshot, Per-Track MIDI Channel Assignment (CH1-CH4), MIDI OTHER Setting (OFF), MIDI Editor Page, Pitch Bend Range (BEND +12 st), Texture Ducking (DUCK: ON), Texture Movement (MOVE / RATE 4BAR), Texture Editor Page (+3 more)

### Community 110 - "Installer Package Template"
Cohesion: 0.22
Nodes (11): .fwsc package (20 marker bytes, product identity), logicalImage(), meta: version 2.8.4, product FM-1_900, firmware/sloop-2.8.4.fwsc + sha256, package loader IIFE (fetch + sha256 check), productOf(), validateStockPackage(), applyLang() (template), Template placeholders: LOGO, STUDIO_GUIDE, BANNER, /*LIB*/, /*META*/ (+3 more)

### Community 111 - "The web editor"
Cohesion: 0.13
Nodes (21): Backup and restore, Bank Select (CC 0), CHOP (chop a recording), DX7 / SysEx patches (FM6 bank), Editor protocol (EDITOR_PROTOCOL.md), Favourites (FAV), M-VAVE FM-1 (hardware groovebox), Hardware calibration (+13 more)

### Community 112 - "Guide: MIDI & Sync"
Cohesion: 0.20
Nodes (14): ARP modes, Arpeggiator, Expression (CC 11), Felucca (base firmware), FX CH (punch-in over MIDI), KBD HOLD (latch without arp), MIDI, MIDI CCs (+6 more)

### Community 113 - "Guide: Song Mode & Sections"
Cohesion: 0.22
Nodes (12): Autosave, LIVE page (editor), Song files (.sloopsong) and LIVE playlist, Quick chain, SAVE layer (song), SAVE TOOLS (CLRSQ, INIT, NEW loop), Sections A-D, Song mode (+4 more)

### Community 115 - "Piano Roll Screenshot"
Cohesion: 0.24
Nodes (10): Editor Piano Roll Screenshot, Grid / Piano Roll View Toggle, MIDI Export / Import, Note Length Selector (1/1 to 1/16), Octave Down/Up Range Control (D#2 - D#4), Parameter Locks, Piano Roll View, Step Inspector (Step / Nudge / Fill) (+2 more)

### Community 116 - "Punch Layer Screenshot"
Cohesion: 0.21
Nodes (9): Punch Layer Screen (loop16 active), Duck Knob (0), Dust Knob (0), Filter/Tone Effects (low, high, phone, crush), Filter Knob (off), Loop Repeat Effects (loop 4/8/16/32), Punch FX 4x4 Pad Grid, Texture Effects (alias, gate, echo, wobble) (+1 more)

### Community 118 - "eng_fm6.c"
Cohesion: 0.22
Nodes (13): preview_fm6(), preview_init(), fm6_init(), fm6_load_slot(), fm6_max(), fm6_pack(), fm6_poll(), fm6_sanitize() (+5 more)

### Community 119 - "is_drum"
Cohesion: 0.14
Nodes (48): is_drum(), ft_owns_press(), cur_page(), cursor_fix(), cursor_set(), home_param(), accel(), btn_hold() (+40 more)

### Community 120 - "Project Overview & Engines"
Cohesion: 0.23
Nodes (11): SLOOP (project overview), Twelve synthesis engines, msfa / Dexed FM core, Felucca (base firmware), M-VAVE FM-1 hardware, FM6 (six-operator FM / DX7), NOISE engine, PHYS (physical models) (+3 more)

### Community 121 - "Layer System Overview"
Cohesion: 0.17
Nodes (12): ARP layer (note repeat/roll), CHORD+ (chords on keys), EDIT layer (erase), FX layer (punch-in), GLO layer (mix), Layer system (tap/hold), Master DUST / DUCK / FILT, Punch-in effects (27) (+4 more)

### Community 122 - "Cartridge Import Screenshot"
Cohesion: 0.25
Nodes (10): Editor Cartridge Screen (screenshot), Cartridge Voice Grid (32 voices), DX7 32-Voice Cartridge (.syx bulk dump), FM-1 PRESETS / SELECT Controls, Init Voice, Selection Shortcuts (first 27 / none), Store Cartridge in Bank (27 -> b1-b27), SysEx Import/Export Toolbar (+2 more)

### Community 123 - "recovery_test.c"
Cohesion: 0.09
Nodes (12): fm1_wdt_feed(), fm1_usb_off(), bootguard_begin(), bootguard_clear(), bootguard_manual(), ota_commit(), ota_idle(), recovery_key() (+4 more)

### Community 124 - "PWA Tests"
Cohesion: 0.20
Nodes (3): launch, serve(), sleep()

### Community 125 - "Release Notes 2.6-2.8"
Cohesion: 0.18
Nodes (10): INSERT effect (per track), MIDI in (TRS jack + USB, per-track channels), MIDI LEARN, NOTES piano-roll editor, TEXTURE (looping bed), SLOOP 2.6, SLOOP 2.7, SLOOP 2.8 (+2 more)

### Community 126 - "FM6 Patch Generator"
Cohesion: 0.24
Nodes (5): c_rows(), js(), main(), pack(), voice()

### Community 127 - "Parameter Icon Atlas"
Cohesion: 0.22
Nodes (9): Effect Icons (dist, drive, fold, bits, chorus, delay, reverb, feedback), Engine/Instrument Icons (chip, midi, tape, drum, mouth, trio, drawbar, slice, grain, sample), Envelope ADSR Icons (attack/decay/sustain/release/env), File Action Icons (save/load/clear), Filter Icons (cutoff/reso), Parameter Icon Atlas (icons.png), LFO Waveform Glyphs (w_sin, w_tri, w_saw, w_sqr, w_pls, w_pwm, w_sh, w_dsin, w_spls, w_rsaw, w_rtri, w_rtrp), Oscillator/Pitch Icons (wave, pulse, shape, pitch, tune, detune, transpose, octave) (+1 more)

### Community 128 - "Backup Screenshot"
Cohesion: 0.24
Nodes (10): Editor Projects & Backup Screen, Backup Panel (Save / Restore), Device Settings (colours, calibration, song, lights), FM-1 Device, Full Device Backup File, Project (whole device state), Projects Panel (4 slots Load/Save), Song Sections A-D (+2 more)

### Community 129 - "Chop Editor Screenshot"
Cohesion: 0.33
Nodes (8): Editor Chop Screenshot, CHOP Editor Panel, Per-Chop Length Trim, Chop Waveform Strip, Download WAVs Export, Fit to Slot, Open a Sound (load sample), Send to USR1/USR2/USR3 Slots

### Community 130 - "Drum Sequencer Screenshot"
Cohesion: 0.27
Nodes (10): Drum Sequencer Editor Screenshot, Drum Kit Selector (808), Drum Step Grid (16 voices x 16 steps), Hit Velocity Levels (GHOST, SOFT, NORM, HARD), Reload / Clear Sequence Actions, Roll / Ratchet (x1-x4), SEQ Pattern Parameters (LEN, DIV, SWG, GATE), Sequencer Tab (Web UI) (+2 more)

### Community 133 - "SEL layer (key and chords)"
Cohesion: 0.23
Nodes (14): ARP layer (note repeat / roll), Chord mode (one finger, one chord), Drum MUTE mode (EDIT + black key), EDIT layer (erase), GLO layer (mix), Key of the song, KEYS setting (OFF, SNAP, WHITE), Lock a layer open (+6 more)

### Community 134 - "Editor Protocol & Preview Docs"
Cohesion: 0.22
Nodes (8): Local audio preview (WebAssembly DSP), Host test suite (run_tests.sh), Web editor (README), The visualiser, The web editor, frame(), Frame framing (F0 7D 46 4C ...), SLOOP editor protocol (SysEx over USB-MIDI)

### Community 135 - "Font Rendering Tests"
Cohesion: 0.33
Nodes (6): bdf_read(), capital(), check(), hash_cv(), main(), render_all()

### Community 136 - "SLOOP Brand Identity"
Cohesion: 0.47
Nodes (9): SLOOP Brand Identity, SLOOP Icon (PNG), SLOOP Logo (PNG), SLOOP Splash Screen, Webapp Icon 192 (docs), Webapp Icon 512 (docs), Webapp Maskable Icon 512 (docs), Web Icon 192 (+1 more)

### Community 137 - "Dual-Core & RAM Branches"
Cohesion: 0.14
Nodes (14): 2ND CORE dual-core audio (2.7 FR), 2ND CORE menu switch, dualcore branch of sloop-lab, Felucca, .lowram SRAM section (patch 5), mix_block render split, Second-core audio render, SLOOP firmware (+6 more)

### Community 138 - "param_desc_t"
Cohesion: 0.44
Nodes (7): param_desc_t, ins_desc(), kmac_label(), names_turn(), page_desc(), page_for_drum(), track_desc()

### Community 139 - "Bitmap Font Generator"
Cohesion: 0.36
Nodes (4): main(), render(), render_bdf(), upscale()

### Community 140 - "fm1pkg_make.py"
Cohesion: 0.22
Nodes (10): chipkey_decode(), crc16(), enc(), entry(), flash_image(), key_blob(), main(), sdk_file() (+2 more)

### Community 142 - "FM1 Package Validation"
Cohesion: 0.33
Nodes (8): logicalImage(), productOf(), sha256hex(), STOCK_V15_PRODUCT, STOCK_V15_SHA256, STOCK_V15_SIZE, validateStockPackage(), packages()

### Community 143 - "FM6 module (6-op voice pack/unpack, SysEx, bank)"
Cohesion: 0.18
Nodes (14): FM6 patch editor (firmware v9, SysEx import/export), FM6 module (6-op voice pack/unpack, SysEx, bank), fm6Follow(), fm6ImportFile(), fm6Num(), fm6ReadTrack(), fm6Sel(), fm6Send() (+6 more)

### Community 144 - "Build & Install Docs"
Cohesion: 0.22
Nodes (9): JieLi AC79 SDK, FELUCCA build flags, build.sh build process, Docker linux/amd64 build container, tools/fm1_install.py CLI installer, felucca.fwsc installable package, INSTALL-SLOOP.bat (Windows/WSL), JieLi clang toolchain (pi32v2) (+1 more)

### Community 145 - "noise32"
Cohesion: 0.18
Nodes (12): noise32(), tsvf_coef(), tsvf_lp(), isqrt32(), noise_desc(), noise_inc(), noise_inc64(), noise_note_on() (+4 more)

### Community 146 - "Release Notes 2.0-2.3"
Cohesion: 0.33
Nodes (6): MIDI clock in (SYNC), USB audio input (Felucca), SLOOP 2.0, SLOOP 2.1, SLOOP 2.2, SLOOP 2.3

### Community 147 - "sample_pitch_test.c"
Cohesion: 0.46
Nodes (7): fft(), grain_rate(), main(), peak_shift(), render(), sample_capped(), shift()

### Community 148 - "Web Editor Drum Panel"
Cohesion: 0.46
Nodes (8): Drum track sound panel (2.7, LIVE op 12), DP (drum panel state), drumPanel(), drumPanelBuild(), drumPanelMerge(), drumPanelRead(), drumPanelRender(), drumPanelTw()

### Community 149 - "Steps Layer Screenshot"
Cohesion: 0.38
Nodes (7): div parameter (1/16 clock division), Encoder Knob Parameter Row, sound parameter (snare), 16-Step Sequencer Grid (4x4), STEPS Layer Screen (track 4), steps parameter (pattern length 16), swing parameter (50%)

### Community 150 - "Dual-Core Render Units"
Cohesion: 0.15
Nodes (11): regress.c regression suite + golden.txt, tests/run_tests.sh host test suite, Per-unit accumulator set, cpu1.h API (cpu1_run/cpu1_wait/cpu1_on), FM6 per-part operator buses (fm6_part_t), Golden render hashes, Host double of core 1 (cpu1_host.c), Render units (mix_part/mix_drums/mix_units) (+3 more)

### Community 151 - "InstallError"
Cohesion: 0.22
Nodes (3): InstallError, not_found(), Updater

### Community 152 - "midi_uart_test.c"
Cohesion: 0.24
Nodes (11): midi_in_event(), sysex_byte(), check(), dma_put(), drain(), feed(), main(), ring_clean() (+3 more)

### Community 153 - "Protocol v9-v12 Features"
Cohesion: 0.17
Nodes (12): Editor LIVE page, CHOP (recording slicer), Drum kits (37 + user), SYN1-SYN4 synthesised drum kits, User samples (USR1-USR4), pack7(), pack7 encoding, User sample slot format (FSMP / ADPCM) (+4 more)

### Community 154 - "gen_drumkits.py"
Cohesion: 0.23
Nodes (9): cut(), dec(), enc(), kit(), main(), note(), note16(), punch() (+1 more)

### Community 155 - "mix_block"
Cohesion: 0.24
Nodes (11): mix_block(), hold(), main(), reset(), mag_at(), main(), ok(), has() (+3 more)

### Community 156 - "User Kit Tests"
Cohesion: 0.57
Nodes (6): check(), drum_voice_on(), main(), quiet(), run_peak(), slot_build()

### Community 157 - "eq"
Cohesion: 0.24
Nodes (6): chopAttack(), chopHits(), editorMock(), eq(), samplesMatch(), wav()

### Community 158 - "main"
Cohesion: 0.32
Nodes (10): check(), ed_b(), ed_pack7(), ed_str(), ed_unpack7(), hit_render(), lanes_same(), main() (+2 more)

### Community 159 - "SLOOP quickstart (FR)"
Cohesion: 0.16
Nodes (14): FM6 engine / DX7 patches (FR), Calques (hold layers), MIDI clavier / canaux (FR), SLOOP quickstart (FR), USB audio input (Felucca), Web editor (FR), CrispyZebra (PHASE engine port), DaisySP / Rings sympathetic strings (PHYS) (+6 more)

### Community 160 - "Core-1 HAL & Credits"
Cohesion: 0.40
Nodes (5): Andre Rezemini, Charles Vestal, hal/fm1_cpu1 HAL, Melodee, X0X (fm1-x0x)

### Community 161 - "Guide: ENV & LFO"
Cohesion: 0.33
Nodes (6): ENV (envelope) page, ENV DEST, ENV SYNC (ESYNC), LFO page, LFO DEST page, LFO SYNC (LFO 2)

### Community 162 - "Chop Attack Tests"
Cohesion: 0.60
Nodes (5): block(), check(), main(), run(), voice_of()

### Community 163 - "midi_uart.c"
Cohesion: 0.33
Nodes (7): fm1_uart1_midi_init(), fm1_uart1_rx_take(), uart_midi_init(), uart_midi_poll(), um_byte(), um_drain(), um_len()

### Community 164 - "msfa Apache-2.0 license notice"
Cohesion: 0.38
Nodes (9): Apache License 2.0, Grant of Copyright License, Dexed, fm6_core.c integer C port, msfa (Dexed synthesis core), msfa Apache-2.0 license notice, Grant of Patent License (with litigation termination), Redistribution conditions (notices, NOTICE file) (+1 more)

### Community 165 - "drum_steal_test.c"
Cohesion: 0.60
Nodes (3): block(), main(), run_kit()

### Community 166 - "run()"
Cohesion: 0.70
Nodes (4): check(), fit_left(), main(), run()

### Community 167 - "run_tests.sh"
Cohesion: 0.50
Nodes (3): AC79_SDK, run(), run_tests.sh script

### Community 168 - "build.sh"
Cohesion: 0.50
Nodes (3): AC79_SDK, JIELI_TOOLCHAIN, build.sh script

### Community 170 - "cpu1_modes.sh"
Cohesion: 0.83
Nodes (3): golden(), cpu1_modes.sh script, split()

### Community 171 - "render"
Cohesion: 0.38
Nodes (8): cpu1_host_mode(), child(), chords(), drums_pattern(), main(), render(), scene_block(), scene_setup()

### Community 202 - "ui_frame"
Cohesion: 0.47
Nodes (9): audio_blocks(), ui_frame(), ed(), main(), midi(), pack7(), repro_pc(), repro_root() (+1 more)

### Community 203 - "eng_sample.c"
Cohesion: 0.33
Nodes (8): pow2_q16(), sample_next(), sample_note_on(), sample_render(), sample_spread(), smp_user_scan(), smp_zone(), smp_zone_ok()

### Community 204 - "SLOOP 2.4"
Cohesion: 0.31
Nodes (9): Fill conditions, Micro timing (nudge), Parameter locks, SEQ layer (step sequencer), SLOOP 2.4, FC fill conditions + fillGet/fillSet, lockable(), v7: step nudge and parameter locks (+1 more)

### Community 205 - "fm6_sync"
Cohesion: 0.36
Nodes (7): fm6_block(), fm6_note_on(), fm6_sync(), fm6_lfo_delay(), fm6_lfo_key(), fm6_lfo_reset(), fm6_lfo_sample()

### Community 207 - "FakeFM1"
Cohesion: 0.11
Nodes (11): against_js(), cli(), errors(), boot(), FakeFM1, FakeLink, installs(), ok() (+3 more)

### Community 210 - "events_block"
Cohesion: 0.12
Nodes (24): arrangement_apply(), click_on(), vel_lvl(), aclk_block(), arm_start(), click_tick(), events_block(), ft_block() (+16 more)

### Community 213 - "core.h"
Cohesion: 0.29
Nodes (7): dly_samples(), dly_units(), engine_t, plock_t, song_t, delay_samples(), cc74_slot()

## Ambiguous Edges - Review These
- `SLOOP firmware` → `Editor protocol (EDITOR_PROTOCOL.md)`  [AMBIGUOUS]
  GUIDE.md · relation: conceptually_related_to
- `USB audio input (Felucca)` → `Browser audio preview (Emscripten WASM)`  [AMBIGUOUS]
  DEMARRAGE-RAPIDE-FR.md · relation: conceptually_related_to
- `SG (Song page state)` → `songLoadUI()`  [AMBIGUOUS]
  web/editor.html · relation: shares_data_with
- `drumHear()` → `LV (LIVE page state)`  [AMBIGUOUS]
  web/editor.html · relation: shares_data_with
- `Encoder Parameter Row` → `Track 2: RHODES (digital, green, selected, rec-armed)`  [AMBIGUOUS]
  assets/screens/live-tracks.png · relation: conceptually_related_to
- `Punch-in Effects (loop4/8/16/32, stutt, rev, stop, half, low, high, phone, crush, alias, gate, echo, wobble)` → `Loop Record Screen (free take, count-in, bars, rec/play)`  [AMBIGUOUS]
  assets/screens/screens.png · relation: conceptually_related_to

## Knowledge Gaps
- **252 isolated node(s):** `JIELI_TOOLCHAIN`, `AC79_SDK`, `p`, `engine`, `preset` (+247 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 817 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **40 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `fm6_core.c integer C port` connect `msfa Apache-2.0 license notice` to `FM6 Operator Core (msfa)`, `Guide: MIDI & Sync`?**
  _High betweenness centrality (0.079) - this node is a cross-community bridge._
- **Are the 137 inferred relationships involving `clamp()` (e.g. with `preview_global()` and `preview_hit()`) actually correct?**
  _`clamp()` has 137 INFERRED edges - model-reasoned connections that need verification._
- **What connects `JIELI_TOOLCHAIN`, `AC79_SDK`, `p` to the rest of the system?**
  _252 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Track State Struct` be split into smaller, more focused modules?**
  _Cohesion score 0.02197802197802198 - nodes in this community are weakly interconnected._
- **Why does `Felucca (base firmware)` connect `Guide: MIDI & Sync` to `Guide: Punch-in FX & Signal Path`, `Guide: Sound Bank & Presets`, `msfa Apache-2.0 license notice`, `The web editor`?**
  _High betweenness centrality (0.077) - this node is a cross-community bridge._

### Low-confidence Hints
_AMBIGUOUS edges — the extractor was unsure. Verify before acting on these._

- **What is the exact relationship between `SLOOP firmware` and `Editor protocol (EDITOR_PROTOCOL.md)`?**
  _Edge tagged AMBIGUOUS (relation: conceptually_related_to) - confidence is low._
- **What is the exact relationship between `USB audio input (Felucca)` and `Browser audio preview (Emscripten WASM)`?**
  _Edge tagged AMBIGUOUS (relation: conceptually_related_to) - confidence is low._