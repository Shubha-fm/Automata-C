#!/usr/bin/env python3
"""Regression tests for programs 201-210."""
from pathlib import Path
import subprocess
import tempfile
import itertools

BIN=Path(__file__).resolve().parents[1]/"bin"
def run(program,*args):
    return subprocess.run([str(BIN/program),*map(str,args)],
                          capture_output=True,text=True,timeout=10)
checks=0
def assert_output(program,args,expected,rc=0):
    global checks
    p=run(program,*args)
    output=p.stdout if rc==0 else p.stderr
    assert p.returncode==rc and expected in output,(
        program,args,rc,expected,p.returncode,p.stdout,p.stderr)
    checks+=1

for length in range(0,8):
    accepted=["".join(bits) for bits in itertools.product("01",repeat=length)
              if sum(int(bit) for bit in bits)%2==0]
    for rank,word in enumerate(accepted):
        assert_output("201_dfa_accepted_word_rank",[word],
                      f"RANK={rank} TOTAL={len(accepted)}")
assert_output("201_dfa_accepted_word_rank",["111"],"REJECT")
assert_output("201_dfa_accepted_word_rank",["01x"],"Binary alphabet only",2)

assert_output("202_dfa_transition_monoid",[],"MONOID_SIZE=5")
for n,answer in [(0,0.0),(1,0.0),(2,0.25),(3,0.25),(8,0.25)]:
    assert_output("203_dfa_iid_accept_probability",[n],f"P_ACCEPT={answer:.6f}")
assert_output("203_dfa_iid_accept_probability",["abc"],"Invalid length",2)
assert_output("204_nfa_language_inclusion_witness",[],"NOT_INCLUDED WITNESS=01")
for word,expected in [("","REJECT"),("a","ACCEPT"),("b","REJECT"),
                      ("aba","ACCEPT"),("abb","REJECT")]:
    assert_output("205_dfa_inverse_homomorphism",[word],expected)
assert_output("205_dfa_inverse_homomorphism",["abc"],"Alphabet",2)
for word,output in [("","DERIVATIVE=ZERO_STAR_ONE REJECT"),
                    ("0001","DERIVATIVE=EPSILON ACCEPT"),
                    ("11","DERIVATIVE=EMPTY REJECT")]:
    assert_output("206_regex_brzozowski_derivative",[word],output)
assert_output("206_regex_brzozowski_derivative",["012"],"Binary alphabet only",2)
for target,word,expected in [("101","101","DISTANCE=0 ACCEPT"),
                             ("101","111","DISTANCE=1 ACCEPT"),
                             ("101","000","DISTANCE=2 REJECT"),
                             ("01","001","DISTANCE=UNDEFINED REJECT")]:
    assert_output("207_dfa_hamming_distance_one",[target,word],expected)
for prefix,loop,expected in [("","01","BUCHI_ACCEPT=YES"),
                             ("","10","BUCHI_ACCEPT=YES"),
                             ("","00","BUCHI_ACCEPT=NO"),
                             ("01","0","BUCHI_ACCEPT=NO")]:
    assert_output("208_buchi_ultimately_periodic_word",[prefix,loop],expected)
assert_output("208_buchi_ultimately_periodic_word",["",""],"nonempty binary loop",2)
for word,expected in [("ab","TREE=S(A(a),B(b))"),
                      ("ba","TREE=S(B(b),C(a))"),
                      ("baaba","TREE=S("),
                      ("aaaa","REJECT"),("","REJECT")]:
    assert_output("209_cyk_parse_tree_witness",[word],expected)
with tempfile.TemporaryDirectory() as td:
    partial=Path(td)/"partial.dfa"
    partial.write_text("2 0\n0 1\n1 -1\n1 0\n")
    complete=Path(td)/"complete.dfa"
    complete.write_text("2 0\n0 1\n1 0\n1 0\n")
    bad=Path(td)/"bad.dfa"
    bad.write_text("2 0\n0 1\n3 0\n1 0\n")
    assert_output("210_partial_dfa_sink_completion",[partial],"STATES=3 START=0 SINK=2")
    assert_output("210_partial_dfa_sink_completion",[partial],"COMPLETED=1")
    assert_output("210_partial_dfa_sink_completion",[complete],"STATES=2 START=0 SINK=NONE")
    assert_output("210_partial_dfa_sink_completion",[bad],"Invalid transition",2)
print(f"{checks} regression checks passed")
