# Programs 71–80: Automata Algorithms

Each program is a standalone C11 demonstration using a built-in example machine; unlike recognizer programs 01–70, these print computed automata results and do not accept binary strings as CLI arguments.

- [71_epsilon_closure.c](programs/71_epsilon_closure.c): Compute epsilon closure of NFA state sets
- [72_nfa_subset_construction.c](programs/72_nfa_subset_construction.c): Convert sample NFA to DFA by subset construction
- [73_dfa_reachable_states.c](programs/73_dfa_reachable_states.c): Find reachable DFA states with BFS
- [74_dfa_minimization.c](programs/74_dfa_minimization.c): Minimize a sample DFA with partition refinement
- [75_dfa_equivalence.c](programs/75_dfa_equivalence.c): Check sample DFA equivalence by product-state BFS
- [76_dfa_complement_table.c](programs/76_dfa_complement_table.c): Construct complement accepting states
- [77_dfa_product_intersection.c](programs/77_dfa_product_intersection.c): Construct product automaton for even zeros AND even ones
- [78_dfa_shortest_word.c](programs/78_dfa_shortest_word.c): Find shortest accepted word using BFS
- [79_dfa_enumerate_length_3.c](programs/79_dfa_enumerate_length_3.c): Enumerate accepted binary strings of length three
- [80_dfa_distinguishable_pairs.c](programs/80_dfa_distinguishable_pairs.c): Table-filling distinguishability for DFA states

## Run

```sh
make
./bin/74_dfa_minimization
python3 tests/test_programs_71_80.py
```

These are educational fixed-size examples, not general-purpose parsers for arbitrary automata specifications.
