import re
import sys
import os
import subprocess


def read_file(file_path):
	with open(file_path, 'r') as file:
		return file.readlines()

def write_file(file_path, lines):
	with open(file_path, 'w') as file:
		file.writelines(lines)

def align_prototypes(lines):
	prototypes = [line for line in lines if re.match(r'^\w+\s+\**\w+\s*\(', line)]
	if not prototypes:
		return lines

	max_return_len = max(len(re.match(r'^(\w+\s+\**)', line).group(1)) for line in prototypes)

	aligned_lines = []
	for line in lines:
		match = re.match(r'^(\w+\s+)(\**)(\w+\s*\(.*)', line)
		if match:
			return_type = match.group(1) + match.group(2)
			rest = match.group(3)
			current_return_len = len(return_type)
			spaces_needed = max_return_len - current_return_len
			aligned_line = f"{return_type}{'	' * (spaces_needed//3)}{rest}\n"
			aligned_lines.append(aligned_line)
		else:
			aligned_lines.append(line)

	return aligned_lines

def add_tab_after_return_type(line):
	return re.sub(r'(\b\w+\b)\s+(\*?\s*\*?\s*\*?\s*\w+\s*\()', r'\1\t\2', line)

def add_tab_after_variable_declaration(line):
	return re.sub(r'(\b\w+\b)\s+(\*?\s*\*?\s*\*?\s*\w+\s*;)', r'\1\t\2', line)

def add_tab_before_variable_type(line):
	"""
	Ensures there is a tab before the variable type in a line of code.
	This function assumes the line is part of a typedef struct or similar context.
	"""
	# Match any leading whitespace followed by a type and variable declaration
	return re.sub(r'^\s*(\w+(\s+\**\w+)+;)', r'\t\1', line)

def reformat_preprocessor_directives(line):
	line = re.sub(r'^#include', r'# include', line)
	line = re.sub(r'^#define', r'# define', line)
	return line

def reformat_typedef_struct(line):
	return re.sub(r'(\btypedef\s+struct)\s+', r'\1 ', line)

def add_tab_after_struct_brace(line):
	return re.sub(r'(\})\s+(t_\w+;)', r'\1\t\2', line)

def add_tab_before_variable_declaration(line):
	"""
	Ensures there is a tab before each enumerator in an enum declaration.
	"""
	return re.sub(r'^\s*(\w+\s*=\s*\d+,?)', r'\t\1', line)

def add_newline_between_functions(lines):
	"""
	Adds a single newline between function definitions in the provided lines of code,
	and removes any extraneous newlines, without adding an extra newline at the end of the file.
	"""
	processed_lines = []
	brace_level = 0
	in_function = False
	consecutive_empty_lines = 0

	for i, line in enumerate(lines):
		stripped_line = line.strip()

		# Check if the current line is the start of a function
		if re.match(r'^\w+\s+\w+\s*$$.*$$\s*{', stripped_line):
			in_function = True

		# Adjust brace level
		brace_level += line.count('{')
		brace_level -= line.count('}')

		# Determine if we are at the end of a function
		if in_function and brace_level == 0:
			in_function = False
			previous_line_was_function_end = True
		else:
			previous_line_was_function_end = False

		# Add a newline between functions
		if previous_line_was_function_end and i + 1 < len(lines) and lines[i + 1].strip():
			processed_lines.append('\n')

		# Append the current line if it's not an extraneous empty line
		if stripped_line == '':
			consecutive_empty_lines += 1
		else:
			consecutive_empty_lines = 0

		if consecutive_empty_lines <= 1:
			processed_lines.append(line)

	# Remove any extra newline at the end of the file
	while processed_lines and processed_lines[-1].strip() == '':
		processed_lines.pop()

	return processed_lines

def clean_empty_lines_in_function_body(lines, file_name):
	"""
	Ensures there is exactly one empty line after variable declarations
	and removes any other unnecessary empty lines within function bodies.
	Additionally, removes lines flagged by norminette as "EMPTY_LINE_FUNCTION".
	"""
	lines_to_remove = set()

	# Run norminette and capture the output
	try:
		result = subprocess.run(
			["norminette", file_name],
			stdout=subprocess.PIPE,
			stderr=subprocess.PIPE,
			text=True
		)
		# Parse the output to find lines with "EMPTY_LINE_FUNCTION" errors
		for line in result.stdout.splitlines():
			if "EMPTY_LINE_FUNCTION" in line:
				match = re.search(r'line:\s*(\d+)', line)
				if match:
					lines_to_remove.add(int(match.group(1)))
	except Exception as e:
		print(f"Error running norminette: {e}")
		# Continue processing even if norminette fails
		lines_to_remove = set()

	processed_lines = []
	in_function = False
	last_line_was_declaration = False
	consecutive_empty_lines = 0

	for i, line in enumerate(lines, start=1):
		stripped_line = line.strip()

		# Skip lines flagged by norminette
		if i in lines_to_remove:
			continue

		# Check if we are entering a function
		if re.match(r'^\w.*\(', stripped_line):
			in_function = True

		# Check if we are exiting a function
		if in_function and stripped_line == '}':
			in_function = False

		# If inside a function, handle empty lines
		if in_function:
			if stripped_line == '':
				consecutive_empty_lines += 1
			else:
				consecutive_empty_lines = 0

			if consecutive_empty_lines > 1:
				continue

			if consecutive_empty_lines == 1 and not last_line_was_declaration:
				continue

			# Check if the current line is a variable declaration
			if re.match(r'^\s*\w+(\s+\**\w+)+\s*;', stripped_line):
				last_line_was_declaration = True
			else:
				last_line_was_declaration = False

		processed_lines.append(line)

	# Ensure the last line is a newline if the file ends with code
	if processed_lines and processed_lines[-1].strip() != '':
		processed_lines.append('\n')

	# Write the processed lines back to the file
	with open(file_name, 'w') as file:
		file.writelines(processed_lines)

	return processed_lines

