# Automata-C: 260 Automata Programs in C

A collection of **260 C11 command-line programs** covering deterministic and nondeterministic finite automata, regular languages, fixed automata algorithms, and selected pushdown-language and grammar examples. Most examples use the binary alphabet **{0, 1}**, while programs 91–150 also include other alphabets. Suitable for Theory of Computation, automata theory, and introductory compiler-design exercises.

> **Scope:** Programs 01–60 are DFAs. Programs 61–62 demonstrate NFA and ε-NFA simulation. Programs 63–70 demonstrate language operations and further regular-language recognizers. Programs 71–90 demonstrate fixed-size automata algorithms and machines with output. Programs 91–110 include pushdown-language recognizers, fixed grammar and regular-language examples, and DFAs for other alphabets. Programs 101–110 include more string-language recognizers, including nonregular languages. Programs 151–160 add ε-NFA conversion, shortest-word searches, formal-language finiteness, and machine analysis. Programs 161–170 cover regex compilation, DFA coverage, synchronization, strongly connected components, language quotients, reversal, and cross-checking. Programs 171–180 extend the tooling with KMP/Aho-Corasick and automata verification. Programs 181–190 demonstrate weighted and probabilistic machines, Mealy transducers, approximate matching, timed guards, Büchi-cycle analysis, and DFA validation. Programs 191–200 cover Hopcroft refinement, exact language equivalence, combinatorial counting, generalized Büchi acceptance, Mealy composition, and CYK parsing. Programs 201–210 introduce accepted-word ranking, transition monoids, probabilistic acceptance, inverse homomorphisms, regex derivatives, Büchi word evaluation, parse-tree reconstruction, and sink-state completion. Programs 211–220 add pumping witnesses, NFA distinct-word counting, weighted path reconstruction, exact ambiguity analysis, Earley parsing, grammar-to-NFA construction, epsilon elimination, and finite-language cardinality. Programs 221–230 cover mutation-test generation, universality and intersection witnesses, Moore equivalence, FIRST/FOLLOW analysis, LL(1) parsing, ambiguous parse counting, epsilon-NFA shortest words, shuffle languages, and file-based DFA equivalence. Programs 231–240 introduce DFA conformance suites, bounded NFA comparison, weighted shortest words, nullable/unit closure, LL(1) table construction, probabilistic state tracking, bounded PDA BFS, finite-trace property monitoring, unique NFA word enumeration, and generalized Büchi lasso witnesses. Programs 241–250 add file-based DFA inclusion, shortest-word and counting analyses, SCC audits, complement, intersection, reachable-state trimming, minimization, distinguishing words, and DOT export. Programs 251–260 extend those file-based tools with universality, finiteness, synchronization, rank/unrank, reversal, symmetric difference, access words, coverage, enumeration, and inverse homomorphisms. Both batches share `include/dfa_io.h`. Programs 171–180 add configurable automata loaded from files, multi-pattern matching, DOT export, partition refinement, and Büchi nonemptiness. These examples are educational and not industrial-scale automata libraries. Programs 173–175 and 180 support user-provided machines with documented size limits.

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
python3 tests/test_programs_121_130.py
python3 tests/test_programs_131_140.py
python3 tests/test_programs_141_150.py
python3 tests/test_programs_151_160.py
python3 tests/test_programs_161_170.py
python3 tests/test_programs_171_180.py
python3 tests/test_programs_181_190.py
```

Expected result for `./bin/03_ends_01 1101`: `ACCEPT`.

Programs 01–70 take one optional binary-string argument. Programs 71–90 run built-in algorithm demonstrations without arguments. Programs 91–150 accept a string argument, using the alphabet described for each program. Programs 151, 156, 157 and 159 take command-line inputs; other programs in the 151–160 range analyze built-in machines. See the separate guides for [programs 161–170](README_161_170.md) and [programs 171–180](README_171_180.md) for their command-line interfaces. Without an argument, it prompts for input on standard input. It prints `ACCEPT` or `REJECT` and returns exit code 2 on invalid symbols. The empty string can be supplied as a command-line argument (`""`), and acceptance depends on the individual language. The earlier recognizers use binary alphabets, whereas programs 91–100 use the alphabets specified in their descriptions.

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

### More binary and mixed-alphabet languages (121–130)

| # | Source | Recognized language |
|---:|---|---|
| 121 | [`121_dfa_count_01_mod_3.c`](programs/121_dfa_count_01_mod_3.c) | Number of 01 occurrences divisible by three |
| 122 | [`122_dfa_count_10_mod_2.c`](programs/122_dfa_count_10_mod_2.c) | Even number of 10 occurrences |
| 123 | [`123_dfa_ends_same_two.c`](programs/123_dfa_ends_same_two.c) | Binary strings whose last two digits agree |
| 124 | [`124_dfa_first_last_same.c`](programs/124_dfa_first_last_same.c) | Nonempty binary strings starting and ending with same symbol |
| 125 | [`125_dfa_contains_010_and_101.c`](programs/125_dfa_contains_010_and_101.c) | Binary strings containing both 010 and 101 |
| 126 | [`126_dfa_no_010_or_101.c`](programs/126_dfa_no_010_or_101.c) | Binary strings avoiding 010 and 101 |
| 127 | [`127_dfa_a_mod_3_b_mod_2.c`](programs/127_dfa_a_mod_3_b_mod_2.c) | a count multiple of 3 and b count even |
| 128 | [`128_dfa_odd_length_ends_0.c`](programs/128_dfa_odd_length_ends_0.c) | Odd-length binary strings ending in zero |
| 129 | [`129_dfa_binary_mod_19.c`](programs/129_dfa_binary_mod_19.c) | Binary number divisible by 19 |
| 130 | [`130_dfa_abc_ends_ab.c`](programs/130_dfa_abc_ends_ab.c) | Strings over a,b,c ending with ab |

### Additional multi-alphabet DFA recognizers (131–140)

| # | Source | Recognized language |
|---:|---|---|
| 131 | [`131_dfa_binary_mod_23.c`](programs/131_dfa_binary_mod_23.c) | Binary integer divisible by 23 |
| 132 | [`132_dfa_decimal_mod_11.c`](programs/132_dfa_decimal_mod_11.c) | Decimal integer divisible by 11 |
| 133 | [`133_dfa_contains_abc.c`](programs/133_dfa_contains_abc.c) | Strings over abc containing substring abc |
| 134 | [`134_dfa_avoid_bb.c`](programs/134_dfa_avoid_bb.c) | Strings over ab without adjacent b |
| 135 | [`135_dfa_exactly_three_a.c`](programs/135_dfa_exactly_three_a.c) | Strings over ab containing exactly three a |
| 136 | [`136_dfa_a_count_mod_5.c`](programs/136_dfa_a_count_mod_5.c) | Strings over ab with a count divisible by five |
| 137 | [`137_dfa_binary_length_mod_7.c`](programs/137_dfa_binary_length_mod_7.c) | Binary strings of length divisible by seven |
| 138 | [`138_dfa_binary_has_exactly_one_11.c`](programs/138_dfa_binary_has_exactly_one_11.c) | Binary strings with exactly one overlapping occurrence of 11 |
| 139 | [`139_dfa_ends_ab_or_ba.c`](programs/139_dfa_ends_ab_or_ba.c) | Strings over ab ending ab or ba |
| 140 | [`140_dfa_even_a_odd_c.c`](programs/140_dfa_even_a_odd_c.c) | Strings over abc with even a count and odd c count |

### Positional-number remainder DFAs (141–150)

| # | Source | Recognized language |
|---:|---|---|
| 141 | [`141_dfa_binary_mod_29.c`](programs/141_dfa_binary_mod_29.c) | Binary integer divisible by 29 |
| 142 | [`142_dfa_binary_mod_31.c`](programs/142_dfa_binary_mod_31.c) | Binary integer divisible by 31 |
| 143 | [`143_dfa_decimal_mod_13.c`](programs/143_dfa_decimal_mod_13.c) | Decimal integer divisible by 13 |
| 144 | [`144_dfa_hex_mod_7.c`](programs/144_dfa_hex_mod_7.c) | Hexadecimal integer divisible by 7 |
| 145 | [`145_dfa_ternary_mod_7.c`](programs/145_dfa_ternary_mod_7.c) | Ternary integer divisible by 7 |
| 146 | [`146_dfa_quaternary_mod_5.c`](programs/146_dfa_quaternary_mod_5.c) | Base-4 integer divisible by 5 |
| 147 | [`147_dfa_binary_mod_37.c`](programs/147_dfa_binary_mod_37.c) | Binary integer divisible by 37 |
| 148 | [`148_dfa_decimal_mod_17.c`](programs/148_dfa_decimal_mod_17.c) | Decimal integer divisible by 17 |
| 149 | [`149_dfa_octal_mod_9.c`](programs/149_dfa_octal_mod_9.c) | Octal integer divisible by 9 |
| 150 | [`150_dfa_hex_mod_11.c`](programs/150_dfa_hex_mod_11.c) | Hexadecimal integer divisible by 11 |

### Construction, analysis and witness algorithms (151–160)

| # | Source | Demonstration |
|---:|---|---|
| 151 | [`151_epsilon_nfa_cycle_simulator.c`](programs/151_epsilon_nfa_cycle_simulator.c) | Epsilon-NFA simulation with a cyclic epsilon closure |
| 152 | [`152_epsilon_nfa_subset_construction.c`](programs/152_epsilon_nfa_subset_construction.c) | Reachable DFA subsets from an epsilon-NFA |
| 153 | [`153_dfa_shortest_rejected_word.c`](programs/153_dfa_shortest_rejected_word.c) | Find the shortest rejected word using BFS |
| 154 | [`154_dfa_shortest_access_words.c`](programs/154_dfa_shortest_access_words.c) | Shortest access words for every reachable DFA state |
| 155 | [`155_dfa_finiteness_productive_cycle.c`](programs/155_dfa_finiteness_productive_cycle.c) | Decide language finiteness by finding productive cycles |
| 156 | [`156_dfa_count_accepted_words.c`](programs/156_dfa_count_accepted_words.c) | Dynamic programming counts accepted words of a given length |
| 157 | [`157_nfa_count_accepting_paths.c`](programs/157_nfa_count_accepting_paths.c) | Count accepting runs of a nondeterministic automaton |
| 158 | [`158_mealy_equivalence_witness.c`](programs/158_mealy_equivalence_witness.c) | Find the shortest distinguishing word for two Mealy machines |
| 159 | [`159_right_linear_grammar_recognizer.c`](programs/159_right_linear_grammar_recognizer.c) | Right-linear grammar recognition via an equivalent NFA |
| 160 | [`160_dfa_canonical_bfs_encoding.c`](programs/160_dfa_canonical_bfs_encoding.c) | Canonical reachable-state renumbering of a sample DFA |

### Regex and automata algorithms (161–170)

| # | C source | Description |
|---:|---|---|
| 161 | [`161_regex_postfix_thompson.c`](programs/161_regex_postfix_thompson.c) | Compile postfix regex to a Thompson ε-NFA and simulate it |
| 162 | [`162_regex_infix_to_postfix.c`](programs/162_regex_infix_to_postfix.c) | Convert binary infix regex with implicit concatenation to postfix |
| 163 | [`163_dfa_transition_cover.c`](programs/163_dfa_transition_cover.c) | Construct a shortest-prefix transition coverage suite using BFS |
| 164 | [`164_dfa_shortest_reset_word.c`](programs/164_dfa_shortest_reset_word.c) | Find a shortest synchronizing word by subset BFS |
| 165 | [`165_dfa_tarjan_scc.c`](programs/165_dfa_tarjan_scc.c) | Compute strongly connected components of a DFA using Tarjan's algorithm |
| 166 | [`166_dfa_left_quotient.c`](programs/166_dfa_left_quotient.c) | Evaluate a left quotient of the ends-in-01 language |
| 167 | [`167_dfa_right_quotient.c`](programs/167_dfa_right_quotient.c) | Compute DFA final states for right quotient by suffix 01 |
| 168 | [`168_reversed_dfa_nfa.c`](programs/168_reversed_dfa_nfa.c) | Reverse all transitions of a DFA to recognize its reverse language |
| 169 | [`169_dfa_state_pair_witnesses.c`](programs/169_dfa_state_pair_witnesses.c) | Find shortest distinguishing words for every DFA state pair |
| 170 | [`170_nfa_dfa_exhaustive_crosscheck.c`](programs/170_nfa_dfa_exhaustive_crosscheck.c) | Exhaustively compare NFA and DFA recognition through length eight |

### Configurable automata and analysis (171–180)

| # | C source | Description |
|---:|---|---|
| 171 | [`171_kmp_binary_match.c`](programs/171_kmp_binary_match.c) | KMP binary pattern matching |
| 172 | [`172_aho_binary_patterns.c`](programs/172_aho_binary_patterns.c) | Aho-Corasick multi-pattern binary matching |
| 173 | [`173_dfa_file_simulator.c`](programs/173_dfa_file_simulator.c) | DFA simulation from transition-table file |
| 174 | [`174_nfa_file_simulator.c`](programs/174_nfa_file_simulator.c) | NFA simulation from bitmask file |
| 175 | [`175_epsilon_nfa_file_simulator.c`](programs/175_epsilon_nfa_file_simulator.c) | ε-NFA simulation from file |
| 176 | [`176_dfa_dot_export.c`](programs/176_dfa_dot_export.c) | DFA export in Graphviz DOT format |
| 177 | [`177_dfa_partition_minimization.c`](programs/177_dfa_partition_minimization.c) | DFA partition-refinement minimization |
| 178 | [`178_buchi_nonemptiness.c`](programs/178_buchi_nonemptiness.c) | Büchi automaton nonemptiness |
| 179 | [`179_moore_partition_minimization.c`](programs/179_moore_partition_minimization.c) | Moore machine partition minimization |
| 180 | [`180_dfa_equivalence_from_files.c`](programs/180_dfa_equivalence_from_files.c) | DFA equivalence from files with a shortest counterexample |

### Weighted, probabilistic, transducer and validation programs (181–190)

| # | Source | Function |
|---:|---|---|
| 181 | [`181_weighted_nfa_min_cost.c`](programs/181_weighted_nfa_min_cost.c) | Minimum accepting cost of a nondeterministic weighted finite automaton |
| 182 | [`182_probabilistic_finite_automaton.c`](programs/182_probabilistic_finite_automaton.c) | Probabilistic finite automaton with acceptance threshold 0.5 |
| 183 | [`183_mealy_binary_to_gray.c`](programs/183_mealy_binary_to_gray.c) | Mealy transducer converting binary digits into Gray code |
| 184 | [`184_mealy_bit_stuffing.c`](programs/184_mealy_bit_stuffing.c) | Mealy-style bit stuffing: insert zero after five consecutive ones |
| 185 | [`185_mealy_bit_unstuffing.c`](programs/185_mealy_bit_unstuffing.c) | Inverse of bit-stuffing transducer with malformed-input rejection |
| 186 | [`186_levenshtein_automaton_distance_one.c`](programs/186_levenshtein_automaton_distance_one.c) | Threshold-one Levenshtein recognizer for binary words |
| 187 | [`187_trie_keyword_dfa.c`](programs/187_trie_keyword_dfa.c) | Dynamically construct a trie DFA for six compiler keywords |
| 188 | [`188_timed_automaton_guard.c`](programs/188_timed_automaton_guard.c) | Timed transition monitor: consecutive timestamps must be within ten units |
| 189 | [`189_buchi_accepting_lasso.c`](programs/189_buchi_accepting_lasso.c) | Find a reachable Büchi accepting cycle and show a lasso witness |
| 190 | [`190_dfa_transition_validator.c`](programs/190_dfa_transition_validator.c) | Validate a complete deterministic binary transition table from a text file |

### Algorithms and verification examples (191–200)

| # | Source | Demonstration |
|---:|---|---|
| 191 | [`191_hopcroft_dfa_minimization.c`](programs/191_hopcroft_dfa_minimization.c) | Hopcroft partition refinement of a six-state DFA |
| 192 | [`192_dfa_matrix_word_count.c`](programs/192_dfa_matrix_word_count.c) | Count accepted binary words using matrix exponentiation |
| 193 | [`193_nfa_dfa_exact_equivalence.c`](programs/193_nfa_dfa_exact_equivalence.c) | On-the-fly exact equivalence of an NFA and a DFA, with witness |
| 194 | [`194_nfa_shortest_accepted_word.c`](programs/194_nfa_shortest_accepted_word.c) | Breadth-first subset search for the shortest NFA-accepted word |
| 195 | [`195_dfa_lexicographic_unranking.c`](programs/195_dfa_lexicographic_unranking.c) | Find the kth lexicographic word accepted by a parity DFA |
| 196 | [`196_nfa_ambiguity_witness.c`](programs/196_nfa_ambiguity_witness.c) | Find the shortest word with multiple accepting NFA runs |
| 197 | [`197_generalized_buchi_scc.c`](programs/197_generalized_buchi_scc.c) | Check two-set generalized Büchi acceptance using SCCs |
| 198 | [`198_mealy_transducer_composition.c`](programs/198_mealy_transducer_composition.c) | Compose bit-complement and binary-to-Gray Mealy transducers |
| 199 | [`199_cfg_cyk_membership.c`](programs/199_cfg_cyk_membership.c) | CYK membership for a nontrivial fixed Chomsky-normal-form grammar |
| 200 | [`200_dfa_reachability_productivity_audit.c`](programs/200_dfa_reachability_productivity_audit.c) | Audit reachable, productive, dead, and unreachable DFA states |

### Word ranking and automata analysis (201–210)

| # | Source | Explanation |
|---:|---|---|
| 201 | [`201_dfa_accepted_word_rank.c`](programs/201_dfa_accepted_word_rank.c) | Find a binary word's zero-based lexicographic rank among even-parity words |
| 202 | [`202_dfa_transition_monoid.c`](programs/202_dfa_transition_monoid.c) | Enumerate the finite transition monoid of a sample DFA |
| 203 | [`203_dfa_iid_accept_probability.c`](programs/203_dfa_iid_accept_probability.c) | Compute DFA acceptance probability for uniformly random binary words |
| 204 | [`204_nfa_language_inclusion_witness.c`](programs/204_nfa_language_inclusion_witness.c) | Exact NFA language inclusion against a DFA using a product-state BFS |
| 205 | [`205_dfa_inverse_homomorphism.c`](programs/205_dfa_inverse_homomorphism.c) | Recognize the inverse image of ends-in-01 under a binary substitution |
| 206 | [`206_regex_brzozowski_derivative.c`](programs/206_regex_brzozowski_derivative.c) | Derivative-state recognition of the fixed regular expression 0*1 |
| 207 | [`207_dfa_hamming_distance_one.c`](programs/207_dfa_hamming_distance_one.c) | Hamming-distance-one language recognizer for a supplied binary target |
| 208 | [`208_buchi_ultimately_periodic_word.c`](programs/208_buchi_ultimately_periodic_word.c) | Check Büchi acceptance of an ultimately periodic infinite word u(v)^omega |
| 209 | [`209_cyk_parse_tree_witness.c`](programs/209_cyk_parse_tree_witness.c) | Construct an explicit CYK parse tree for a fixed CNF grammar |
| 210 | [`210_partial_dfa_sink_completion.c`](programs/210_partial_dfa_sink_completion.c) | Complete a partial binary DFA by adding a rejecting sink state |

### Pumping, ambiguity, grammar parsing and finiteness (211–220)

| # | C source | Description |
|---:|---|---|
| 211 | [`211_dfa_pumping_witness.c`](programs/211_dfa_pumping_witness.c) | Construct and validate a pumping decomposition for an infinite DFA language |
| 212 | [`212_nfa_count_distinct_words.c`](programs/212_nfa_count_distinct_words.c) | Count distinct NFA-accepted binary words without double-counting paths |
| 213 | [`213_dfa_next_accepted_word.c`](programs/213_dfa_next_accepted_word.c) | Find the next accepted same-length word in lexicographic order |
| 214 | [`214_weighted_nfa_viterbi_path.c`](programs/214_weighted_nfa_viterbi_path.c) | Recover a minimum-cost accepting state sequence in a weighted NFA |
| 215 | [`215_dfa_pair_synchronization.c`](programs/215_dfa_pair_synchronization.c) | Check pair mergeability as a synchronizing-DFA criterion |
| 216 | [`216_nfa_exact_ambiguity.c`](programs/216_nfa_exact_ambiguity.c) | Check NFA ambiguity exactly via a product of two independent runs |
| 217 | [`217_earley_cfg_membership.c`](programs/217_earley_cfg_membership.c) | Earley membership for S -> a S b | epsilon |
| 218 | [`218_regular_grammar_to_nfa.c`](programs/218_regular_grammar_to_nfa.c) | Build and simulate an NFA from a user-supplied right-linear grammar |
| 219 | [`219_nfa_epsilon_elimination.c`](programs/219_nfa_epsilon_elimination.c) | Eliminate epsilon transitions and exhaustively cross-check the result |
| 220 | [`220_dfa_finite_language_cardinality.c`](programs/220_dfa_finite_language_cardinality.c) | Determine finite-language cardinality or detect infinite accepted words |

### Equivalence, grammar analysis and test generation (221–230)

| # | C source | Description |
|---:|---|---|
| 221 | [`221_dfa_mutation_test_suite.c`](programs/221_dfa_mutation_test_suite.c) | Generate shortest test words that distinguish reference and mutated DFAs |
| 222 | [`222_nfa_universality_counterexample.c`](programs/222_nfa_universality_counterexample.c) | Exact NFA universality test via subset BFS with shortest rejected word |
| 223 | [`223_nfa_intersection_witness.c`](programs/223_nfa_intersection_witness.c) | Shortest accepted word in the intersection of two NFAs |
| 224 | [`224_moore_machine_equivalence.c`](programs/224_moore_machine_equivalence.c) | Check two Moore machines and return a shortest output-mismatch witness |
| 225 | [`225_cfg_first_follow_sets.c`](programs/225_cfg_first_follow_sets.c) | Iteratively compute FIRST, nullable, and FOLLOW sets for a fixed CFG |
| 226 | [`226_ll1_predictive_parser.c`](programs/226_ll1_predictive_parser.c) | Stack-based LL(1) parser for S -> a S b | epsilon |
| 227 | [`227_cyk_ambiguous_parse_count.c`](programs/227_cyk_ambiguous_parse_count.c) | Count parses in the ambiguous grammar S -> SS | a via dynamic programming |
| 228 | [`228_epsilon_nfa_shortest_word.c`](programs/228_epsilon_nfa_shortest_word.c) | Shortest accepted word in an epsilon-NFA using zero-one BFS |
| 229 | [`229_nfa_shuffle_language.c`](programs/229_nfa_shuffle_language.c) | Recognize shuffles of the two fixed words 01 and 10 |
| 230 | [`230_dfa_file_equivalence.c`](programs/230_dfa_file_equivalence.c) | File-based DFA equivalence checking with shortest counterexample |

### Conformance testing, weighted search and Büchi witnesses (231–240)

| # | Source | Description |
|---:|---|---|
| 231 | [`231_dfa_w_method_tests.c`](programs/231_dfa_w_method_tests.c) | Construct a W-method conformance suite for a three-state DFA |
| 232 | [`232_nfa_bounded_language_comparison.c`](programs/232_nfa_bounded_language_comparison.c) | Compare two NFAs on every binary word up to a chosen length |
| 233 | [`233_weighted_shortest_accepted_word.c`](programs/233_weighted_shortest_accepted_word.c) | Dijkstra search for the least-cost word accepted by a weighted automaton |
| 234 | [`234_cfg_nullable_unit_closure.c`](programs/234_cfg_nullable_unit_closure.c) | Compute nullable nonterminals and unit-production closure of a CFG |
| 235 | [`235_ll1_parse_table_generator.c`](programs/235_ll1_parse_table_generator.c) | Compute LL(1) predictive table from a fixed grammar using FIRST and FOLLOW |
| 236 | [`236_dfa_symbol_probability.c`](programs/236_dfa_symbol_probability.c) | Compute DFA state probabilities under biased independent binary input |
| 237 | [`237_pda_bounded_configuration_bfs.c`](programs/237_pda_bounded_configuration_bfs.c) | Explore bounded pushdown configurations for the language a^n b^n |
| 238 | [`238_finite_trace_temporal_monitor.c`](programs/238_finite_trace_temporal_monitor.c) | Evaluate safety and bounded-response properties on finite binary traces |
| 239 | [`239_nfa_distinct_word_enumerator.c`](programs/239_nfa_distinct_word_enumerator.c) | Enumerate distinct NFA-accepted binary words of a specified length |
| 240 | [`240_generalized_buchi_lasso_witness.c`](programs/240_generalized_buchi_lasso_witness.c) | Construct a witness lasso visiting two Büchi acceptance sets infinitely often |

### File-based DFA analysis and transformations (241–250)

| # | Source | Description |
|---:|---|---|
| 241 | [`241_dfa_file_inclusion.c`](programs/241_dfa_file_inclusion.c) | DFA language inclusion with shortest counterexample |
| 242 | [`242_dfa_file_shortest_word.c`](programs/242_dfa_file_shortest_word.c) | Shortest accepted word via breadth-first search |
| 243 | [`243_dfa_file_word_count.c`](programs/243_dfa_file_word_count.c) | Count accepted words of specified length modulo 1,000,000,007 |
| 244 | [`244_dfa_file_scc_audit.c`](programs/244_dfa_file_scc_audit.c) | Reachable strongly connected components and accepting-cycle audit |
| 245 | [`245_dfa_file_complement.c`](programs/245_dfa_file_complement.c) | Produce a complete DFA for the complement language |
| 246 | [`246_dfa_file_intersection.c`](programs/246_dfa_file_intersection.c) | Construct the DFA product for language intersection |
| 247 | [`247_dfa_file_reachable_trim.c`](programs/247_dfa_file_reachable_trim.c) | Remove unreachable DFA states with canonical BFS numbering |
| 248 | [`248_dfa_file_minimize.c`](programs/248_dfa_file_minimize.c) | Minimize a DFA by partition refinement |
| 249 | [`249_dfa_file_state_pair_witnesses.c`](programs/249_dfa_file_state_pair_witnesses.c) | Find shortest distinguishing words for all DFA state pairs |
| 250 | [`250_dfa_file_graphviz.c`](programs/250_dfa_file_graphviz.c) | Export a DFA to Graphviz DOT |

### File-based DFA universality, word ranking, and transformations (251–260)

| # | Source | Description |
|---:|---|---|
| 251 | [`251_dfa_file_universality.c`](programs/251_dfa_file_universality.c) | DFA universality and shortest rejected-word witness |
| 252 | [`252_dfa_file_finiteness.c`](programs/252_dfa_file_finiteness.c) | Finite-language detection and exact accepted-word cardinality |
| 253 | [`253_dfa_file_reset_word.c`](programs/253_dfa_file_reset_word.c) | Shortest synchronizing word using subset BFS |
| 254 | [`254_dfa_file_word_rank.c`](programs/254_dfa_file_word_rank.c) | Accepted-word lexicographic ranking and unranking |
| 255 | [`255_dfa_file_reverse_determinize.c`](programs/255_dfa_file_reverse_determinize.c) | DFA reversal and subset determinization |
| 256 | [`256_dfa_file_symmetric_difference.c`](programs/256_dfa_file_symmetric_difference.c) | Symmetric difference product automaton |
| 257 | [`257_dfa_file_access_words.c`](programs/257_dfa_file_access_words.c) | Shortest words reaching each reachable DFA state |
| 258 | [`258_dfa_file_transition_cover.c`](programs/258_dfa_file_transition_cover.c) | BFS-based transition coverage test suite |
| 259 | [`259_dfa_file_finite_enumeration.c`](programs/259_dfa_file_finite_enumeration.c) | Finite-language enumeration in lexicographic order |
| 260 | [`260_dfa_file_inverse_homomorphism.c`](programs/260_dfa_file_inverse_homomorphism.c) | Construct inverse language images under symbol-to-word substitutions |

## Project structure

```text
Automata-C/
├── programs/                   # 260 independent C source files
├── tests/
│   ├── run_tests.py            # Tests for programs 01–20
│   ├── test_programs_21_50.py  # Tests for programs 21–50
│   └── test_programs_51_60.py  # Tests for programs 51–60
│   ├── test_programs_61_70.py # Tests for programs 61–70
│   ├── test_programs_71_80.py # Tests for programs 71–80
│   ├── test_programs_81_90.py # Tests for programs 81–90
│   ├── test_programs_91_100.py # Tests for programs 91–100
│   ├── test_programs_101_110.py # Tests for programs 101–110
│   ├── test_programs_111_120.py # Tests for programs 111–120
│   ├── test_programs_121_130.py # Tests for programs 121–130
│   ├── test_programs_131_140.py # Tests for programs 131–140
│   ├── test_programs_141_150.py # Tests for programs 141–150
│   ├── test_programs_151_160.py # Tests for programs 151–160
│   ├── test_programs_161_170.py # Tests for programs 161–170
│   ├── test_programs_171_180.py # Tests for programs 171–180
│   ├── test_programs_181_190.py # Tests for programs 181–190
│   ├── test_programs_191_200.py # Tests for programs 191–200
│   ├── test_programs_201_210.py # Tests for programs 201–210
│   ├── test_programs_211_220.py # Tests for programs 211–220
│   ├── test_programs_221_230.py # Tests for programs 221–230
│   ├── test_programs_231_240.py # Tests for programs 231–240
│   ├── test_programs_241_250.py # Tests for programs 241–250
│   └── test_programs_251_260.py # Tests for programs 251–260
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
python3 tests/test_programs_151_160.py
python3 tests/test_programs_161_170.py
python3 tests/test_programs_171_180.py
python3 tests/test_programs_181_190.py
python3 tests/test_programs_191_200.py
python3 tests/test_programs_201_210.py
python3 tests/test_programs_211_220.py
python3 tests/test_programs_221_230.py
python3 tests/test_programs_231_240.py
python3 tests/test_programs_241_250.py
python3 tests/test_programs_251_260.py
make clean
```

The extra Python scripts are separate test suites; **`make test` alone does not run all test groups**. No compiled executables are committed.

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
- [Programs 121–130](README_121_130.md)
- [Programs 131–140](README_131_140.md)
- [Programs 141–150](README_141_150.md)
- [Programs 151–160](README_151_160.md)
- [Programs 161–170](README_161_170.md)
- [Programs 171–180](README_171_180.md)
- [Programs 181–190](README_181_190.md)
- [Programs 191–200](README_191_200.md)
- [Programs 201–210](README_201_210.md)
- [Programs 211–220](README_211_220.md)
- [Programs 221–230](README_221_230.md)
- [Programs 231–240](README_231_240.md)
- [Programs 241–250](README_241_250.md)
- [Programs 251–260](README_251_260.md)

## License

[MIT License](LICENSE).
