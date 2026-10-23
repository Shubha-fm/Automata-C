# Programs 61–70

New examples of NFA and ε-NFA simulation, complement, union, intersection, difference, symmetric difference, reversed languages, product-language recognition, and counting substring occurrences.

- [61_nfa_contains_01.c](programs/61_nfa_contains_01.c): NFA simulation: contains 01
- [62_epsilon_nfa_ends_10.c](programs/62_epsilon_nfa_ends_10.c): Epsilon-NFA simulation: ends in 10
- [63_dfa_complement_contains_00.c](programs/63_dfa_complement_contains_00.c): DFA complement: strings avoiding 00
- [64_dfa_union_ends_01_or_10.c](programs/64_dfa_union_ends_01_or_10.c): DFA union: ends 01 or 10
- [65_dfa_intersection_even_zeros_and_ones.c](programs/65_dfa_intersection_even_zeros_and_ones.c): DFA intersection: even zeros and ones
- [66_dfa_difference_contains_11_not_00.c](programs/66_dfa_difference_contains_11_not_00.c): DFA difference: contains 11 but not 00
- [67_dfa_symmetric_difference_parities.c](programs/67_dfa_symmetric_difference_parities.c): DFA symmetric difference: odd zeros XOR odd ones
- [68_reversed_language_nfa.c](programs/68_reversed_language_nfa.c): NFA for reversed language of strings ending 01 (starts 10)
- [69_dfa_product_contains_00_and_ends_1.c](programs/69_dfa_product_contains_00_and_ends_1.c): Product DFA: contains 00 and ends with 1
- [70_dfa_exactly_one_01.c](programs/70_dfa_exactly_one_01.c): DFA counting exactly one occurrence of 01

Compile with `make` and run `python3 tests/test_programs_61_70.py`. Note that some language operations are implemented directly as recognizers, not as general-purpose automata-construction APIs.
