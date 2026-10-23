#!/usr/bin/env python3
"""Automated positive/negative/invalid input tests for programs 61-70."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["61_nfa_contains_01",["01","001","010","011","101","0001","0010","0011"],["","0","1","00","10","11","000","100"]],["62_epsilon_nfa_ends_10",["10","010","110","0010","0110","1010","1110","00010"],["","0","1","00","01","11","000","001"]],["63_dfa_complement_contains_00",["","0","1","01","10","11","010","011"],["00","000","001","100","0000","0001","0010","0011"]],["64_dfa_union_ends_01_or_10",["01","10","001","010","101","110","0001","0010"],["","0","1","00","11","000","011","100"]],["65_dfa_intersection_even_zeros_and_ones",["","00","11","0000","0011","0101","0110","1001"],["0","1","01","10","000","001","010","011"]],["66_dfa_difference_contains_11_not_00",["11","011","110","111","0110","0111","1011","1101"],["","0","1","00","01","10","000","001"]],["67_dfa_symmetric_difference_parities",["0","1","000","001","010","011","100","101"],["","00","01","10","11","0000","0001","0010"]],["68_reversed_language_nfa",["10","100","101","1000","1001","1010","1011","10000"],["","0","1","00","01","11","000","001"]],["69_dfa_product_contains_00_and_ends_1",["001","0001","0011","1001","00001","00011","00101","00111"],["","0","1","00","01","10","11","000"]],["70_dfa_exactly_one_01",["01","001","010","011","101","0001","0010","0011"],["","0","1","00","10","11","000","100"]]]
total=0
for name, yes, no in cases:
    exe=root/"bin"/name
    for inputs, label in [(yes,"ACCEPT"),(no,"REJECT")]:
        for value in inputs:
            r=subprocess.run([str(exe),value],capture_output=True,text=True)
            assert r.returncode==0 and r.stdout.strip()==label,(name,value,label,r.stdout,r.stderr)
            total+=1
    r=subprocess.run([str(exe),"012"],capture_output=True,text=True)
    assert r.returncode==2,name
    total+=1
print(f"{total} checks passed")
