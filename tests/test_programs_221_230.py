#!/usr/bin/env python3
"""Regression tests for programs 221-230."""
from pathlib import Path
from itertools import product
import subprocess
import tempfile
BIN=Path(__file__).resolve().parents[1]/"bin"
count=0
def check(program,args,expected,code=0):
    global count
    p=subprocess.run([str(BIN/program),*map(str,args)],
                     capture_output=True,text=True,timeout=10)
    value=p.stdout if code==0 else p.stderr
    assert p.returncode==code and expected in value,(program,args,expected,p.returncode,p.stdout,p.stderr)
    count+=1

for m,expected in [(1,"MUTANT_1=0"),(2,"MUTANT_2=01"),(3,"MUTANT_3=<epsilon>")]:
    check("221_dfa_mutation_test_suite",[],expected)
check("222_nfa_universality_counterexample",[],"NOT_UNIVERSAL WITNESS=11")
check("222_nfa_universality_counterexample",["universal"],"UNIVERSAL")
check("223_nfa_intersection_witness",[],"INTERSECTION_WITNESS=010")
check("224_moore_machine_equivalence",[],"EQUIVALENT")
check("224_moore_machine_equivalence",["mutant"],"OUTPUT_MISMATCH_WITNESS=1")
check("225_cfg_first_follow_sets",[],"S FIRST={a,b,c} FOLLOW={$}")
check("225_cfg_first_follow_sets",[],"A FIRST={a,eps} FOLLOW={b,c}")
check("225_cfg_first_follow_sets",[],"B FIRST={b,c} FOLLOW={$}")
for n in range(0,20):
    valid="a"*n+"b"*n
    check("226_ll1_predictive_parser",[valid],f"ACCEPT EXPANSIONS={n+1}")
for invalid in ("ba","aab","abb","abab","aabbba"):
    check("226_ll1_predictive_parser",[invalid],"REJECT")
check("226_ll1_predictive_parser",["aabx"],"Alphabet must be",2)
catalan=[0,1,1,2,5,14,42,132,429,1430,4862,16796]
for n in range(0,12):
    check("227_cyk_ambiguous_parse_count",["a"*n],
          f"PARSES={catalan[n]} AMBIGUOUS={'YES' if n>=3 else 'NO'}")
check("227_cyk_ambiguous_parse_count",["aaab"],"PARSES=0 AMBIGUOUS=NO")
check("228_epsilon_nfa_shortest_word",[],"SHORTEST=01 LENGTH=2")
def shuffle_paths(word):
    a,b="01","10"
    dp={(0,0):1}
    for symbol in word:
        nd={}
        for (i,j),count in dp.items():
            if i<2 and symbol==a[i]:
                nd[(i+1,j)]=nd.get((i+1,j),0)+count
            if j<2 and symbol==b[j]:
                nd[(i,j+1)]=nd.get((i,j+1),0)+count
        dp=nd
    return dp.get((2,2),0)
for n in range(0,7):
    for letters in product("01",repeat=n):
        word="".join(letters)
        paths=shuffle_paths(word)
        check("229_nfa_shuffle_language",[word],
              f"{'ACCEPT' if paths else 'REJECT'} PATHS={paths}")
check("229_nfa_shuffle_language",["0x"],"Binary alphabet only",2)
with tempfile.TemporaryDirectory() as folder:
    root=Path(folder)
    ends01=root/"ends01.dfa"
    ends10=root/"ends10.dfa"
    ends01.write_text("3 0\n0 0 1\n1 0\n1 2\n1 0\n")
    ends10.write_text("3 0\n0 0 1\n0 1\n2 1\n0 1\n")
    check("230_dfa_file_equivalence",[ends01,ends01],"EQUIVALENT")
    check("230_dfa_file_equivalence",[ends01,ends10],
          "NOT_EQUIVALENT WITNESS=01")
    invalid=root/"invalid.dfa"
    invalid.write_text("3 0\n0 0 1\n0 1\n")
    check("230_dfa_file_equivalence",[ends01,invalid],"Invalid DFA input files",2)
print(f"{count} regression checks passed")
