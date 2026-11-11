#!/usr/bin/env python3
"""Regression and property-based tests for programs 251-260."""
from itertools import product
from pathlib import Path
from random import Random
import subprocess
import tempfile

BIN = Path(__file__).resolve().parents[1] / "bin"
checks = 0

def run(program, *args, expect=None, code=0):
    global checks
    p = subprocess.run([str(BIN / program), *map(str, args)],
                       capture_output=True, text=True, timeout=12)
    assert p.returncode == code, (program, args, p.returncode, p.stdout, p.stderr)
    output = p.stdout if code == 0 else p.stderr
    if expect is not None:
        assert expect in output, (program, args, expect, p.stdout, p.stderr)
    checks += 1
    return p.stdout

def serialize(flags, transitions, start=0):
    n = len(flags)
    return f"{n} {start}\n" + " ".join(map(str, flags)) + "\n" + \
        "".join(f"{a} {b}\n" for a,b in transitions)

def parse(contents):
    data = [int(i) for i in contents.split()]
    n, start = data[:2]
    assert 1 <= n <= 32 and 0 <= start < n
    assert len(data) == 2 + 3*n, data
    flags = data[2:2+n]
    transitions = [tuple(data[2+n+2*i:2+n+2*i+2]) for i in range(n)]
    assert all(x in (0, 1) for x in flags)
    assert all(0 <= x < n for row in transitions for x in row)
    return flags, transitions, start

def accepts(contents, word):
    flags, transitions, q = parse(contents)
    for letter in word:
        assert letter in "01"
        q = transitions[q][int(letter)]
    return bool(flags[q])

def words(length):
    return ["".join(t) for t in product("01", repeat=length)]

def shortest_reset(contents):
    flags, transition, _ = parse(contents)
    n = len(flags)
    initial = frozenset(range(n))
    queue = [(initial,"")]
    seen = {initial}
    for mask,prefix in queue:
        if len(mask) == 1:
            return prefix
        for bit in range(2):
            nxt = frozenset(transition[q][bit] for q in mask)
            if nxt not in seen:
                seen.add(nxt)
                queue.append((nxt, prefix+str(bit)))
    return None

