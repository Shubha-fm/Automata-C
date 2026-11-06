#!/usr/bin/env python3
"""Regression tests for standalone C11 programs 211-220."""
from pathlib import Path
from itertools import product
import subprocess
import tempfile

BIN=Path(__file__).resolve().parents[1]/"bin"
checks=0
def check(name,argv,expected,exit_code=0):
    global checks
    result=subprocess.run([str(BIN/name),*map(str,argv)],
                          capture_output=True,text=True,timeout=12)
    actual=result.stdout if exit_code==0 else result.stderr
    assert result.returncode==exit_code and expected in actual,(
        name,argv,expected,exit_code,result.returncode,result.stdout,result.stderr)
    checks+=1

check("211_dfa_pumping_witness",[],"X=0 Y=0 Z=1")
for k in range(4):
    check("211_dfa_pumping_witness",[],f"k={k} WORD={'0'*(k+1)}1 ACCEPT")

for n in range(0,13):
    expected=sum("01" in "".join(word) for word in product("01",repeat=n))
    check("212_nfa_count_distinct_words",[n],f"DISTINCT_ACCEPTED={expected}")
check("212_nfa_count_distinct_words",["41"],"Length must",2)

for n in range(0,8):
    for symbols in product("01",repeat=n):
        word="".join(symbols)
        accepted=["".join(candidate) for candidate in product("01",repeat=n)
                  if sum(int(x) for x in candidate)%2==0]
        successor=next((v for v in accepted if v>word),None)
        check("213_dfa_next_accepted_word",[word],
              f"NEXT={successor}" if successor is not None else "NO_SUCCESSOR")
check("213_dfa_next_accepted_word",["2"],"Binary input only",2)

for word,answer in [("01","MIN_COST=4 PATH=q0->q1->q2"),
                    ("001","MIN_COST=5 PATH=q0->q1->q1->q2"),
                    ("111","NO_ACCEPTING_PATH"),
                    ("","NO_ACCEPTING_PATH")]:
    check("214_weighted_nfa_viterbi_path",[word],answer)
check("214_weighted_nfa_viterbi_path",["12"],"Binary alphabet only",2)

check("215_dfa_pair_synchronization",[],"MERGEABLE_PAIRS=6/6 SYNCHRONIZING=YES")
check("215_dfa_pair_synchronization",["permutation"],
      "MERGEABLE_PAIRS=0/6 SYNCHRONIZING=NO")
check("216_nfa_exact_ambiguity",[],"AMBIGUOUS_WORD=0")
check("216_nfa_exact_ambiguity",["unambiguous"],"UNAMBIGUOUS")

for n in range(0,6):
    for word in product("ab",repeat=n):
        s="".join(word)
        valid=(len(s)%2==0 and s=="a"*(len(s)//2)+"b"*(len(s)//2))
        check("217_earley_cfg_membership",[s],"ACCEPT" if valid else "REJECT")
check("217_earley_cfg_membership",["abc"],"Alphabet is",2)

with tempfile.TemporaryDirectory() as directory:
    grammar=Path(directory)/"sample.rg"
    grammar.write_text("S\n4\nS 0 S\nS 1 A\nA 0 A\nA 1 #\n")
    for word,wanted in [("11","ACCEPT"),("001001","ACCEPT"),
                        ("01","REJECT"),("10","REJECT"),("","REJECT")]:
        check("218_regular_grammar_to_nfa",[grammar,word],wanted)
    epsilon=Path(directory)/"epsilon.rg"
    epsilon.write_text("S\n1\nS e #\n")
    check("218_regular_grammar_to_nfa",[epsilon,""],"ACCEPT")
    check("218_regular_grammar_to_nfa",[epsilon,"0"],"REJECT")
    bad=Path(directory)/"bad.rg"
    bad.write_text("S\n1\nS x A\n")
    check("218_regular_grammar_to_nfa",[bad,""],"Expected 0, 1 or e",2)

check("219_nfa_epsilon_elimination",[],"CHECKED=2047 MISMATCHES=0")
check("220_dfa_finite_language_cardinality",[],
      "LANGUAGE=FINITE COUNT=2 MAX_LENGTH=2")
check("220_dfa_finite_language_cardinality",["infinite"],"LANGUAGE=INFINITE")

print(f"{checks} regression checks passed")
