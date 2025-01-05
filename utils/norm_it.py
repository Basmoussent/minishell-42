import re
import sys

def process_code_in_place(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    processed_lines = []
    for line in lines:
        # Add a tab after function return types
        line = re.sub(r'(\b\w+\b)\s+(\w+\s*\()', r'\1\t\2', line)

        # Add a tab after variable declarations
        line = re.sub(r'(\b\w+\b)\s+(\w+\s*;)', r'\1\t\2', line)

        # Change '#include' to '# include'
        line = re.sub(r'^#include', r'# include', line)

        # Change '#define' to '# define'
        line = re.sub(r'^#define', r'# define', line)

        processed_lines.append(line)

    with open(file_path, 'w') as file:
        file.writelines(processed_lines)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python format_code.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    process_code_in_place(file_path)