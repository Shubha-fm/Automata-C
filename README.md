# Automata-C: 120 Automata Programs in C

A collection of **120 standalone C11 programs** covering deterministic and nondeterministic finite automata, regular languages, fixed automata algorithms, and selected pushdown-language and grammar examples. Most examples use the binary alphabet **{0, 1}**, while programs 91–100 include other alphabets. Suitable for Theory of Computation, automata theory, and introductory compiler-design exercises.

> **Scope:** Programs 01–60 are DFAs. Programs 61–62 demonstrate NFA and ε-NFA simulation. Programs 63–70 demonstrate language operations and further regular-language recognizers. Programs 71–90 demonstrate fixed-size automata algorithms and machines with output. Programs 91–110 include pushdown-language recognizers, fixed grammar and regular-language examples, and DFAs for other alphabets. Programs 101–110 include more string-language recognizers, including nonregular languages. These examples are educational; general-purpose automata construction and parsing libraries are not included.

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
python3 tests/test_programs_61_70.py
python3 tests/test_programs_71_80.py
python3 tests/test_programs_81_90.py
python3 tests/test_programs_91_100.py
python3 tests/test_programs_101_110.py
python3 tests/test_programs_111_120.py
```

Expected result for `./bin/03_ends_01 1101`: `ACCEPT`.

Programs 01–70 take one optional binary-string argument. Programs 71–90 run built-in algorithm demonstrations without arguments. Programs 91–120 accept a string argument, using the alphabet described for each program. Without an argument, it prompts for input on standard input. It prints `ACCEPT` or `REJECT` and returns exit code 2 on invalid symbols. The empty string can be supplied as a command-line argument (`""`), and acceptance depends on the individual language. The earlier recognizers use binary alphabets, whereas programs 91–100 use the alphabets specified in their descriptions.

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

### NFA examples and additional regular languages (61–70)

| # | C source | Language / demonstration |
|---:|---|---|
| 61 | [`61_nfa_contains_01.c`](programs/61_nfa_contains_01.c) | NFA simulation: contains 01 |
| 62 | [`62_epsilon_nfa_ends_10.c`](programs/62_epsilon_nfa_ends_10.c) | Epsilon-NFA simulation: ends in 10 |
| 63 | [`63_dfa_complement_contains_00.c`](programs/63_dfa_complement_contains_00.c) | DFA complement: strings avoiding 00 |
| 64 | [`64_dfa_union_ends_01_or_10.c`](programs/64_dfa_union_ends_01_or_10.c) | DFA union: ends 01 or 10 |
| 65 | [`65_dfa_intersection_even_zeros_and_ones.c`](programs/65_dfa_intersection_even_zeros_and_ones.c) | DFA intersection: even zeros and ones |
| 66 | [`66_dfa_difference_contains_11_not_00.c`](programs/66_dfa_difference_contains_11_not_00.c) | DFA difference: contains 11 but not 00 |
| 67 | [`67_dfa_symmetric_difference_parities.c`](programs/67_dfa_symmetric_difference_parities.c) | DFA symmetric difference: odd zeros XOR odd ones |
| 68 | [`68_reversed_language_nfa.c`](programs/68_reversed_language_nfa.c) | NFA for reversed language of strings ending 01 (starts 10) |
| 69 | [`69_dfa_product_contains_00_and_ends_1.c`](programs/69_dfa_product_contains_00_and_ends_1.c) | Product DFA: contains 00 and ends with 1 |
| 70 | [`70_dfa_exactly_one_01.c`](programs/70_dfa_exactly_one_01.c) | DFA counting exactly one occurrence of 01 |

### Automata algorithms (71–80)

| # | Source | Demonstration |
|---:|---|---|
| 71 | [`71_epsilon_closure.c`](programs/71_epsilon_closure.c) | Compute epsilon closure of NFA state sets |
| 72 | [`72_nfa_subset_construction.c`](programs/72_nfa_subset_construction.c) | Convert sample NFA to DFA by subset construction |
| 73 | [`73_dfa_reachable_states.c`](programs/73_dfa_reachable_states.c) | Find reachable DFA states with BFS |
| 74 | [`74_dfa_minimization.c`](programs/74_dfa_minimization.c) | Minimize a sample DFA with partition refinement |
| 75 | [`75_dfa_equivalence.c`](programs/75_dfa_equivalence.c) | Check sample DFA equivalence by product-state BFS |
| 76 | [`76_dfa_complement_table.c`](programs/76_dfa_complement_table.c) | Construct complement accepting states |
| 77 | [`77_dfa_product_intersection.c`](programs/77_dfa_product_intersection.c) | Construct product automaton for even zeros AND even ones |
| 78 | [`78_dfa_shortest_word.c`](programs/78_dfa_shortest_word.c) | Find shortest accepted word using BFS |
| 79 | [`79_dfa_enumerate_length_3.c`](programs/79_dfa_enumerate_length_3.c) | Enumerate accepted binary strings of length three |
| 80 | [`80_dfa_distinguishable_pairs.c`](programs/80_dfa_distinguishable_pairs.c) | Table-filling distinguishability for DFA states |

### Further automata algorithms (81–90)

| # | Source | Demonstration |
|---:|---|---|
| 81 | [`81_dfa_transition_trace.c`](programs/81_dfa_transition_trace.c) | Trace transitions for input 1010 |
| 82 | [`82_dfa_language_emptiness.c`](programs/82_dfa_language_emptiness.c) | Check emptiness using reachable accepting states |
| 83 | [`83_dfa_universality.c`](programs/83_dfa_universality.c) | Check whether every binary string is accepted |
| 84 | [`84_dfa_finite_language.c`](programs/84_dfa_finite_language.c) | Detect productive cycles to test language finiteness |
| 85 | [`85_nfa_epsilon_closure_set.c`](programs/85_nfa_epsilon_closure_set.c) | Compute epsilon-closure of a chosen state set |
| 86 | [`86_dfa_inclusion_counterexample.c`](programs/86_dfa_inclusion_counterexample.c) | Find counterexample to DFA language inclusion |
| 87 | [`87_dfa_shortest_distinguishing_word.c`](programs/87_dfa_shortest_distinguishing_word.c) | Find shortest word distinguishing two DFAs |
| 88 | [`88_nfa_bitset_simulation.c`](programs/88_nfa_bitset_simulation.c) | Simulate an NFA on 0101 using bit sets |
| 89 | [`89_moore_machine.c`](programs/89_moore_machine.c) | Generate Moore machine outputs for 10110 |
| 90 | [`90_mealy_machine.c`](programs/90_mealy_machine.c) | Generate Mealy machine outputs for 10110 |

### Pushdown-language and other-alphabet examples (91–100)

| # | Source | Demonstration |
|---:|---|---|
| 91 | [`91_pda_balanced_parentheses.c`](programs/91_pda_balanced_parentheses.c) | Pushdown automaton for balanced parentheses |
| 92 | [`92_pda_anbn.c`](programs/92_pda_anbn.c) | Pushdown recognition of a^n b^n (n>=0) |
| 93 | [`93_pda_palindrome_with_separator.c`](programs/93_pda_palindrome_with_separator.c) | Pushdown recognition of w#w^R |
| 94 | [`94_cfg_cyk_ab.c`](programs/94_cfg_cyk_ab.c) | CYK-style membership for grammar S -> AB, A -> a, B -> b |
| 95 | [`95_regex_thompson_01star.c`](programs/95_regex_thompson_01star.c) | Recognition of regex 0(1)* (fixed Thompson-language example) |
| 96 | [`96_dfa_decimal_mod_3.c`](programs/96_dfa_decimal_mod_3.c) | Decimal digit DFA modulo 3 |
| 97 | [`97_dfa_hex_mod_5.c`](programs/97_dfa_hex_mod_5.c) | Hexadecimal digit DFA modulo 5 |
| 98 | [`98_dfa_ternary_mod_4.c`](programs/98_dfa_ternary_mod_4.c) | Ternary digit DFA modulo 4 |
| 99 | [`99_dfa_identifier.c`](programs/99_dfa_identifier.c) | DFA for ASCII identifiers [A-Za-z_][A-Za-z0-9_]* |
| 100 | [`100_dfa_binary_multiple_11.c`](programs/100_dfa_binary_multiple_11.c) | Binary-number DFA modulo 11 |

### Further language recognition examples (101–110)

| # | Source | Recognized language |
|---:|---|---|
| 101 | [`101_dyck_two_brackets.c`](programs/101_dyck_two_brackets.c) | Balanced () and [] with stack |
| 102 | [`102_anbncn_counter.c`](programs/102_anbncn_counter.c) | Recognize a^n b^n c^n using counters |
| 103 | [`103_cfg_palindrome.c`](programs/103_cfg_palindrome.c) | Recognize binary palindromes (CFG S->0S0|1S1|0|1|epsilon) |
| 104 | [`104_regex_a_star_b_plus.c`](programs/104_regex_a_star_b_plus.c) | Recognize regular expression a*b+ |
| 105 | [`105_dfa_binary_mod_13.c`](programs/105_dfa_binary_mod_13.c) | Binary-value DFA modulo 13 |
| 106 | [`106_dfa_avoid_1011.c`](programs/106_dfa_avoid_1011.c) | Recognize binary strings avoiding 1011 |
| 107 | [`107_nfa_ends_abb.c`](programs/107_nfa_ends_abb.c) | NFA bitset simulation for strings ending abb |
| 108 | [`108_dfa_even_a_odd_b.c`](programs/108_dfa_even_a_odd_b.c) | Product DFA: even a and odd b counts |
| 109 | [`109_pda_anb2n.c`](programs/109_pda_anb2n.c) | Stack-style recognition of a^n b^(2n) |
| 110 | [`110_binary_no_000_or_111.c`](programs/110_binary_no_000_or_111.c) | DFA recognizer forbidding triple repeated bits |

### New numeric and a/b language recognizers (111–120)

| # | Source | Recognized language |
|---:|---|---|
| 111 | [`111_dfa_binary_mod_17.c`](programs/111_dfa_binary_mod_17.c) | Binary number divisible by 17 |
| 112 | [`112_dfa_decimal_mod_7.c`](programs/112_dfa_decimal_mod_7.c) | Decimal number divisible by 7 |
| 113 | [`113_dfa_ternary_mod_5.c`](programs/113_dfa_ternary_mod_5.c) | Ternary number divisible by 5 |
| 114 | [`114_dfa_a_count_mod_4.c`](programs/114_dfa_a_count_mod_4.c) | Number of a symbols divisible by 4 |
| 115 | [`115_dfa_ends_aba.c`](programs/115_dfa_ends_aba.c) | Strings over a,b ending in aba |
| 116 | [`116_dfa_contains_bbaa.c`](programs/116_dfa_contains_bbaa.c) | Strings over a,b containing bbaa |
| 117 | [`117_dfa_even_a_and_ends_b.c`](programs/117_dfa_even_a_and_ends_b.c) | Even a count and ends in b |
| 118 | [`118_dfa_no_adjacent_a.c`](programs/118_dfa_no_adjacent_a.c) | No consecutive a symbols |
| 119 | [`119_dfa_exactly_two_b.c`](programs/119_dfa_exactly_two_b.c) | Exactly two b symbols |
| 120 | [`120_dfa_length_mod_5.c`](programs/120_dfa_length_mod_5.c) | Word length divisible by five over a,b |

## Project structure

```text
Automata-C/
├── programs/                   # 120 independent C source files
├── tests/
│   ├── run_tests.py            # Tests for programs 01–20
│   ├── test_programs_21_50.py  # Tests for programs 21–50
│   └── test_programs_51_60.py  # Tests for programs 51–60
│   ├── test_programs_61_70.py # Tests for programs 61–70
│   ├── test_programs_71_80.py # Tests for programs 71–80
│   ├── test_programs_81_90.py # Tests for programs 81–90
│   ├── test_programs_91_100.py # Tests for programs 91–100
│   ├── test_programs_101_110.py # Tests for programs 101–110
│   └── test_programs_111_120.py # Tests for programs 111–120
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

The extra Python scripts are separate test suites; **`make test` alone does not run all nine**. No compiled executables are committed.

## How the automata work

The recognizer programs define a transition table, a starting state, and a set of accepting states. Starting at state 0, the DFA reads each binary digit, follows the corresponding transition, and accepts only if the final state is accepting. Some programs track substrings; others track parity, remainders, counts, or combinations of conditions.

## Further reading

- [Programs 21–50](README_30_NEW_PROGRAMS.md)
- [Programs 51–60](README_10_NEW_PROGRAMS.md)
- [Programs 61–70](README_61_70.md)
- [Programs 71–80](README_71_80.md)
- [Programs 81–90](README_81_90.md)
- [Programs 91–100](README_91_100.md)
- [Programs 101–110](README_101_110.md)
- [Programs 111–120](README_111_120.md)

## License

[MIT License](LICENSE).
