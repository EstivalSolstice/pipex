#!/bin/bash

# Colors for better output visibility
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Counters for test summary
total_tests=0
passed_tests=0
failed_tests=0

# Function to run a test
run_test() {
    local description=$1
    local command=$2
    local expected_exit=$3
    local expected_output=$4
    local output_file="output.txt"

    # Cleanup previous output
    rm -f "$output_file"
    total_tests=$((total_tests + 1))

    echo -e "\n${GREEN}Test: $description${NC}"
    echo -e "Command: $command"

    # Run the command and capture the exit code
    eval "$command"
    local exit_code=$?

    # Compare exit codes
    if [[ $exit_code -eq $expected_exit ]]; then
        echo -e "${GREEN}Exit Code PASS${NC}"
        exit_code_pass=true
    else
        echo -e "${RED}Exit Code FAIL (Expected: $expected_exit, Got: $exit_code)${NC}"
        exit_code_pass=false
    fi

    # Compare output file content to expected
    if [[ -e $output_file ]]; then
        # Normalize the output to remove leading spaces from `wc -l` if needed
        sed 's/^ *//' "$output_file" > normalized_output.txt
        sed 's/^ *//' "$expected_output" > normalized_expected.txt

        if diff -q normalized_output.txt normalized_expected.txt >/dev/null; then
            echo -e "${GREEN}Output File PASS${NC}"
            output_pass=true
        else
            echo -e "${RED}Output File FAIL${NC}"
            echo "Expected:"
            cat normalized_expected.txt
            echo "Got:"
            cat normalized_output.txt
            output_pass=false
        fi
        rm -f normalized_output.txt normalized_expected.txt
    else
        echo -e "${RED}Output File FAIL (File not created)${NC}"
        output_pass=false
    fi

    # Update pass/fail counters
    if [[ $exit_code_pass == true && $output_pass == true ]]; then
        passed_tests=$((passed_tests + 1))
    else
        failed_tests=$((failed_tests + 1))
    fi
}

# Mandatory tests (without here_doc or multiple pipes)
echo -e "${GREEN}--- Mandatory Tests ---${NC}"

# Test 1: Basic command chain
echo -e "Hello\nWorld\n42\nSchool" > input.txt
echo -e "4" > expected_output.txt
run_test "Basic command chain (cat | wc)" \
    "./pipex input.txt \"cat\" \"wc -l\" output.txt" \
    0 expected_output.txt

# Test 2: Invalid command
echo -e "0" > expected_output.txt
run_test "Invalid command creates output file" \
    "./pipex input.txt \"invalid_cmd\" \"wc -l\" output.txt 2>/dev/null" \
    127 expected_output.txt

# Test 3: Empty input file
> empty.txt
echo -e "0" > expected_output.txt
run_test "Empty input file (cat | wc)" \
    "./pipex empty.txt \"cat\" \"wc -l\" output.txt" \
    0 expected_output.txt

# Test 4: Nonexistent input file
run_test "Nonexistent input file" \
    "./pipex nonexistent.txt \"cat\" \"wc -l\" output.txt" \
    1 /dev/null

# Bonus tests (with here_doc and multiple pipes)
echo -e "${GREEN}--- Bonus Tests ---${NC}"

# Test 5: Basic here_doc
echo -e "2" > expected_output.txt
run_test "Basic here_doc test" \
    "./pipex_bonus here_doc EOF \"cat\" \"wc -l\" output.txt << EOF
Line 1
Line 2
EOF" \
    0 expected_output.txt

# Test 6: Here_doc with empty input
echo -e "0" > expected_output.txt
run_test "Here_doc with empty input" \
    "./pipex_bonus here_doc EOF \"cat\" \"wc -l\" output.txt << EOF
EOF" \
    0 expected_output.txt

# Test 7: Multiple pipes with here_doc
echo -e "2" > expected_output.txt
run_test "Here_doc with multiple pipes" \
    "./pipex_bonus here_doc EOF \"cat\" \"grep Line\" \"wc -l\" output.txt << EOF
Line 1
Line 2
EOF" \
    0 expected_output.txt

# Test 8: Multiple commands without here_doc
echo -e "1" > expected_output.txt
run_test "Multiple commands without here_doc" \
    "./pipex_bonus input.txt \"cat\" \"grep 42\" \"wc -l\" output.txt" \
    0 expected_output.txt

# Test 9: Invalid command in the middle of a pipeline
echo -e "0" > expected_output.txt
run_test "Invalid command in pipeline" \
    "./pipex_bonus input.txt \"cat\" \"invalid_cmd\" \"wc -l\" output.txt 2>/dev/null" \
    127 expected_output.txt

# Test 10: Long pipeline with here_doc
echo -e "1" > expected_output.txt
run_test "Long pipeline with here_doc" \
    "./pipex_bonus here_doc EOF \"cat\" \"grep Line\" \"grep 1\" \"wc -l\" output.txt << EOF
Line 1
Line 2
Line 3
EOF" \
    0 expected_output.txt

# Test 11: Complex commands in pipeline
echo -e "2" > expected_output.txt
run_test "Complex commands in pipeline" \
    "./pipex_bonus input.txt \"cat\" \"grep -E 'Hello|World'\" \"wc -l\" output.txt" \
    0 expected_output.txt

# Cleanup
rm -f input.txt empty.txt expected_output.txt output.txt

# Print Summary
echo -e "\n${GREEN}--- Test Summary ---${NC}"
echo -e "${GREEN}Total Tests: $total_tests${NC}"
echo -e "${GREEN}Passed Tests: $passed_tests${NC}"
if [[ $failed_tests -gt 0 ]]; then
    echo -e "${RED}Failed Tests: $failed_tests${NC}"
else
    echo -e "${GREEN}Failed Tests: $failed_tests${NC}"
fi
