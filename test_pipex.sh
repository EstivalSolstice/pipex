#!/bin/bash

# Colors for better output visibility
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to run a test
run_test() {
    local description=$1
    local command=$2
    local expected=$3
    local check_output_file=$4

    echo -e "\n${GREEN}Test: ${description}${NC}"
    echo -e "Command: ${command}"
    eval "$command"

    # Check the exit code
    if [[ $? -eq $expected ]]; then
        echo -e "${GREEN}Exit Code PASS${NC}"
    else
        echo -e "${RED}Exit Code FAIL${NC}"
    fi

    # Check if the output file was created when expected
    if [[ $check_output_file -eq 1 && -e output.txt ]]; then
        echo -e "${GREEN}Output File PASS${NC}"
    elif [[ $check_output_file -eq 1 ]]; then
        echo -e "${RED}Output File FAIL${NC}"
    fi
}

# Paths
PIPEX="./pipex"
INPUT_FILE="input.txt"
OUTPUT_FILE="output.txt"

# Create a sample input file
echo -e "Hello\nWorld\n42\nSchool" > $INPUT_FILE

# Test cases
run_test "Basic command chain (cat | wc)" \
    "$PIPEX $INPUT_FILE \"cat\" \"wc -l\" $OUTPUT_FILE && diff $OUTPUT_FILE <(echo -e \"4\")" \
    0 1

run_test "Invalid command creates output file" \
    "$PIPEX $INPUT_FILE \"invalid_cmd\" \"wc -l\" $OUTPUT_FILE 2>/dev/null; [[ -s $OUTPUT_FILE ]]" \
    127 1

run_test "Empty input file" \
    "echo -n \"\" > empty.txt && $PIPEX empty.txt \"cat\" \"wc -l\" $OUTPUT_FILE && diff $OUTPUT_FILE <(echo -e \"0\")" \
    0 1

run_test "Nonexistent input file" \
    "$PIPEX nonexistent.txt \"cat\" \"wc -l\" $OUTPUT_FILE" \
    1 0

run_test "Nonexistent output file (write permission issue)" \
    "chmod -w . && $PIPEX $INPUT_FILE \"cat\" \"wc -l\" no_write_here.txt 2>/dev/null; chmod +w ." \
    1 0

run_test "Here_doc basic test" \
    "$PIPEX here_doc EOF \"cat\" \"wc -l\" $OUTPUT_FILE <<< \"Hello\nWorld\nEOF\" && diff $OUTPUT_FILE <(echo -e \"2\")" \
    0 1

run_test "Here_doc with empty input" \
    "$PIPEX here_doc EOF \"cat\" \"wc -l\" $OUTPUT_FILE <<< \"EOF\" && diff $OUTPUT_FILE <(echo -e \"0\")" \
    0 1

run_test "Here_doc with invalid limiter" \
    "$PIPEX here_doc WRONG_LIMITER \"cat\" \"wc -l\" $OUTPUT_FILE <<< \"Hello\nWorld\nEOF\" 2>/dev/null" \
    1 1

# Cleanup
rm -f $INPUT_FILE $OUTPUT_FILE empty.txt no_write_here.txt
