#!/usr/bin/env python3
"""Regression tests for programs 231-240 (standard library only)."""
from pathlib import Path
from itertools import product
import subprocess
BIN=Path(__file__).resolve().parents[1]/"bin"
checks=0
def run(program,args,expected,rc=0):
    global checks
    proc=subprocess.run([str(BIN/program),*map(str,args)],
                        capture_output=True,text=True,timeout=15)
    out=proc.stdout if rc==0 else proc.stderr
    assert proc.returncode==rc and expected in out,(
        program,args,expected,rc,proc.returncode,proc.stdout,proc.stderr)
    checks+=1
    return proc.stdout

result=run("231_dfa_w_method_tests",[],"KILLED_MUTANTS=3/3")
for i in range(1,4):
    assert f"MUTANT_{i}=SURVIVED" not in result
run("232_nfa_bounded_language_comparison",[0],"EQUIVALENT_UP_TO=0 CHECKED=1")
run("232_nfa_bounded_language_comparison",[10],"EQUIVALENT_UP_TO=10 CHECKED=2047")
run("232_nfa_bounded_language_comparison",[10,"mutant"],"MISMATCH=01")
run("232_nfa_bounded_language_comparison",[16],"Length must",2)
run("233_weighted_shortest_accepted_word",[],"MIN_COST=3 WORD=01")
run("233_weighted_shortest_accepted_word",["unreachable"],"NO_ACCEPTED_WORD")
run("234_cfg_nullable_unit_closure",[],"S NULLABLE=YES UNIT=SAB TERMINALS=ab")
run("234_cfg_nullable_unit_closure",[],"A NULLABLE=YES UNIT=AB TERMINALS=a")
run("234_cfg_nullable_unit_closure",[],"B NULLABLE=YES UNIT=AB TERMINALS=a")
run("235_ll1_parse_table_generator",[],"E,i=TR")
run("235_ll1_parse_table_generator",[],"R,+=+TR")
run("235_ll1_parse_table_generator",[],"R,$=epsilon")
run("235_ll1_parse_table_generator",[],"T,i=i")
run("235_ll1_parse_table_generator",[],"ENTRIES=4 CONFLICTS=0")
for n,p,even,odd in [
    (0,"0.3",1.0,0.0),(1,"0.3",.7,.3),(2,"0.3",.58,.42),
    (5,"0",1.0,0.0),(5,"1",0.0,1.0),(2,"0.5",.5,.5)
]:
    run("236_dfa_symbol_probability",[n,p],
        f"P_EVEN={even:.6f} P_ODD={odd:.6f}")
run("236_dfa_symbol_probability",["10","1.5"],"Probability must",2)
run("236_dfa_symbol_probability",["-1","0.3"],"Invalid number of steps",2)
for n in range(0,9):
    for chars in product("ab",repeat=n):
        word="".join(chars)
        accept=(n%2==0 and word=="a"*(n//2)+"b"*(n//2))
        run("237_pda_bounded_configuration_bfs",[word],
            "ACCEPT" if accept else "REJECT")
run("237_pda_bounded_configuration_bfs",["aac"],"Alphabet must",2)
for n in range(0,8):
    for chars in product("01",repeat=n):
        word="".join(chars)
        no11="PASS" if "11" not in word else "FAIL"
        has01="YES" if "01" in word else "NO"
        response="PASS" if all(
            i+1<len(word) and word[i+1]=="0"
            for i,c in enumerate(word) if c=="1") else "FAIL"
        run("238_finite_trace_temporal_monitor",[word],
            f"NO_11={no11} HAS_01={has01} RESPONSE={response}")
run("238_finite_trace_temporal_monitor",["1a"],"Binary trace required",2)
for n in range(0,10):
    out=run("239_nfa_distinct_word_enumerator",[n],"TOTAL=")
    words=["".join(chars) for chars in product("01",repeat=n)
           if "01" in "".join(chars)]
    actual=[line[5:] for line in out.splitlines() if line.startswith("WORD=")]
    assert actual==words,(n,len(actual),len(words),actual[:10])
    assert f"TOTAL={len(words)}" in out,(n,out[-50:])
run("239_nfa_distinct_word_enumerator",[13],"Length must",2)
run("240_generalized_buchi_lasso_witness",[],
    "GENERALIZED_BUCHI_NONEMPTY=YES PREFIX=0 CYCLE=10")
run("240_generalized_buchi_lasso_witness",["no_cycle"],
    "GENERALIZED_BUCHI_NONEMPTY=NO")
print(f"{checks} regression checks passed")
