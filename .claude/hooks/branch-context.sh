#!/bin/sh
# SessionStart hook: print the current branch's handoff notes and git state.
# Claude Code adds this output to the new conversation's context.
cd "${CLAUDE_PROJECT_DIR:-.}" || exit 0
b=$(git branch --show-current 2>/dev/null)
[ -n "$b" ] || exit 0
f=".claude/branches/$(printf %s "$b" | tr / -).md"

echo "# Branch: $b"
if [ -f "$f" ]; then
    echo "## Handoff notes ($f)"
    cat "$f"
else
    echo "No handoff notes yet. Create $f once there is something worth handing off (see CLAUDE.md)."
fi
if [ "$b" != main ]; then
    echo
    echo "## Commits on $b not in main"
    git log --oneline --no-decorate main..HEAD 2>/dev/null | cut -c1-120 | head -20
fi
s=$(git status --short 2>/dev/null | head -20)
[ -n "$s" ] && printf '\n## Uncommitted changes\n%s\n' "$s"
exit 0
