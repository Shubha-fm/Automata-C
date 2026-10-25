# Programs 91–100

Additional pushdown-language demonstrations, a simple fixed grammar recognizer, regular-expression language recognition and digit-alphabet DFAs.

- [91_pda_balanced_parentheses.c](programs/91_pda_balanced_parentheses.c): Pushdown automaton for balanced parentheses
- [92_pda_anbn.c](programs/92_pda_anbn.c): Pushdown recognition of a^n b^n (n>=0)
- [93_pda_palindrome_with_separator.c](programs/93_pda_palindrome_with_separator.c): Pushdown recognition of w#w^R
- [94_cfg_cyk_ab.c](programs/94_cfg_cyk_ab.c): CYK-style membership for grammar S -> AB, A -> a, B -> b
- [95_regex_thompson_01star.c](programs/95_regex_thompson_01star.c): Recognition of regex 0(1)* (fixed Thompson-language example)
- [96_dfa_decimal_mod_3.c](programs/96_dfa_decimal_mod_3.c): Decimal digit DFA modulo 3
- [97_dfa_hex_mod_5.c](programs/97_dfa_hex_mod_5.c): Hexadecimal digit DFA modulo 5
- [98_dfa_ternary_mod_4.c](programs/98_dfa_ternary_mod_4.c): Ternary digit DFA modulo 4
- [99_dfa_identifier.c](programs/99_dfa_identifier.c): DFA for ASCII identifiers [A-Za-z_][A-Za-z0-9_]*
- [100_dfa_binary_multiple_11.c](programs/100_dfa_binary_multiple_11.c): Binary-number DFA modulo 11

Run `make` and `python3 tests/test_programs_91_100.py`. These are purpose-built recognizers, not full generic PDA, CYK, or Thompson construction libraries.
