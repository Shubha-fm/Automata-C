#!/usr/bin/env python3
"""Regression suite for examples 181-190; uses no external packages."""
from pathlib import Path
import subprocess
import tempfile
ROOT = Path(__file__).resolve().parents[1]
def run(name,*arguments):
    return subprocess.run([str(ROOT/"bin"/name),*arguments],
                          capture_output=True,text=True,timeout=10)
cases=[
 ("181_weighted_nfa_min_cost",["01"],"MIN_COST=4",0),
 ("181_weighted_nfa_min_cost",["010"],"MIN_COST=5",0),
 ("181_weighted_nfa_min_cost",["111"],"NO_ACCEPTING_PATH",0),
 ("181_weighted_nfa_min_cost",["x"],"Binary alphabet only",2),
 ("182_probabilistic_finite_automaton",["1"],"P_ACCEPT=0.800000 DECISION=ACCEPT",0),
 ("182_probabilistic_finite_automaton",["0"],"P_ACCEPT=0.100000 DECISION=REJECT",0),
 ("182_probabilistic_finite_automaton",[""],"P_ACCEPT=0.000000 DECISION=REJECT",0),
 ("183_mealy_binary_to_gray",["1011"],"GRAY=1110",0),
 ("183_mealy_binary_to_gray",[""],"GRAY=",0),
 ("184_mealy_bit_stuffing",["111111"],"STUFFED=1111101",0),
 ("184_mealy_bit_stuffing",["111110"],"STUFFED=1111100",0),
 ("185_mealy_bit_unstuffing",["1111101"],"UNSTUFFED=111111",0),
 ("185_mealy_bit_unstuffing",["1111100"],"UNSTUFFED=111110",0),
 ("185_mealy_bit_unstuffing",["11111"],"Missing terminal",2),
 ("185_mealy_bit_unstuffing",["111111"],"Missing stuffed zero",2),
 ("186_levenshtein_automaton_distance_one",["101","101"],"DISTANCE=0 ACCEPT",0),
 ("186_levenshtein_automaton_distance_one",["101","1001"],"DISTANCE=1 ACCEPT",0),
 ("186_levenshtein_automaton_distance_one",["101","000"],"DISTANCE=2 REJECT",0),
 ("187_trie_keyword_dfa",["while"],"ACCEPT",0),
 ("187_trie_keyword_dfa",["return"],"ACCEPT",0),
 ("187_trie_keyword_dfa",["whiles"],"REJECT",0),
 ("187_trie_keyword_dfa",["If"],"REJECT",0),
 ("188_timed_automaton_guard",["0,4,9"],"SAFE",0),
 ("188_timed_automaton_guard",["0,5,16"],"UNSAFE",0),
 ("188_timed_automaton_guard",["9,7"],"UNSAFE",0),
 ("188_timed_automaton_guard",["0,foo"],"Invalid",2),
 ("188_timed_automaton_guard",["0,"],"Trailing comma",2),
 ("189_buchi_accepting_lasso",[],"PREFIX=q0->q1",0),
 ("189_buchi_accepting_lasso",[],"CYCLE=q1->q1",0),
 ("189_buchi_accepting_lasso",[],"BUCHI_NONEMPTY=YES",0),
]
passed=0
for name,args,expected,exit_code in cases:
    result=run(name,*args)
    output=result.stdout if exit_code==0 else result.stderr
    assert result.returncode==exit_code and expected in output,(
        name,args,result.returncode,result.stdout,result.stderr)
    passed+=1
with tempfile.TemporaryDirectory() as directory:
    valid=Path(directory)/"valid.dfa"
    valid.write_text("3 0\n0 0 1\n0 0 1\n0 1 0\n1 0 1\n1 1 2\n2 0 1\n2 1 0\n")
    duplicate=Path(directory)/"duplicate.dfa"
    duplicate.write_text("2 0\n0 1\n0 0 1\n0 0 1\n1 0 0\n1 1 1\n")
    incomplete=Path(directory)/"incomplete.dfa"
    incomplete.write_text("2 0\n0 1\n0 0 1\n0 1 0\n1 0 1\n")
    for path,wanted,code in [
        (valid,"VALID STATES=3",0),
        (duplicate,"INVALID",1),
        (incomplete,"INVALID",1),
    ]:
        proc=run("190_dfa_transition_validator",str(path))
        assert proc.returncode==code and wanted in proc.stdout,(
            path,proc.returncode,proc.stdout,proc.stderr)
        passed+=1
print(f"{passed} regression checks passed")
