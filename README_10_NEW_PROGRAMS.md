# Programs 51–60

Ten additional standalone C11 deterministic finite automata. No existing programs were replaced.

- [51_binary_divisible_7.c](programs/51_binary_divisible_7.c): Binary value divisible by 7
- [52_binary_divisible_9.c](programs/52_binary_divisible_9.c): Binary value divisible by 9
- [53_zeros_multiple_of_7.c](programs/53_zeros_multiple_of_7.c): Zero count divisible by 7
- [54_exactly_three_zeros.c](programs/54_exactly_three_zeros.c): Exactly three zeros
- [55_length_multiple_of_4.c](programs/55_length_multiple_of_4.c): String length divisible by four
- [56_alternating_bits.c](programs/56_alternating_bits.c): All neighboring bits different
- [57_avoid_010.c](programs/57_avoid_010.c): Does not contain substring 010
- [58_contains_00_and_11.c](programs/58_contains_00_and_11.c): Contains both 00 and 11
- [59_even_ones_ends_01.c](programs/59_even_ones_ends_01.c): Ends in 01 and has even number of ones
- [60_no_more_than_two_ones.c](programs/60_no_more_than_two_ones.c): At most two ones

## Build and test

```sh
make
python3 tests/test_programs_51_60.py
./bin/58_contains_00_and_11 0011
```

Each program accepts binary-string command-line input or reads a line from stdin; invalid symbols return exit code 2. The empty string is a valid input where recognized by the DFA.
