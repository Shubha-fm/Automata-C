#!/usr/bin/env python3
"""Runtime regression tests for programs 191-200 (standard library only)."""
from pathlib import Path
import subprocess
import itertools
ROOT=Path(__file__).resolve().parents[1]/"bin"
def check(program,args,expected,rc=0):
    p=subprocess.run([str(ROOT/program),*map(str,args)],capture_output=True,text=True,timeout=10)
    got=p.stdout if rc==0 else p.stderr
    assert p.returncode==rc and expected in got,(program,args,p.returncode,p.stdout,p.stderr,expected)
counter=0
def test(program,args,expected,rc=0):
    global counter
    check(program,args,expected,rc)
    counter+=1
test("191_hopcroft_dfa_minimization",[],"MIN_STATES=3")
for n in range(0,40):
    expected=1 if n==0 else pow(2,n-1,1000000007)
    test("192_dfa_matrix_word_count",[n],f"ACCEPTED_MOD={expected}")
test("192_dfa_matrix_word_count",["-1"],"Invalid length",2)
test("193_nfa_dfa_exact_equivalence",[],"EQUIVALENT")
test("193_nfa_dfa_exact_equivalence",["mutant"],"COUNTEREXAMPLE=0")
test("194_nfa_shortest_accepted_word",[],"SHORTEST=01")
for n in range(0,8):
    accepted=["".join(word) for word in itertools.product("01",repeat=n)
              if sum(bit=="1" for bit in word)%2==0]
    for k,word in enumerate(accepted):
        test("195_dfa_lexicographic_unranking",[n,k],f"WORD={word} TOTAL={len(accepted)}")
test("195_dfa_lexicographic_unranking",[3,4],"Rank out of range",2)
test("196_nfa_ambiguity_witness",[],"AMBIGUOUS_WORD=0 PATHS=2")
test("197_generalized_buchi_scc",[],"GENERALIZED_BUCHI_NONEMPTY=YES")
for n in range(0,7):
    for bits in itertools.product("01",repeat=n):
        word="".join(bits)
        complement="".join("0" if b=="1" else "1" for b in word)
        gray="".join(str(int(complement[i]) ^ (int(complement[i-1]) if i else 0))
                     for i in range(n))
        test("198_mealy_transducer_composition",[word],
             f"INTERMEDIATE={complement} COMPOSED_GRAY={gray}")
test("198_mealy_transducer_composition",["012"],"Binary only",2)
test("199_cfg_cyk_membership",["baaba"],"ACCEPT")
test("199_cfg_cyk_membership",["bbbbb"],"REJECT")
test("199_cfg_cyk_membership",["aaa"],"ACCEPT")
test("199_cfg_cyk_membership",["aaaa"],"REJECT")
test("199_cfg_cyk_membership",["abc"],"Alphabet is",2)
test("200_dfa_reachability_productivity_audit",[],
     "REACHABLE=4 PRODUCTIVE=3 DEAD=1 UNREACHABLE=2")
print(f"{counter} regression checks passed")
