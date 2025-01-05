#!/bin/bash

format_file() {
    local file="$1"
    clang-format -i "$file"
    python3 utils/norm_it.py "$file"
}

if [ "$#" -gt 0 ]; then
    files_to_format=("$@")
else
	files_to_format=($(find ./src ./include -type f \( -name "*.c" -o -name "*.h" \) -not -path "./libft/*"\)))
fi

for file in "${files_to_format[@]}"; do
    echo "Normed: $file"
    format_file "$file"
done
