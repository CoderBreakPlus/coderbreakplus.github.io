#!/usr/bin/env bash
set -e
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
git add -A
if ! git diff --cached --quiet; then
    git commit -m "批量更新"
fi
git push origin main
