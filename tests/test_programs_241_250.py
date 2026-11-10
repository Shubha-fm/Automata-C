#!/usr/bin/env python3
"""File-based DFA interoperability and regression tests for programs 241-250."""
from pathlib import Path
from itertools import product
import subprocess
import tempfile

BIN=Path(__file__).resolve().parents[1]/"bin"
checks=0
def run(n,*args,expected=None,rc=0):
    global checks
    command=[str(BIN/n),*map(str,args)]
    p=subprocess.run(command,capture_output=True,text=True,timeout=10)
    assert p.returncode==rc,(command,p.returncode,p.stdout,p.stderr)
    if expected is not None:
        output=p.stdout if rc==0 else p.stderr
        assert expected in output,(command,expected,p.stdout,p.stderr)
    checks+=1
    return p.stdout

def parse(text):
    nums=list(map(int,text.split()))
    n,start=nums[:2]
    assert 1<=n<=32 and len(nums)==2+n+2*n
    flags=nums[2:2+n]
    jumps=[nums[2+n+2*i:2+n+2*i+2] for i in range(n)]
    assert 0<=start<n and all(x in (0,1) for x in flags)
    assert all(0<=x<n for row in jumps for x in row)
    return n,start,flags,jumps

def accepts(model,word):
    _,q,flags,jumps=parse(model)
    for bit in word:q=jumps[q][int(bit)]
    return bool(flags[q])

