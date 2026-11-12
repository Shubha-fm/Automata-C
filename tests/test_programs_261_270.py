#!/usr/bin/env python3
"""Language-operation regression and randomized oracle tests for programs 261-270."""
from itertools import product
from pathlib import Path
from random import Random
import subprocess
import tempfile

BIN = Path(__file__).resolve().parents[1] / "bin"
checks = 0

def run(program, *args, expected=None, rc=0):
    global checks
    command = [str(BIN / program), *map(str, args)]
    p = subprocess.run(command, text=True, capture_output=True, timeout=12)
    assert p.returncode == rc, (command, p.returncode, p.stdout, p.stderr)
    output = p.stdout if rc == 0 else p.stderr
    if expected is not None:
        assert expected in output, (command, expected, p.stdout, p.stderr)
    checks += 1
    return p.stdout

def encode(final, transitions, start=0):
    n = len(final)
    return f"{n} {start}\n" + " ".join(map(str, final)) + "\n" + \
        "".join(f"{row[0]} {row[1]}\n" for row in transitions)

def decode(text):
    parts = [int(p) for p in text.split()]
    n, start = parts[:2]
    assert 1 <= n <= 32 and 0 <= start < n and len(parts) == 2+3*n
    final = parts[2:2+n]
    go = [tuple(parts[2+n+i*2:2+n+i*2+2]) for i in range(n)]
    assert all(v in (0,1) for v in final)
    assert all(0 <= r < n for row in go for r in row)
    return n,start,final,go

def state(model, word, start=None):
    _, q0, _, go = decode(model)
    q = q0 if start is None else start
    for c in word:
        q = go[q][int(c)]
    return q

def accepts(model, word):
    _,_, final, _ = decode(model)
    return bool(final[state(model, word)])

def all_words(maxlength):
    return (''.join(w) for n in range(maxlength+1)
            for w in product("01",repeat=n))

def reachable(model):
    _, start, _, go = decode(model)
    found={start}
    queue=[start]
    for q in queue:
        for z in go[q]:
            if z not in found:
                found.add(z)
                queue.append(z)
    return found

def productive(model):
    n, _, final, go = decode(model)
    yes={q for q in range(n) if final[q]}
    changed=True
    while changed:
        before=len(yes)
        yes|={q for q in range(n) if any(z in yes for z in go[q])}
        changed=len(yes)!=before
    return yes

def prefix_free(model):
    # A reachable accepting state has a nonempty accepted continuation.
    n,_,final,go=decode(model)
    for q in reachable(model):
        if not final[q]:
            continue
        seen={go[q][0],go[q][1]}
        queue=list(seen)
        for state_ in queue:
            if final[state_]:
                return False
            for z in go[state_]:
                if z not in seen:
                    seen.add(z);queue.append(z)
    return True

def expect_language(result, oracle, length=7):
    global checks
    decode(result)
    for word in all_words(length):
        assert accepts(result, word) == oracle(word), (word, result)
        checks += 1

def save(path, text):
    path.write_text(text)
    return path