with tempfile.TemporaryDirectory() as tmp:
    root = Path(tmp)
    def save(name, contents):
        path = root / name
        path.write_text(contents)
        return path

    all_text = serialize([1], [(0,0)])
    none_text = serialize([0], [(0,0)])
    eps_text = serialize([1,0], [(1,1),(1,1)])
    finite_text = serialize([0,1,1,0], [(1,3),(3,2),(3,3),(3,3)])
    ends01_text = serialize([0,0,1], [(1,0),(1,2),(1,0)])
    contains01_text = serialize([0,0,1], [(1,0),(1,2),(2,2)])
    parity_text = serialize([1,0], [(0,1),(1,0)])
    reset_text = serialize([0,1], [(0,1),(0,1)])
    unreachable_text = serialize([0,0,1,1], [(1,0),(1,2),(1,0),(3,3)])
    all_file=save("all.dfa",all_text)
    none_file=save("none.dfa",none_text)
    eps_file=save("epsilon.dfa",eps_text)
    finite_file=save("finite.dfa",finite_text)
    ends_file=save("ends.dfa",ends01_text)
    contains_file=save("contains.dfa",contains01_text)
    parity_file=save("parity.dfa",parity_text)
    reset_file=save("reset.dfa",reset_text)
    unreachable_file=save("unreachable.dfa",unreachable_text)

    run("251_dfa_file_universality", all_file, expect="UNIVERSAL")
    run("251_dfa_file_universality", ends_file,
        expect="NOT_UNIVERSAL WITNESS=<epsilon>")
    run("251_dfa_file_universality", eps_file, expect="NOT_UNIVERSAL WITNESS=0")
    run("251_dfa_file_universality", all_file.with_name("missing"),
        expect="Invalid DFA file", code=2)
    for path, expect in [
        (finite_file,"FINITE COUNT=2 MAX_LENGTH=2"),
        (none_file,"FINITE COUNT=0 MAX_LENGTH=-1"),
        (eps_file,"FINITE COUNT=1 MAX_LENGTH=0"),
        (all_file,"INFINITE"),
        (ends_file,"INFINITE"),
    ]:
        run("252_dfa_file_finiteness",path,expect=expect)

    run("253_dfa_file_reset_word",reset_file,expect="RESET_WORD=0")
    run("253_dfa_file_reset_word",parity_file,expect="NOT_SYNCHRONIZING")
    run("253_dfa_file_reset_word",all_file,expect="RESET_WORD=<epsilon>")
    size13=save("13_states.dfa",serialize([0]*13,[(q,q) for q in range(13)]))
    run("253_dfa_file_reset_word",size13,expect="limited to 12 states",code=2)

    for name,path,model in [
        ("universal",all_file,all_text),("ends01",ends_file,ends01_text),
        ("parity",parity_file,parity_text),("finite",finite_file,finite_text),
        ("epsilon",eps_file,eps_text)
    ]:
        for n in range(7):
            accepted=[w for w in words(n) if accepts(model,w)]
            for rank,w in enumerate(accepted):
                run("254_dfa_file_word_rank",path,"rank",w,
                    expect=f"RANK={rank} TOTAL={len(accepted)}")
                run("254_dfa_file_word_rank",path,"unrank",n,rank,
                    expect=f"WORD={w} TOTAL={len(accepted)}")
            if not accepted:
                run("254_dfa_file_word_rank",path,"unrank",n,0,
                    expect="Rank out of range",code=2)
    run("254_dfa_file_word_rank",ends_file,"rank","01x",
        expect="Binary word required",code=2)

    # Reversal equivalence is checked by independently reversing input strings.
    samples=[("all",all_text,all_file),("none",none_text,none_file),
             ("ends01",ends01_text,ends_file),
             ("contains01",contains01_text,contains_file),
             ("parity",parity_text,parity_file),
             ("epsilon",eps_text,eps_file)]
    for name,model,path in samples:
        reversed_text=run("255_dfa_file_reverse_determinize",path)
        parse(reversed_text)
        for n in range(9):
            for word in words(n):
                assert accepts(reversed_text,word)==accepts(model,word[::-1]),(
                    "reverse",name,word)
                checks += 1
    size11=save("11_states.dfa",serialize([0]*11,[(q,q) for q in range(11)]))
    run("255_dfa_file_reverse_determinize",size11,
        expect="limited to 10 input states",code=2)

    symmetric_text=run("256_dfa_file_symmetric_difference",ends_file,contains_file)
    symmetric_file=save("symdiff.dfa",symmetric_text)
    parse(symmetric_text)
    for n in range(9):
        for word in words(n):
            assert accepts(symmetric_text,word)==(
                accepts(ends01_text,word)!=accepts(contains01_text,word))
            checks += 1
    run("256_dfa_file_symmetric_difference",all_file,all_file,
        expect=serialize([0],[(0,0)]))
    run("256_dfa_file_symmetric_difference",size11,size11,
        expect="Product exceeds 32 states",code=2)

    accessed=run("257_dfa_file_access_words",ends_file,expect="REACHABLE=3")
    for line in accessed.splitlines():
        if not line.startswith("q"):continue
        state,word=line.split("=")
        q=0
        for bit in word.replace("<epsilon>",""):
            q=parse(ends01_text)[1][q][int(bit)]
        assert int(state[1:])==q,(state,word,q)
        checks += 1
    accessed=run("257_dfa_file_access_words",unreachable_file,
                 expect="REACHABLE=3")
    assert "q3=" not in accessed

    covered=run("258_dfa_file_transition_cover",ends_file,
                expect="COVERED_TRANSITIONS=6")
    transitions=parse(ends01_text)[1]
    lines=[line for line in covered.splitlines() if " WORD=" in line]
    assert len(lines)==6
    seen=set()
    for line in lines:
        prefix,word=line.split(" WORD=")
        fields=prefix.split()
        state=int(fields[0][1:])
        bit=int(fields[1][2])
        target=int(fields[2][1:])
        assert target==transitions[state][bit]
        assert word.endswith(str(bit))
        q=0
        for letter in word[:-1]:q=transitions[q][int(letter)]
        assert q==state
        seen.add((state,bit))
        checks += 1
    assert len(seen)==6

    for name,path,expected in [
        ("finite",finite_file,["0","01"]),
        ("epsilon",eps_file,["<epsilon>"]),
        ("empty",none_file,[])
    ]:
        content=run("259_dfa_file_finite_enumeration",path,
                    expect=f"COUNT={len(expected)} SHOWN={len(expected)} TRUNCATED=NO")
        output=[line[5:] for line in content.splitlines() if line.startswith("WORD=")]
        assert output==expected,(name,output,expected)
        checks += 1
    run("259_dfa_file_finite_enumeration",all_file,
        expect="INFINITE_LANGUAGE")

    for image0,image1 in [("01","10"),("e","1"),("0","e"),("1","0")]:
        mapped=run("260_dfa_file_inverse_homomorphism",ends_file,image0,image1)
        parse(mapped)
        for n in range(9):
            for word in words(n):
                expanded="".join((image0 if c=="0" else image1).replace("e","")
                                 for c in word)
                assert accepts(mapped,word)==accepts(ends01_text,expanded),(
                    image0,image1,word)
                checks += 1
    run("260_dfa_file_inverse_homomorphism",ends_file,"0x","1",
        expect="Images must",code=2)

    # Independent random DFA checks for universality, reversal, inclusion,
    # counting, finite-language counting, ranking and synchronization.
    rng=Random(251260)
    for example in range(24):
        n=rng.randint(1,5)
        flags=[rng.randrange(2) for _ in range(n)]
        transitions=[(rng.randrange(n),rng.randrange(n)) for _ in range(n)]
        start=rng.randrange(n)
        model=serialize(flags,transitions,start)
        path=save(f"random_{example}.dfa",model)
        reversed_text=run("255_dfa_file_reverse_determinize",path)
        for length in range(7):
            accepted=[w for w in words(length) if accepts(model,w)]
            for index,w in enumerate(accepted):
                if length<=4:
                    run("254_dfa_file_word_rank",path,"unrank",length,index,
                        expect=f"WORD={w} TOTAL={len(accepted)}")
            run("254_dfa_file_word_rank",path,"unrank",length,len(accepted),
                expect="Rank out of range",code=2)
            count_output=run("243_dfa_file_word_count",path,length)
            assert f"ACCEPTED_MOD={len(accepted)}" in count_output
            checks += 1
            for word in words(length):
                assert accepts(reversed_text,word)==accepts(model,word[::-1])
                checks += 1
        reset=shortest_reset(model)
        output=run("253_dfa_file_reset_word",path)
        expected=f"RESET_WORD={reset if reset else '<epsilon>'}" if reset is not None else "NOT_SYNCHRONIZING"
        assert expected in output,(example,model,expected,output)
        checks += 1
print(f"{checks} regression checks passed")
