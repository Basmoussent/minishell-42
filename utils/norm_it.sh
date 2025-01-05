#!/bin/bash

format_file() {
    local file="$1"
    clang-format -i "$file"
    python utils/norm_it.py "$file"
}

if [ "$#" -gt 0 ]; then
    files_to_format=("$@")
else
    files_to_format=($(find . -type f $$ -name "*.c" -o -name "*.h" $$))
fi

for file in "${files_to_format[@]}"; do
    echo "Normed: $file"
    format_file "$file"
done