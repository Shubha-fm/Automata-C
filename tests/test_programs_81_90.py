#!/usr/bin/env python3
"""Check illustrative outputs for programs 81-90 after running make."""
import subprocess
from pathlib import Path
root=Path(__file__).resolve().parents[1]
cases=[["81_dfa_transition_trace","final=0"],["82_dfa_language_emptiness","EMPTY"],["83_dfa_universality","NOT UNIVERSAL"],["84_dfa_finite_language","FINITE"],["85_nfa_epsilon_closure_set","closure: q0 q1 q2 q3 q4"],["86_dfa_inclusion_counterexample","NOT INCLUDED: 1"],["87_dfa_shortest_distinguishing_word","WITNESS: 1"],["88_nfa_bitset_simulation","ACCEPT"],["89_moore_machine","output: 0 1 0 1 1 0"],["90_mealy_machine","output: 1 1 1 0 1"]]
for name,fragment in cases:
    result=subprocess.run([str(root/'bin'/name)],capture_output=True,text=True,timeout=5)
    assert result.returncode==0 and fragment in result.stdout,(name,result.stdout,result.stderr)
print(f'{len(cases)} new program checks passed')
