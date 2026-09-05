#!/usr/bin/env bash
set -u
cd "$(dirname "$0")/.."

make -s all || exit 1

pass=0
fail=0
for infile in tests/*.in; do
    case=$(basename "$infile" .in)
    expected="tests/$case.out"

    if [ ! -f "$expected" ]; then
        echo "SKIP (sin .out): $case"
        continue
    fi

    actual=$(./bin/"$case" < "$infile")

    if [ "$actual" = "$(cat "$expected")" ]; then
        echo "PASS: $case"
        pass=$((pass + 1))
    else
        echo "FAIL: $case"
        diff <(printf '%s\n' "$actual") "$expected" | sed 's/^/    /'
        fail=$((fail + 1))
    fi
done

echo "---"
echo "$pass ok, $fail fallidos"
[ "$fail" -eq 0 ]
