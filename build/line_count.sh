#!/bin/bash

# Change to the script's parent directory
cd "$(dirname "$0")"
cd ../

# Regular expression to exclude specific directories
EXCLUDE_DIRS='build|PulsarionBenchmarks/vendor|PulsarionMedia/vendor|PulsarionCore/vendor|PulsarionMath/tests/vendor|PulsarionShaderLanguage/tests/vendor'

# Run CLOC with regular expression exclusion
cloc --fullpath --not-match-d="$EXCLUDE_DIRS" --by-file --csv --quiet --report-file=build/line_count.csv .

# We also display it
cloc --fullpath --not-match-d="$EXCLUDE_DIRS" .