with tempfile.TemporaryDirectory() as folder:
    tmp=Path(folder)
    def save(name,text):
        f=tmp/name;f.write_text(text);return f
    ends01=save("ends01.dfa","3 0\n0 0 1\n1 0\n1 2\n1 0\n")
    contains01=save("contains01.dfa","3 0\n0 0 1\n1 0\n1 2\n2 2\n")
    universal=save("all.dfa","1 0\n1\n0 0\n")
    empty=save("empty.dfa","1 0\n0\n0 0\n")
    even=save("even.dfa","2 0\n1 0\n0 1\n1 0\n")
    finite=save("finite.dfa","3 0\n0 1 0\n1 2\n2 2\n2 2\n")
    unreachable=save("unreachable.dfa","4 0\n0 0 1 1\n1 0\n1 2\n1 0\n3 3\n")
    dup=save("duplicate.dfa","4 0\n0 1 0 1\n2 1\n2 1\n0 3\n0 3\n")
    large=save("large.dfa","6 0\n1 0 0 0 0 0\n"+
                "0 0\n"*6)
    invalid=save("invalid.dfa","2 0\n0 1\n0 1\n")  # missing transition row

    run("241_dfa_file_inclusion",ends01,contains01,expected="INCLUDED")
    run("241_dfa_file_inclusion",contains01,ends01,expected="NOT_INCLUDED WITNESS=010")
    run("241_dfa_file_inclusion",universal,ends01,expected="NOT_INCLUDED WITNESS=<epsilon>")
    run("241_dfa_file_inclusion",empty,ends01,expected="INCLUDED")
    run("241_dfa_file_inclusion",ends01,invalid,expected="Invalid DFA file",rc=2)
    for path,expected in [(ends01,"SHORTEST=01"),(universal,"SHORTEST=<epsilon>"),
                          (empty,"EMPTY_LANGUAGE"),(finite,"SHORTEST=0")]:
        run("242_dfa_file_shortest_word",path,expected=expected)

    for n in range(0,15):
        run("243_dfa_file_word_count",ends01,n,
            expected=f"ACCEPTED_MOD={2**(n-2) if n>=2 else 0}")
        run("243_dfa_file_word_count",even,n,
            expected=f"ACCEPTED_MOD={2**(n-1) if n>=1 else 1}")
    run("243_dfa_file_word_count",even,-1,expected="Length must",rc=2)
    run("243_dfa_file_word_count",even,100001,expected="Length must",rc=2)
    run("244_dfa_file_scc_audit",ends01,
        expected="REACHABLE=3 SCCS=1 CYCLIC=1 ACCEPTING_CYCLIC=1")
    run("244_dfa_file_scc_audit",finite,
        expected="REACHABLE=3 SCCS=3 CYCLIC=1 ACCEPTING_CYCLIC=0")

    complement=run("245_dfa_file_complement",ends01)
    parse(complement)
    complement_file=save("complement.dfa",complement)
    twice=run("245_dfa_file_complement",complement_file)
    assert parse(twice)==parse(ends01.read_text())
    for n in range(0,8):
        for bits in product("01",repeat=n):
            word="".join(bits)
            assert accepts(ends01.read_text(),word)!=accepts(complement,word)
            checks+=1
    run("242_dfa_file_shortest_word",complement_file,expected="SHORTEST=<epsilon>")
    cross=run("246_dfa_file_intersection",ends01,contains01)
    cross_file=save("cross.dfa",cross)
    assert parse(cross)[0]==9
    for n in range(0,8):
        for bits in product("01",repeat=n):
            word="".join(bits)
            assert accepts(cross,word)==(
                accepts(ends01.read_text(),word) and
                accepts(contains01.read_text(),word))
            checks+=1
    run("246_dfa_file_intersection",large,large,
        expected="Product exceeds 32 states",rc=2)
    intersect_empty=run("246_dfa_file_intersection",ends01,empty)
    empty_product=save("empty_product.dfa",intersect_empty)
    run("242_dfa_file_shortest_word",empty_product,expected="EMPTY_LANGUAGE")

    trimmed=run("247_dfa_file_reachable_trim",unreachable)
    assert parse(trimmed)[0]==3
    assert parse(trimmed)[1]==0
    for n in range(0,6):
        for bits in product("01",repeat=n):
            word="".join(bits)
            assert accepts(trimmed,word)==accepts(unreachable.read_text(),word)
            checks+=1

    minimized=run("248_dfa_file_minimize",dup)
    assert parse(minimized)[0]==2
    for n in range(0,8):
        for bits in product("01",repeat=n):
            word="".join(bits)
            assert accepts(minimized,word)==accepts(dup.read_text(),word)
            checks+=1
    minimal_ends=run("248_dfa_file_minimize",ends01)
    assert parse(minimal_ends)[0]==3
    run("249_dfa_file_state_pair_witnesses",ends01,expected="q0,q1=1")
    run("249_dfa_file_state_pair_witnesses",ends01,expected="q0,q2=<epsilon>")
    pairs=run("249_dfa_file_state_pair_witnesses",dup)
    assert "EQUIVALENT" in pairs
    dot=run("250_dfa_file_graphviz",ends01,expected="digraph DFA {")
    assert 'q1 -> q2 [label="1"];' in dot
    assert 'q2 [shape=doublecircle];' in dot
    for name in ("242_dfa_file_shortest_word","243_dfa_file_word_count",
                 "244_dfa_file_scc_audit","245_dfa_file_complement",
                 "247_dfa_file_reachable_trim","248_dfa_file_minimize",
                 "249_dfa_file_state_pair_witnesses","250_dfa_file_graphviz"):
        args=[invalid,2] if name=="243_dfa_file_word_count" else [invalid]
        run(name,*args,expected="Invalid DFA file",rc=2)

    # Independently check equivalence and minimality on 30 seeded random DFAs.
    from random import Random
    rng=Random(241250)
    for case in range(30):
        n=rng.randrange(1,8)
        start=rng.randrange(n)
        finals=[rng.randrange(2) for _ in range(n)]
        jumps=[[rng.randrange(n),rng.randrange(n)] for _ in range(n)]
        original=(f"{n} {start}\n"+" ".join(map(str,finals))+"\n"+
                  "".join(f"{a} {b}\n" for a,b in jumps))
        source=save(f"random_{case}.dfa",original)
        minimized=run("248_dfa_file_minimize",source)
        output_n,output_start,output_finals,output_jumps=parse(minimized)
        # Independent table-filling distinguishability algorithm.
        reachable={start}
        pending=[start]
        while pending:
            q=pending.pop()
            for z in jumps[q]:
                if z not in reachable:
                    reachable.add(z)
                    pending.append(z)
        distinct=[[finals[i]!=finals[j] for j in range(n)] for i in range(n)]
        changed=True
        while changed:
            changed=False
            for q in reachable:
                for r in reachable:
                    if distinct[q][r]:
                        continue
                    if any(distinct[jumps[q][b]][jumps[r][b]] for b in (0,1)):
                        distinct[q][r]=distinct[r][q]=True
                        changed=True
        representatives=[]
        for q in sorted(reachable):
            if not any(not distinct[q][r] for r in representatives):
                representatives.append(q)
        assert output_n==len(representatives),(case,n,output_n,len(representatives),minimized)
        for length in range(8):
            for bits in product("01",repeat=length):
                word="".join(bits)
                assert accepts(original,word)==accepts(minimized,word),(
                    case,word,original,minimized
                )
                checks+=1
print(f"{checks} regression checks passed")
