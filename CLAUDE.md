# SLOOP (FM-1 firmware) — working notes for Claude

## Session handoff (one branch = one conversation)
Context is cleared at the start of every branch. A SessionStart hook injects the branch's notes
file, its commits vs `main` and `git status` — read that before exploring anything.
- Notes live in `.claude/branches/<branch with / → ->.md` (gitignored, local only).
- Update the notes at each milestone and before you finish a task. Rewrite, don't append a log;
  keep it under ~40 lines with these headings: **Goal**, **State** (done / in progress),
  **Decisions** (and why), **Dead ends** (what was tried and failed — so it is not retried),
  **Next**, **Gotchas** (file:line pointers, commands that worked).
- Don't re-verify what the notes record as done unless the code under it changed since.
- Facts useful on *every* branch go to auto-memory, not the branch notes.

## Finding things (cheapest first)
1. Known symbol/string → `grep -rn` in `firmware/ tests/ tools/ web/`. Precise and cheap.
2. "How do X and Y connect / where does X live" → graphify CLI directly via Bash
   (no need to load the graphify skill for queries):
   `graphify query "<question>" --budget 1500` · `graphify explain "<node>"` · `graphify path "A" "B"`.
   Graph answers are leads, not facts — confirm in source before acting.
3. Wide sweeps across many files → an Explore subagent, so file dumps stay out of context.

Never read whole: `graphify-out/GRAPH_REPORT.md` (60 KB) or `graph.json`, `GUIDE.md` (136 KB),
`SLOOP.md` (98 KB), `README.md` (62 KB), `DEMARRAGE-RAPIDE-FR.md`, `DUALCORE.md` — grep them
and read line ranges. Ignore `build/`, `docs/` (published site + release `.fwsc`, regenerated
at release), `assets/` binaries, `__pycache__/`.

Never run a full `/graphify` rebuild (~1.7 M tokens). To refresh after code changes use
`graphify update .` (no LLM); `graphify hook install` makes that automatic on every commit.

## Map
- `firmware/src/` app (C, ~66 files): sequencer, engines `eng_*.c`, `dsp.c`, `audio.c`, UI,
  `editor*.c` (web-editor SysEx protocol, spec in `web/EDITOR_PROTOCOL.md`), `project.c`/`storage.c`
  (flash), `ota.c`, `cpu1.c` (second core, see `DUALCORE.md`). Build flags: `felucca.c`.
- `firmware/hal/` FM-1 hardware headers + asm · `firmware/loader/` update loader · `firmware/host/` preview adapter.
- `tests/` host C tests + `regress.c` (golden renders, `golden.txt`) + `run_tests.sh`.
- `tools/` build (`build.py`), packaging, table/sample/font generators, `fm1_install.py`.
- `web/` web editor + installer (JS/HTML); `tools/build_preview.py` builds the WASM preview.

## Build & test
- `./build.sh`, then `tests/run_tests.sh > <scratchpad>/tests.log 2>&1; echo exit=$?` —
  never pipe through `tail` (masks the exit code). Then grep the log for `==`, `FAIL`, `golden renders`.
- The trustworthy signal is regress.c's "N golden renders (0 changed …)". `target_budget.py`
  fails on this machine for toolchain reasons — not a regression; A/B on the local toolchain instead.
- Only rebuild/retest when code changed since the last run; reuse the previous log otherwise.
- Intended sound change: `GOLDEN_UPDATE=1 sh tests/run_tests.sh`. Never `BUDGET_UPDATE=1` locally.

## Commits
Style: `SLOOP X.Y.Z: <user-facing summary>` for releases; plain imperative messages otherwise.
