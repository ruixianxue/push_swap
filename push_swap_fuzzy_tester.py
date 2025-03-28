#!/usr/bin/env python3

import argparse
import os
import random
import string
import subprocess
import sys
import time
from collections import defaultdict
from typing import List, Dict, Tuple, Optional, Any

class Colors:
    GREEN = "\033[0;32m"
    RED = "\033[0;31m"
    BLUE = "\033[0;34m"
    YELLOW = "\033[0;33m"
    MAGENTA = "\033[0;35m"
    CYAN = "\033[0;36m"
    RESET = "\033[0m"
    BOLD = "\033[1m"

class PushSwapTester:
    def __init__(self, 
                 push_swap_path: str = "./push_swap",
                 checker_path: str = "./checker_linux",
                 verbose: bool = False,
                 debug: bool = False,
                 disable_valgrind: bool = False):
        """Initialize the tester with paths to executables and settings."""
        self.push_swap_path = push_swap_path
        self.checker_path = checker_path if os.path.exists(checker_path) else None
        self.verbose = verbose
        self.debug = debug
        self.disable_valgrind = disable_valgrind
        
        if not os.path.exists(push_swap_path):
            print(f"{Colors.RED}Error: push_swap executable not found at {push_swap_path}{Colors.RESET}")
            print("Please compile your program first with 'make'")
            sys.exit(1)
            
        if self.checker_path is None:
            print(f"{Colors.YELLOW}Warning: Checker program not found at {checker_path}{Colors.RESET}")
            print("Will only check operation count, not correctness")
            
        if not self.disable_valgrind:
            try:
                subprocess.run(["valgrind", "--version"], capture_output=True, check=True)
            except (subprocess.SubprocessError, FileNotFoundError):
                print(f"{Colors.YELLOW}Warning: Valgrind not found, memory leak checking disabled{Colors.RESET}")
                self.disable_valgrind = True

    def generate_random_array(self, size: int) -> List[int]:
        value_range = size * 10
        return random.sample(range(-value_range, value_range + 1), size)

    def run_push_swap(self, args: List[str], check_leaks: bool = True) -> Tuple[List[str], int, Dict[str, Any]]:
        operations = []
        exit_code = 0
        leak_info = {"has_leaks": False, "leak_summary": "", "error": False}
        
        if self.disable_valgrind or not check_leaks:
            try:
                result = subprocess.run(
                    [self.push_swap_path] + args,
                    capture_output=True,
                    text=True,
                    timeout=30
                )
                
                exit_code = result.returncode
                if exit_code == 0:
                    operations = result.stdout.strip().split('\n') if result.stdout.strip() else []
                    
                return operations, exit_code, leak_info
                
            except subprocess.TimeoutExpired:
                print(f"{Colors.RED}Error: push_swap timeout on input{Colors.RESET}")
                return [], 1, leak_info
            except Exception as e:
                print(f"{Colors.RED}Error running push_swap: {e}{Colors.RESET}")
                return [], 1, leak_info
        else:
            try:
                result = subprocess.run(
                    ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--track-origins=yes", 
                     "--log-file=/tmp/push_swap_valgrind.log", self.push_swap_path] + args,
                    capture_output=True,
                    text=True,
                    timeout=60
                )
                
                exit_code = result.returncode
                if exit_code == 0:
                    operations = result.stdout.strip().split('\n') if result.stdout.strip() else []
                
                try:
                    with open("/tmp/push_swap_valgrind.log", "r") as f:
                        valgrind_output = f.read()
                        
                    if "definitely lost:" in valgrind_output:
                        leak_lines = [line for line in valgrind_output.split('\n') 
                                     if "definitely lost:" in line or "indirectly lost:" in line 
                                     or "possibly lost:" in line or "still reachable:" in line]
                        
                        leak_summary = '\n'.join(leak_lines)
                        
                        has_leaks = not all(x in s for s in leak_lines for x in ["0 bytes", "still reachable"])
                        
                        leak_info = {
                            "has_leaks": has_leaks,
                            "leak_summary": leak_summary,
                            "error": False
                        }
                except FileNotFoundError:
                    leak_info["error"] = True
                    leak_info["leak_summary"] = "Could not read valgrind output file"
                    
                return operations, exit_code, leak_info
                
            except subprocess.TimeoutExpired:
                print(f"{Colors.RED}Error: push_swap timeout during valgrind run{Colors.RESET}")
                return [], 1, {"has_leaks": False, "leak_summary": "", "error": True}
            except Exception as e:
                print(f"{Colors.RED}Error running push_swap with valgrind: {e}{Colors.RESET}")
                return [], 1, {"has_leaks": False, "leak_summary": "", "error": True}
    
    def verify_operations(self, operations: List[str]) -> bool:
        valid_ops = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"}
        for op in operations:
            if op.strip() not in valid_ops:
                return False
        return True
    
    def test_specific_size(self, size: int, expected_counts: List[int], num_tests: int = 5) -> Tuple[int, int]:
        print(f"\n{Colors.BLUE}=== Testing arrays of size {size} (expecting one of {expected_counts} operations) ==={Colors.RESET}")
        
        passed = 0
        failed = 0
        
        for i in range(1, num_tests + 1):
            numbers = self.generate_random_array(size)
            num_args = [str(num) for num in numbers]
            
            operations, exit_code, leak_info = self.run_push_swap(num_args)
            
            op_count = len(operations)
            
            ops_valid = self.verify_operations(operations)
            
            max_expected = max(expected_counts) if expected_counts else float('inf')
            count_pass = op_count <= max_expected
            
            if exit_code == 0 and ops_valid and count_pass and not leak_info["has_leaks"]:
                passed += 1
                result_color = Colors.GREEN
                result_text = "PASS"
            else:
                failed += 1
                result_color = Colors.RED
                result_text = "FAIL"
            
            expected_grade = 0
            if expected_counts:
                best_count = min(expected_counts)
                worst_count = max(expected_counts)
                
                if op_count <= best_count:
                    count_color = Colors.GREEN
                    expected_grade = 5
                elif op_count <= worst_count:
                    for grade, max_count in enumerate(sorted(expected_counts), 1):
                        if op_count <= max_count:
                            expected_grade = 6 - grade
                            break
                    count_color = Colors.YELLOW
                else:
                    count_color = Colors.RED
                    expected_grade = 0
            else:
                count_color = Colors.YELLOW
            
            print(f"Test #{i}: Operations={count_color}{op_count}{Colors.RESET}, "
                  f"Expected={expected_counts}, "
                  f"Grade={expected_grade}/5, "
                  f"Result={result_color}{result_text}{Colors.RESET}")
            
            if leak_info["has_leaks"]:
                print(f"{Colors.RED}Memory leaks detected:{Colors.RESET}")
                print(leak_info["leak_summary"])
            
            if self.verbose or result_text == "FAIL":
                print(f"Input: {' '.join(num_args[:10])}{'...' if len(num_args) > 10 else ''}")
            
            time.sleep(0.05)
        
        print(f"{Colors.BLUE}Size {size} tests completed: "
              f"{Colors.GREEN}{passed} passed{Colors.RESET}, "
              f"{Colors.RED}{failed} failed{Colors.RESET}")
        
        return passed, failed
    
    def generate_non_numeric_string(self) -> str:
        options = [
            "abc", 
            "x", 
            "!@#", 
            "123a", 
            "a123",
            "+", 
            "--", 
            "++123",
            "-+1",
            " ",
            "\t",
            "\n",
            "0x123",
            ".123",
            "123.",
            "9223372036854775808",
            "-9223372036854775809"
        ]
        return random.choice(options)
    
    def test_non_numeric_arguments(self, num_tests: int = 20) -> Tuple[int, int]:
        print(f"\n{Colors.BLUE}=== Fuzzing with non-numeric arguments ==={Colors.RESET}")
        
        passed = 0
        failed = 0
        
        for i in range(1, num_tests + 1):
            size = random.randint(2, 10)
            valid_count = random.randint(0, size - 1)
            
            args = []
            for j in range(size):
                if j < valid_count:
                    args.append(str(random.randint(-100, 100)))
                else:
                    args.append(self.generate_non_numeric_string())
            
            random.shuffle(args)
            
            operations, exit_code, _ = self.run_push_swap(args, check_leaks=False)
            
            if exit_code != 0:
                passed += 1
                result_color = Colors.GREEN
                result_text = "PASS"
            else:
                failed += 1
                result_color = Colors.RED
                result_text = "FAIL"
            
            print(f"Test #{i}: Args={args}, Exit Code={exit_code}, Result={result_color}{result_text}{Colors.RESET}")
            
        print(f"{Colors.BLUE}Non-numeric tests completed: "
              f"{Colors.GREEN}{passed} passed{Colors.RESET}, "
              f"{Colors.RED}{failed} failed{Colors.RESET}")
        
        return passed, failed
    
    def test_duplicate_arguments(self, num_tests: int = 20) -> Tuple[int, int]:
        print(f"\n{Colors.BLUE}=== Fuzzing with duplicate arguments ==={Colors.RESET}")
        
        passed = 0
        failed = 0
        
        for i in range(1, num_tests + 1):
            size = random.randint(3, 15)
            
            unique_nums = [random.randint(-100, 100) for _ in range(size - 1)]
            
            duplicate = random.choice(unique_nums)
            duplicate_index = random.randint(0, size - 1)
            
            nums = unique_nums.copy()
            nums.insert(duplicate_index, duplicate)
            
            args = [str(num) for num in nums]
            
            operations, exit_code, _ = self.run_push_swap(args, check_leaks=False)
            
            if exit_code != 0:
                passed += 1
                result_color = Colors.GREEN
                result_text = "PASS"
            else:
                failed += 1
                result_color = Colors.RED
                result_text = "FAIL"
            
            print(f"Test #{i}: Duplicate={duplicate}, Exit Code={exit_code}, Result={result_color}{result_text}{Colors.RESET}")
            if self.debug or result_text == "FAIL":
                print(f"Array: {' '.join(args)}")
            
        print(f"{Colors.BLUE}Duplicate tests completed: "
              f"{Colors.GREEN}{passed} passed{Colors.RESET}, "
              f"{Colors.RED}{failed} failed{Colors.RESET}")
        
        return passed, failed
    
    def test_integer_overflow(self, num_tests: int = 10) -> Tuple[int, int]:
        print(f"\n{Colors.BLUE}=== Testing integer overflow ==={Colors.RESET}")
        
        passed = 0
        failed = 0
        
        overflow_values = [
            "2147483648",
            "-2147483649",
            "9999999999",
            "-9999999999",
            str(2**32),
            str(-(2**32)),
            str(2**63)
        ]
        
        for i in range(1, num_tests + 1):
            size = random.randint(3, 8)
            args = [str(random.randint(-2000000000, 2000000000)) for _ in range(size - 1)]
            
            overflow_val = random.choice(overflow_values)
            insert_pos = random.randint(0, size - 1)
            args.insert(insert_pos, overflow_val)
            
            operations, exit_code, _ = self.run_push_swap(args, check_leaks=False)
            
            if exit_code != 0:
                passed += 1
                result_color = Colors.GREEN
                result_text = "PASS"
            else:
                failed += 1
                result_color = Colors.RED
                result_text = "FAIL"
            
            print(f"Test #{i}: Overflow={overflow_val}, Exit Code={exit_code}, Result={result_color}{result_text}{Colors.RESET}")
            if self.verbose or result_text == "FAIL":
                print(f"Array: {' '.join(args)}")
            
        print(f"{Colors.BLUE}Integer overflow tests completed: "
              f"{Colors.GREEN}{passed} passed{Colors.RESET}, "
              f"{Colors.RED}{failed} failed{Colors.RESET}")
        
        return passed, failed
    
    def test_edge_cases(self) -> Tuple[int, int]:
        print(f"\n{Colors.BLUE}=== Testing Edge Cases ==={Colors.RESET}")
        
        passed = 0
        failed = 0
        test_num = 1
        
        try:
            operations, exit_code, leak_info = self.run_push_swap([])
            if exit_code == 0 and not operations and not leak_info["has_leaks"]:
                print(f"Edge #{test_num}: No arguments - {Colors.GREEN}PASS{Colors.RESET}")
                passed += 1
            else:
                print(f"Edge #{test_num}: No arguments - {Colors.RED}FAIL{Colors.RESET} (expected no output & exit code 0)")
                print(f"Output: {operations}, Exit Code: {exit_code}")
                if leak_info["has_leaks"]:
                    print(f"Memory leaks: {leak_info['leak_summary']}")
                failed += 1
        except Exception as e:
            print(f"Edge #{test_num}: No arguments - {Colors.RED}FAIL{Colors.RESET} (exception: {e})")
            failed += 1
        test_num += 1
        
        try:
            operations, exit_code, leak_info = self.run_push_swap(["42"])
            if exit_code == 0 and not operations and not leak_info["has_leaks"]:
                print(f"Edge #{test_num}: Single number - {Colors.GREEN}PASS{Colors.RESET}")
                passed += 1
            else:
                print(f"Edge #{test_num}: Single number - {Colors.RED}FAIL{Colors.RESET} (expected no output & exit code 0)")
                print(f"Output: {operations}, Exit Code: {exit_code}")
                if leak_info["has_leaks"]:
                    print(f"Memory leaks: {leak_info['leak_summary']}")
                failed += 1
        except Exception as e:
            print(f"Edge #{test_num}: Single number - {Colors.RED}FAIL{Colors.RESET} (exception: {e})")
            failed += 1
        test_num += 1
        
        try:
            args = ["1", "2", "3", "4", "5"]
            operations, exit_code, leak_info = self.run_push_swap(args)
            if exit_code == 0 and not operations and not leak_info["has_leaks"]:
                print(f"Edge #{test_num}: Already sorted array - {Colors.GREEN}PASS{Colors.RESET}")
                passed += 1
            else:
                print(f"Edge #{test_num}: Already sorted array - {Colors.RED}FAIL{Colors.RESET} (expected no output & exit code 0)")
                print(f"Output: {operations}, Exit Code: {exit_code}")
                if leak_info["has_leaks"]:
                    print(f"Memory leaks: {leak_info['leak_summary']}")
                failed += 1
        except Exception as e:
            print(f"Edge #{test_num}: Already sorted array - {Colors.RED}FAIL{Colors.RESET} (exception: {e})")
            failed += 1
        test_num += 1
        
        try:
            operations, exit_code, _ = self.run_push_swap([""], check_leaks=False)
            if exit_code != 0:
                print(f"Edge #{test_num}: Empty string - {Colors.GREEN}PASS{Colors.RESET}")
                passed += 1
            else:
                print(f"Edge #{test_num}: Empty string - {Colors.RED}FAIL{Colors.RESET} (expected error)")
                print(f"Output: {operations}, Exit Code: {exit_code}")
                failed += 1
        except Exception as e:
            print(f"Edge #{test_num}: Empty string - {Colors.RED}FAIL{Colors.RESET} (exception: {e})")
            failed += 1
        test_num += 1
        
        try:
            operations, exit_code, _ = self.run_push_swap(["-"], check_leaks=False)
            if exit_code != 0:
                print(f"Edge #{test_num}: Single minus - {Colors.GREEN}PASS{Colors.RESET}")
                passed += 1
            else:
                print(f"Edge #{test_num}: Single minus - {Colors.RED}FAIL{Colors.RESET} (expected error)")
                print(f"Output: {operations}, Exit Code: {exit_code}")
                failed += 1
        except Exception as e:
            print(f"Edge #{test_num}: Single minus - {Colors.RED}FAIL{Colors.RESET} (exception: {e})")
            failed += 1
        
        return passed, failed
    
    def run_all_tests(self):
        print(f"{Colors.BLUE}====================================={Colors.RESET}")
        print(f"{Colors.BLUE}      PUSH_SWAP FUZZY TESTER        {Colors.RESET}")
        print(f"{Colors.BLUE}====================================={Colors.RESET}")
        
        total_passed = 0
        total_failed = 0
        
        edge_p, edge_f = self.test_edge_cases()
        total_passed += edge_p
        total_failed += edge_f
        
        non_num_p, non_num_f = self.test_non_numeric_arguments()
        total_passed += non_num_p
        total_failed += non_num_f
        
        dup_p, dup_f = self.test_duplicate_arguments()
        total_passed += dup_p
        total_failed += dup_f
        
        over_p, over_f = self.test_integer_overflow()
        total_passed += over_p
        total_failed += over_f
        
        size3_p, size3_f = self.test_specific_size(3, [2, 3])
        total_passed += size3_p
        total_failed += size3_f
        
        size5_p, size5_f = self.test_specific_size(5, [12])
        total_passed += size5_p
        total_failed += size5_f
        
        size100_p, size100_f = self.test_specific_size(100, [700, 900, 1100, 1300, 1500])
        total_passed += size100_p
        total_failed += size100_f
        
        size500_p, size500_f = self.test_specific_size(500, [5500, 7000, 8500, 10000, 11500])
        total_passed += size500_p
        total_failed += size500_f
        
        success_rate = (total_passed / (total_passed + total_failed)) * 100 if (total_passed + total_failed) > 0 else 0
        
        print(f"\n{Colors.BLUE}====================================={Colors.RESET}")
        print(f"{Colors.BLUE}           TESTING SUMMARY           {Colors.RESET}")
        print(f"{Colors.BLUE}====================================={Colors.RESET}")
        print(f"Total tests: {total_passed + total_failed}")
        print(f"Passed: {Colors.GREEN}{total_passed}{Colors.RESET}")
        print(f"Failed: {Colors.RED}{total_failed}{Colors.RESET}")
        
        if success_rate >= 95:
            color = Colors.GREEN
        elif success_rate >= 80:
            color = Colors.YELLOW
        else:
            color = Colors.RED
            
        print(f"Success rate: {color}{success_rate:.2f}%{Colors.RESET}")
        
        print(f"\n{Colors.BLUE}====================================={Colors.RESET}")
        print(f"{Colors.BLUE}           TESTING COMPLETE          {Colors.RESET}")
        print(f"{Colors.BLUE}====================================={Colors.RESET}")

def main():
    parser = argparse.ArgumentParser(description="Fuzzy tester for push_swap")
    parser.add_argument("--push_swap", default="./push_swap", help="Path to push_swap executable")
    parser.add_argument("--checker", default="./checker_linux", help="Path to checker executable")
    parser.add_argument("--verbose", action="store_true", help="Enable verbose output")
    parser.add_argument("--debug", action="store_true", help="Enable debug mode with step-by-step tracing")
    parser.add_argument("--disable-valgrind", action="store_true", help="Disable memory leak checking with valgrind")
    
    args = parser.parse_args()
    
    tester = PushSwapTester(
        push_swap_path=args.push_swap,
        checker_path=args.checker,
        verbose=args.verbose,
        debug=args.debug,
        disable_valgrind=args.disable_valgrind
    )
    
    tester.run_all_tests()

if __name__ == "__main__":
    main() 