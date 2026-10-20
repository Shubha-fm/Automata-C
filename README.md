# Automata-C: 60 Finite Automata Programs in C

A collection of **60 standalone C11 programs** demonstrating deterministic finite automata (DFA) and regular languages over the binary alphabet **{0, 1}**. Suitable for Theory of Computation, automata theory, and introductory compiler-design exercises.

> **Scope:** All 60 implementations are DFAs. This repository does not currently implement general NFA/ε-NFA simulation, DFA minimization, or regex-to-automata conversion.

## Requirements

- C11-compatible C compiler (GCC or Clang)
- `make` to build the full collection
- Python 3 for the provided tests

## Quick start

```bash
git clone https://github.com/Shubha-fm/Automata-C.git
cd Automata-C
make
./bin/03_ends_01 1101
make test
python3 tests/test_programs_21_50.py
python3 tests/test_programs_51_60.py
```

Expected result for `./bin/03_ends_01 1101`: `ACCEPT`.

Each program takes one optional binary-string argument. Without an argument, it prompts for input on standard input. It prints `ACCEPT` or `REJECT` and returns exit code 2 on invalid symbols. The empty string is supported as a command-line argument (`""`), and acceptance depends on the individual DFA.

Compile a single program without Make:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic programs/58_contains_00_and_11.c -o automata
./automata 0011
```

## Program catalog

### Fundamental DFA examples (1–20)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 1 | [`01_even_zeros.c`](programs/01_even_zeros.c) | even zeros |
| 2 | [`02_odd_ones.c`](programs/02_odd_ones.c) | odd ones |
| 3 | [`03_ends_01.c`](programs/03_ends_01.c) | Ends with 01 |
| 4 | [`04_ends_10.c`](programs/04_ends_10.c) | Ends with 10 |
| 5 | [`05_contains_00.c`](programs/05_contains_00.c) | Contains 00 |
| 6 | [`06_contains_11.c`](programs/06_contains_11.c) | Contains 11 |
| 7 | [`07_no_consecutive_ones.c`](programs/07_no_consecutive_ones.c) | no consecutive ones |
| 8 | [`08_no_consecutive_zeros.c`](programs/08_no_consecutive_zeros.c) | no consecutive zeros |
| 9 | [`09_binary_divisible_3.c`](programs/09_binary_divisible_3.c) | Binary value divisible by 3 |
| 10 | [`10_binary_divisible_5.c`](programs/10_binary_divisible_5.c) | Binary value divisible by 5 |
| 11 | [`11_zeros_mod_3.c`](programs/11_zeros_mod_3.c) | zeros mod 3 |
| 12 | [`12_ones_mod_3.c`](programs/12_ones_mod_3.c) | ones mod 3 |
| 13 | [`13_even_zeros_odd_ones.c`](programs/13_even_zeros_odd_ones.c) | even zeros odd ones |
| 14 | [`14_even_zeros_even_ones.c`](programs/14_even_zeros_even_ones.c) | even zeros even ones |
| 15 | [`15_start_1.c`](programs/15_start_1.c) | start 1 |
| 16 | [`16_exactly_two_ones.c`](programs/16_exactly_two_ones.c) | exactly two ones |
| 17 | [`17_at_least_three_zeros.c`](programs/17_at_least_three_zeros.c) | at least three zeros |
| 18 | [`18_contains_101.c`](programs/18_contains_101.c) | Contains 101 |
| 19 | [`19_ends_001.c`](programs/19_ends_001.c) | Ends with 001 |
| 20 | [`20_even_length.c`](programs/20_even_length.c) | even length |

### Substring recognition (21–30)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 21 | [`21_contains_010.c`](programs/21_contains_010.c) | Contains 010 |
| 22 | [`22_contains_110.c`](programs/22_contains_110.c) | Contains 110 |
| 23 | [`23_contains_0010.c`](programs/23_contains_0010.c) | Contains 0010 |
| 24 | [`24_contains_0110.c`](programs/24_contains_0110.c) | Contains 0110 |
| 25 | [`25_contains_1001.c`](programs/25_contains_1001.c) | Contains 1001 |
| 26 | [`26_contains_000.c`](programs/26_contains_000.c) | Contains 000 |
| 27 | [`27_contains_111.c`](programs/27_contains_111.c) | Contains 111 |
| 28 | [`28_contains_0101.c`](programs/28_contains_0101.c) | Contains 0101 |
| 29 | [`29_contains_1010.c`](programs/29_contains_1010.c) | Contains 1010 |
| 30 | [`30_contains_0011.c`](programs/30_contains_0011.c) | Contains 0011 |

### Suffix recognition (31–40)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 31 | [`31_ends_010.c`](programs/31_ends_010.c) | Ends with 010 |
| 32 | [`32_ends_110.c`](programs/32_ends_110.c) | Ends with 110 |
| 33 | [`33_ends_0010.c`](programs/33_ends_0010.c) | Ends with 0010 |
| 34 | [`34_ends_0110.c`](programs/34_ends_0110.c) | Ends with 0110 |
| 35 | [`35_ends_1001.c`](programs/35_ends_1001.c) | Ends with 1001 |
| 36 | [`36_ends_000.c`](programs/36_ends_000.c) | Ends with 000 |
| 37 | [`37_ends_111.c`](programs/37_ends_111.c) | Ends with 111 |
| 38 | [`38_ends_0101.c`](programs/38_ends_0101.c) | Ends with 0101 |
| 39 | [`39_ends_1010.c`](programs/39_ends_1010.c) | Ends with 1010 |
| 40 | [`40_ends_0011.c`](programs/40_ends_0011.c) | Ends with 0011 |

### Prefix recognition (41–45)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 41 | [`41_starts_010.c`](programs/41_starts_010.c) | Starts with 010 |
| 42 | [`42_starts_110.c`](programs/42_starts_110.c) | Starts with 110 |
| 43 | [`43_starts_0010.c`](programs/43_starts_0010.c) | Starts with 0010 |
| 44 | [`44_starts_1011.c`](programs/44_starts_1011.c) | Starts with 1011 |
| 45 | [`45_starts_0001.c`](programs/45_starts_0001.c) | Starts with 0001 |

### Modular symbol counts (46–50)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 46 | [`46_count_0_multiple_4.c`](programs/46_count_0_multiple_4.c) | Count of 0 divisible by 4 |
| 47 | [`47_count_1_multiple_4.c`](programs/47_count_1_multiple_4.c) | Count of 1 divisible by 4 |
| 48 | [`48_count_0_multiple_5.c`](programs/48_count_0_multiple_5.c) | Count of 0 divisible by 5 |
| 49 | [`49_count_1_multiple_5.c`](programs/49_count_1_multiple_5.c) | Count of 1 divisible by 5 |
| 50 | [`50_count_0_multiple_6.c`](programs/50_count_0_multiple_6.c) | Count of 0 divisible by 6 |

### Additional counting, arithmetic and language constraints (51–60)

| # | C source | Recognized language / behavior |
|---:|---|---|
| 51 | [`51_binary_divisible_7.c`](programs/51_binary_divisible_7.c) | Binary value divisible by 7 |
| 52 | [`52_binary_divisible_9.c`](programs/52_binary_divisible_9.c) | Binary value divisible by 9 |
| 53 | [`53_zeros_multiple_of_7.c`](programs/53_zeros_multiple_of_7.c) | zeros multiple of 7 |
| 54 | [`54_exactly_three_zeros.c`](programs/54_exactly_three_zeros.c) | exactly three zeros |
| 55 | [`55_length_multiple_of_4.c`](programs/55_length_multiple_of_4.c) | length multiple of 4 |
| 56 | [`56_alternating_bits.c`](programs/56_alternating_bits.c) | alternating bits |
| 57 | [`57_avoid_010.c`](programs/57_avoid_010.c) | avoid 010 |
| 58 | [`58_contains_00_and_11.c`](programs/58_contains_00_and_11.c) | Contains 00 and and and 11 |
| 59 | [`59_even_ones_ends_01.c`](programs/59_even_ones_ends_01.c) | even ones ends 01 |
| 60 | [`60_no_more_than_two_ones.c`](programs/60_no_more_than_two_ones.c) | no more than two ones |

## Project structure

```text
Automata-C/
├── programs/                   # 60 independent C source files
├── tests/
│   ├── run_tests.py            # Tests for programs 01–20
│   ├── test_programs_21_50.py  # Tests for programs 21–50
│   └── test_programs_51_60.py  # Tests for programs 51–60
├── Makefile
├── README.md
├── README_30_NEW_PROGRAMS.md
├── README_10_NEW_PROGRAMS.md
├── LICENSE
└── .gitignore
```

## Testing and cleaning

```bash
make             # Compiles every programs/*.c file to bin/
make test        # Runs tests/run_tests.py for the original 20
python3 tests/test_programs_21_50.py
python3 tests/test_programs_51_60.py
make clean
```

The extra Python scripts are separate test suites; **`make test` alone does not run all three**. No compiled executables are committed.

## How the automata work

Each program defines a transition table, a starting state, and a set of accepting states. Starting at state 0, the DFA reads each binary digit, follows the corresponding transition, and accepts only if the final state is accepting. Some programs track substrings; others track parity, remainders, counts, or combinations of conditions.

## Further reading

- [Programs 21–50](README_30_NEW_PROGRAMS.md)
- [Programs 51–60](README_10_NEW_PROGRAMS.md)

## License

[MIT License](LICENSE).