with tempfile.TemporaryDirectory() as directory:
    base=Path(directory)
    empty=encode([0],[(0,0)])
    universal=encode([1],[(0,0)])
    ending01=encode([0,0,1],[(1,0),(1,2),(1,0)])
    containing01=encode([0,0,1],[(1,0),(1,2),(2,2)])
    even=encode([1,0],[(0,1),(1,0)])
    exact01=encode([0,0,1,0],[(1,3),(3,2),(3,3),(3,3)])
    epsilon=encode([1,0],[(1,1),(1,1)])
    models=[
        ("empty",empty),("universal",universal),("ending01",ending01),
        ("containing01",containing01),("even",even),
        ("exact01",exact01),("epsilon",epsilon)
    ]
    random=Random(261270)
    for k in range(22):
        n=random.randint(1,5)
        flags=[random.randrange(2) for _ in range(n)]
        go=[(random.randrange(n),random.randrange(n)) for _ in range(n)]
        start=random.randrange(n)
        models.append((f"random{k}",encode(flags,go,start)))
    paths={name:save(base/f"{name}.dfa",model) for name,model in models}

    # Both product construction tools are checked against independent oracles.
    for a_name,a in models[:9]:
        for b_name,b in models[:9]:
            union=run("261_dfa_file_union",paths[a_name],paths[b_name])
            diff=run("262_dfa_file_difference",paths[a_name],paths[b_name])
            expect_language(union, lambda w: accepts(a,w) or accepts(b,w),6)
            expect_language(diff,lambda w: accepts(a,w) and not accepts(b,w),6)

    for name,model in models:
        path=paths[name]
        right_reachable=reachable(model)
        prod=productive(model)
        for part in ("","0","1","01","110","00101"):
            left=run("263_dfa_file_left_quotient",path,part)
            right=run("264_dfa_file_right_quotient",path,part)
            expect_language(left,lambda w:accepts(model,part+w),6)
            expect_language(right,lambda w:accepts(model,w+part),6)
        pref=run("265_dfa_file_prefix_closure",path)
        expect_language(pref,lambda w:state(model,w) in prod,7)
        suff=run("266_dfa_file_suffix_closure",path)
        expect_language(suff,lambda w:any(
            state(model,w,initial) in {
                q for q,flag in enumerate(decode(model)[2]) if flag
            } for initial in right_reachable),7)

        result=run("267_dfa_file_prefix_free_witness",path)
        is_free=prefix_free(model)
        if is_free:
            assert result.strip()=="PREFIX_FREE", (name,result)
        else:
            assert result.startswith("NOT_PREFIX_FREE PREFIX="), (name,result)
            fields=result.strip().split()
            assert len(fields)==3,fields
            x=fields[1].split("=",1)[1].replace("<epsilon>","")
            extended=fields[2].split("=",1)[1]
            assert extended.startswith(x) and len(extended)>len(x)
            assert accepts(model,x) and accepts(model,extended),(name,x,extended)

        for bound in (0,1,2,5,10):
            accepted_lengths=[
                k for k in range(bound+1)
                if any(accepts(model,w) for w in (
                    ''.join(c) for c in product("01",repeat=k)
                ))
            ]
            got=run("268_dfa_file_length_spectrum",path,bound)
            first=f"ACCEPTED_LENGTHS={','.join(map(str,accepted_lengths)) if accepted_lengths else '<none>'}"
            assert first in got and f"COUNT={len(accepted_lengths)}" in got,(name,bound,got)
            checks+=1

        right_ideal=run("269_dfa_file_right_ideal",path)
        expect_language(right_ideal,lambda w:any(accepts(model,w[:i])
                                                 for i in range(len(w)+1)),7)
        left_ideal=run("270_dfa_file_left_ideal",path)
        expect_language(left_ideal,lambda w:any(accepts(model,w[i:])
                                                for i in range(len(w)+1)),7)

    # Examples with intuitive expected outcomes.
    run("267_dfa_file_prefix_free_witness",paths["exact01"],expected="PREFIX_FREE")
    run("267_dfa_file_prefix_free_witness",paths["universal"],
        expected="PREFIX=<epsilon> EXTENDED=0")
    run("268_dfa_file_length_spectrum",paths["exact01"],5,
        expected="ACCEPTED_LENGTHS=2\nCOUNT=1")
    run("268_dfa_file_length_spectrum",paths["empty"],5,
        expected="ACCEPTED_LENGTHS=<none>\nCOUNT=0")
    run("263_dfa_file_left_quotient",paths["empty"],"2",
        expected="Binary prefix required",rc=2)
    run("264_dfa_file_right_quotient",paths["empty"],"2",
        expected="Binary suffix required",rc=2)
    run("268_dfa_file_length_spectrum",paths["empty"],10001,
        expected="MAX_LENGTH must be",rc=2)

    # Input/output limits are enforced rather than silently truncating.
    large=encode([0]*11,[(q,q) for q in range(11)])
    large_path=save(base/"large.dfa",large)
    run("266_dfa_file_suffix_closure",large_path,
        expected="limited to 10 input states",rc=2)
    run("270_dfa_file_left_ideal",large_path,
        expected="limited to 10 input states",rc=2)
    large6=save(base/"six.dfa",encode([0]*6,[(q,q) for q in range(6)]))
    for program in ("261_dfa_file_union","262_dfa_file_difference"):
        run(program,large6,large6,expected="Product exceeds 32 states",rc=2)
    invalid=save(base/"invalid.dfa","2 0\n0 1\n0 1\n")
    for n,slug,args in [
        (261,"dfa_file_union",[invalid,paths["empty"]]),
        (262,"dfa_file_difference",[invalid,paths["empty"]]),
        (263,"dfa_file_left_quotient",[invalid,"0"]),
        (264,"dfa_file_right_quotient",[invalid,"0"]),
        (265,"dfa_file_prefix_closure",[invalid]),
        (266,"dfa_file_suffix_closure",[invalid]),
        (267,"dfa_file_prefix_free_witness",[invalid]),
        (268,"dfa_file_length_spectrum",[invalid,4]),
        (269,"dfa_file_right_ideal",[invalid]),
        (270,"dfa_file_left_ideal",[invalid])
    ]:
        run(f"{n}_{slug}",*args,expected="Invalid DFA file",rc=2)

print(f"{checks} regression checks passed")
