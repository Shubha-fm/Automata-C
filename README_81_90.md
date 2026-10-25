# Automata programs 81–90

These programs are self-contained C11 demonstrations with built-in automata.

- [81_dfa_transition_trace.c](programs/81_dfa_transition_trace.c): Trace transitions for input 1010
- [82_dfa_language_emptiness.c](programs/82_dfa_language_emptiness.c): Check emptiness using reachable accepting states
- [83_dfa_universality.c](programs/83_dfa_universality.c): Check whether every binary string is accepted
- [84_dfa_finite_language.c](programs/84_dfa_finite_language.c): Detect productive cycles to test language finiteness
- [85_nfa_epsilon_closure_set.c](programs/85_nfa_epsilon_closure_set.c): Compute epsilon-closure of a chosen state set
- [86_dfa_inclusion_counterexample.c](programs/86_dfa_inclusion_counterexample.c): Find counterexample to DFA language inclusion
- [87_dfa_shortest_distinguishing_word.c](programs/87_dfa_shortest_distinguishing_word.c): Find shortest word distinguishing two DFAs
- [88_nfa_bitset_simulation.c](programs/88_nfa_bitset_simulation.c): Simulate an NFA on 0101 using bit sets
- [89_moore_machine.c](programs/89_moore_machine.c): Generate Moore machine outputs for 10110
- [90_mealy_machine.c](programs/90_mealy_machine.c): Generate Mealy machine outputs for 10110

Run `make` then `python3 tests/test_programs_81_90.py` or execute an individual program such as `./bin/86_dfa_inclusion_counterexample`.

The finiteness demo (84) uses a fixed machine and checks self-loops on productive states; it is not a general finiteness decision procedure. These examples are designed for learning, not arbitrary input automata.
