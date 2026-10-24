#!/usr/bin/env python3
from pathlib import Path
import subprocess
base=Path(__file__).resolve().parents[1]/'bin'
cases=["71_epsilon_closure","72_nfa_subset_construction","73_dfa_reachable_states","74_dfa_minimization","75_dfa_equivalence","76_dfa_complement_table","77_dfa_product_intersection","78_dfa_shortest_word","79_dfa_enumerate_length_3","80_dfa_distinguishable_pairs"]
for name in cases:
    p=subprocess.run([str(base/name)],capture_output=True,text=True,timeout=5)
    assert p.returncode==0 and p.stdout.strip(),(name,p.stderr)
print(f'{len(cases)} example executions passed')