def align_variable_declarations(lines):
	"""
	Aligns variable declarations by their types in the provided lines of code.
	"""
	# Collect all variable declarations
	declarations = []
	for line in lines:
		match = re.match(r'^\s*(\w+(\s+\**\w+)*\s+)(\w+)(\s*;)', line)
		if match:
			declarations.append(line)

	if not declarations:
		return lines

	# Calculate the maximum length of the type part
	max_type_length = max(len(re.match(r'^\s*(\w+(\s+\**\w+)*\s+)', line).group(1)) for line in declarations)

	# Align the declarations
	aligned_lines = []
	for line in lines:
		match = re.match(r'^\s*(\w+(\s+\**\w+)*\s+)(\w+)(\s*;)', line)
		if match:
			type_part = match.group(1)
			variable_name = match.group(3)
			semicolon = match.group(4)
			# Calculate spaces needed to align the variable names
			spaces_needed = max_type_length - len(type_part)
			aligned_line = f"	{type_part}{'	' * (spaces_needed//3)}{variable_name}{semicolon}\n"
			aligned_lines.append(aligned_line)
		else:
			aligned_lines.append(line)

	return aligned_lines

def separate_delcaration_assignation(lines, file_name):
	patterns = [
		r"^\s*(\w+\s+\w+\s*=\s*.+;)",
		r"^\s*(\w+\s+\*\w+\s*=\s*.+;)",
		r"^\s*(\w+\s+\*\*\w+\s*=\s*.+;)",
		r"^\s*(\w+\s+\*\*\*\w+\s*=\s*.+;)"
		r"^\s*(\w+\s+\*\*\*\*\w+\s*=\s*.+;)"
		r"^\s*(\w+\s+\*\*\*\*\*\w+\s*=\s*.+;)"
	]
	# yes it's horrible and what ?

	dict_variable = {}
	processed_lines = []

	for line in lines:
		original_line = line.strip()
		for pattern in patterns:
			match = re.match(pattern, original_line)
			if match:
				parts = original_line.split('=', 1)
				decl = parts[0].strip() + ';'
				name = decl.split()[-1].strip(';').lstrip('*')
				assignation = f'\t{name} = {parts[1].strip()}'
				dict_variable[decl] = assignation
				line = f'\t{decl}\n'
				break

		processed_lines.append(line)
	
	# Append assignments after the last declaration
	for i, line in enumerate(processed_lines):
		stripped_line = line.strip()
		if stripped_line in dict_variable and i + 1 < len(processed_lines) and processed_lines[i + 1].strip() not in dict_variable:
			for decl, assignation in dict_variable.items():
				print(1)
				processed_lines.insert(i + 1, f"{assignation}\n")
			break

	# Write the processed lines back to the file or print them
	for line in processed_lines:
		print(line, end='')

	return processed_lines

def add_newline_after_declarations(lines):
    """
    Adds a newline after variable declarations if there isn't one already.
    """
    processed_lines = []
    declaration_pattern = re.compile(r'^\s*\w+(\s+\**\w+)+\s*;')

    i = 0
    while i < len(lines):
        line = lines[i]
        processed_lines.append(line)

        # Check if the current line is a variable declaration
        if declaration_pattern.match(line.strip()):
            # Check if the next line is not empty
            if i + 1 < len(lines) and lines[i + 1].strip() != '':
                processed_lines.append('\n')

        i += 1

    return processed_lines

def process_lines(lines, file_path):
	processed_lines = []
	for line in lines:
		line = add_tab_after_return_type(line)
		line = add_tab_after_variable_declaration(line)
		line = add_tab_before_variable_declaration(line)
		line = add_tab_before_variable_type(line)
		if (file_path.endswith(".h")):
			line = reformat_preprocessor_directives(line)
			line = reformat_typedef_struct(line)
			line = add_tab_after_struct_brace(line)
		if not line.endswith('\n'):
			line += '\n'
		processed_lines.append(line)

	if file_path.endswith('.h'):
		processed_lines = align_prototypes(processed_lines)
	if file_path.endswith('.c'):
		processed_lines = separate_delcaration_assignation(processed_lines, file_path)
		processed_lines = add_newline_between_functions(processed_lines)
		processed_lines = align_variable_declarations(processed_lines)
		processed_lines = clean_empty_lines_in_function_body(processed_lines, file_path)
		processed_lines = add_newline_after_declarations(processed_lines)
		
	return processed_lines

def process_code_in_place(file_path):
	lines = read_file(file_path)
	processed_lines = process_lines(lines, file_path)
	write_file(file_path, processed_lines)

def test_regex_on_file(pattern, file_path):
	
	# Open the file and read lines
	with open(file_path, 'r') as file:
		lines = file.readlines()

	# Apply the regex to each line and print matches
	for line in lines:
		match = re.match(pattern, line)
		if match:
			print(f"Matched line: {line.strip()}")

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print("Usage: python format_code.py <file_path>")
		sys.exit(1)
	with open(sys.argv[1], 'r') as file:
		lines = file.readlines()
	
	file_path = sys.argv[1]
	process_code_in_place(file_path)