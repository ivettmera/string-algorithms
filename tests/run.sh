#!/usr/bin/env bash
set -u
cd "$(dirname "$0")/.."

make -s all || exit 1

pass=0
fail=0
for infile in tests/*.in; do
    algo=$(basename "$infile" .in)
    expected="tests/$algo.out"

    if [ ! -f "$expected" ]; then
        echo "SKIP (sin .out): $algo"
        continue
    fi

    args=""
    [ -f "tests/$algo.args" ] && args=$(cat "tests/$algo.args")

    # shellcheck disable=SC2086
    actual=$(./bin/"$algo" $args < "$infile")

    if [ "$actual" = "$(cat "$expected")" ]; then
        echo "PASS: $algo"
        pass=$((pass + 1))
    else
        echo "FAIL: $algo"
        diff <(printf '%s\n' "$actual") "$expected" | sed 's/^/    /'
        fail=$((fail + 1))
    fi
done

echo "---"
echo "$pass ok, $fail fallidos"
[ "$fail" -eq 0 ]
