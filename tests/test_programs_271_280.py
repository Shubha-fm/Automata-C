#!/usr/bin/env python3
"""Cross-checked tests for DFA utilities 271-280 using independent Python oracles."""
from itertools import product
from pathlib import Path
from random import Random
import subprocess
import tempfile

BIN = Path(__file__).resolve().parents[1] / "bin"
checks = 0

def run(program, *args, expected=None, rc=0):
    global checks
    cmd = [str(BIN / program), *map(str, args)]
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=15)
    assert p.returncode == rc, (cmd, p.returncode, p.stdout, p.stderr)
    if expected is not None:
        out = p.stdout if rc == 0 else p.stderr
        assert expected in out, (cmd, expected, p.stdout, p.stderr)
    checks += 1
    return p.stdout

def serialize(final, go, start=0):
    n = len(final)
    return f"{n} {start}\n" + " ".join(map(str,final)) + "\n" + \
        "".join(f"{row[0]} {row[1]}\n" for row in go)

def parse(text):
    vals = list(map(int,text.split()))
    n,start = vals[:2]
    assert 1 <= n <= 32 and 0 <= start < n and len(vals) == 2+3*n
    final = vals[2:2+n]
    go = [tuple(vals[2+n+2*q:2+n+2*q+2]) for q in range(n)]
    assert all(x in (0,1) for x in final)
    assert all(0 <= x < n for row in go for x in row)
    return n,start,final,go

def state(model, word, initial=None):
    _,start,_,go=parse(model)
    q = start if initial is None else initial
    for b in word: q=go[q][int(b)]
    return q

def accepts(model, word):
    _,_,f,_=parse(model)
    return bool(f[state(model,word)])

def product_strings(length):
    return ["".join(t) for t in product("01",repeat=length)]

def words(limit):
    for n in range(limit+1):
        for s in product("01",repeat=n):
            yield "".join(s)

def reachable(model):
    _,start,_,go=parse(model)
    found={start}
    queue=[start]
    for q in queue:
        for z in go[q]:
            if z not in found:
                found.add(z);queue.append(z)
    return found

def productive(model):
    n,_,f,go=parse(model)
    result={q for q in range(n) if f[q]}
    while True:
        extra={q for q in range(n) if any(z in result for z in go[q])}
        if extra.issubset(result):return result
        result|=extra

def factor_member(model, word):
    _,_,_,go=parse(model)
    prod=productive(model)
    return any(state(model,word,q) in prod for q in reachable(model))

def subsequence_member(model, word):
    n,start,f,go=parse(model)
    queue=[(start,0)];seen=set(queue)
    for q,index in queue:
        if index==len(word) and f[q]:return True
        for b in range(2):
            z=go[q][b]
            options=[(z,index)]
            if index<len(word) and int(word[index])==b:
                options.append((z,index+1))
            for item in options:
                if item not in seen:
                    seen.add(item);queue.append(item)
    return False

def supersequence_member(model, word):
    for mask in range(1<<len(word)):
        sub="".join(c for i,c in enumerate(word) if mask & (1<<i))
        if accepts(model,sub):return True
    return False

def star_member(model, word):
    reachable_prefix=[False]*(len(word)+1)
    reachable_prefix[0]=True
    for i in range(len(word)):
        if not reachable_prefix[i]:continue
        for j in range(i+1,len(word)+1):
            if accepts(model,word[i:j]):reachable_prefix[j]=True
    return reachable_prefix[-1]

def oracle_period(model, unary=False):
    _,start,f,go=parse(model)
    current=start if unary else frozenset((start,))
    seen={}
    masks=[]
    while current not in seen:
        seen[current]=len(masks)
        masks.append(current)
        if unary:current=go[current][0]
        else:current=frozenset(go[q][b] for q in current for b in (0,1))
    mu=seen[current]
    period=len(masks)-mu
    accept=lambda m: bool(f[m]) if unary else any(f[q] for q in m)
    prefixes=[i for i in range(mu) if accept(masks[i])]
    offsets=[i-mu for i in range(mu,len(masks)) if accept(masks[i])]
    return mu,period,prefixes,offsets

def check_period(program,model,path,unary):
    output=run(program,path)
    mu,p,pre,cyc=oracle_period(model,unary)
    pre_str=",".join(map(str,pre)) if pre else "<none>"
    cyc_str=",".join(map(str,cyc)) if cyc else "<none>"
    assert f"PREPERIOD={mu} PERIOD={p}" in output,output
    assert f"ACCEPTING_PREFIX_LENGTHS={pre_str}" in output,output
    assert f"ACCEPTING_CYCLE_OFFSETS={cyc_str}" in output,output

def diameter(model):
    _,start,_,go=parse(model)
    distances={start:0}
    queue=[start]
    for q in queue:
        for z in go[q]:
            if z not in distances:
                distances[z]=distances[q]+1
                queue.append(z)
    return len(distances),max(distances.values())

def check_language(transform,oracle,maxlength=6):
    global checks
    parse(transform)
    for w in words(maxlength):
        assert accepts(transform,w)==oracle(w),(w,transform)
        checks+=1

with tempfile.TemporaryDirectory() as tmp:
    base=Path(tmp)
    def save(name,source):
        file=base/name;file.write_text(source);return file

    models=[
        ("empty",serialize([0],[(0,0)])),
        ("all",serialize([1],[(0,0)])),
        ("epsilon",serialize([1,0],[(1,1),(1,1)])),
        ("ends01",serialize([0,0,1],[(1,0),(1,2),(1,0)])),
        ("contains01",serialize([0,0,1],[(1,0),(1,2),(2,2)])),
        ("exact01",serialize([0,0,1,0],[(1,3),(3,2),(3,3),(3,3)])),
        ("even",serialize([1,0],[(0,1),(1,0)])),
        ("contains1",serialize([0,1],[(0,1),(1,1)])),
        ("unreachable_sink",serialize([0,1,0],[(0,1),(1,1),(2,2)]))
    ]
    rng=Random(271280)
    for k in range(16):
        n=rng.randrange(1,5)
        models.append((f"random{k}",serialize(
            [rng.randrange(2) for _ in range(n)],
            [(rng.randrange(n),rng.randrange(n)) for _ in range(n)],
            rng.randrange(n)
        )))
    paths={name:save(name+".dfa",model) for name,model in models}
    for name,model in models:
        path=paths[name]
        closures=[
            ("271_dfa_file_factor_closure",factor_member),
            ("272_dfa_file_subsequence_closure",subsequence_member),
            ("273_dfa_file_supersequence_closure",supersequence_member)
        ]
        for program,oracle in closures:
            transform=run(program,path)
            check_language(transform,lambda w:oracle(model,w),6)
        star=run("275_dfa_file_kleene_star",path)
        check_language(star,lambda w:star_member(model,w),6)
        reach,diam=diameter(model)
        run("276_dfa_file_access_diameter",path,
            expected=f"REACHABLE={reach} ACCESS_DIAMETER={diam}")
        check_period("277_dfa_file_unary_periodicity",model,path,True)
        check_period("278_dfa_file_length_periodicity",model,path,False)
    # Concatenation independent split-point oracle on small pairs.
    candidates=models[:8]+models[9:15]
    for name_a,a in candidates:
        for name_b,b in candidates:
            if parse(a)[0]+parse(b)[0]>5:continue
            joined=run("274_dfa_file_concatenation",paths[name_a],paths[name_b])
            check_language(joined,
              lambda w:any(accepts(a,w[:i]) and accepts(b,w[i:])
                           for i in range(len(w)+1)),6)

    # Additional closure edge cases and boundary conditions.
    star_empty=run("275_dfa_file_kleene_star",paths["empty"])
    for w in words(5):
        assert accepts(star_empty,w)==(w=="")
        checks+=1
    run("271_dfa_file_factor_closure",paths["ends01"])
    big=serialize([0]*11,[(q,q) for q in range(11)])
    big_path=save("big.dfa",big)
    for program in ("271_dfa_file_factor_closure",
                    "272_dfa_file_subsequence_closure",
                    "273_dfa_file_supersequence_closure",
                    "278_dfa_file_length_periodicity"):
        run(program,big_path,expected="limited to 10",rc=2)
    run("275_dfa_file_kleene_star",big_path,expected="limited to 9",rc=2)
    run("274_dfa_file_concatenation",big_path,paths["all"],
        expected="limited to 10 combined states",rc=2)

    # Exact hitting-time checks against well-understood automata.
    for name,expected in [
        ("all","EXPECTED_STEPS=0.000000"),
        ("even","EXPECTED_STEPS=0.000000"),
        ("contains1","EXPECTED_STEPS=2.000000"),
        ("ends01","EXPECTED_STEPS=4.000000"),
        ("unreachable_sink","EXPECTED_STEPS=2.000000"),
        ("exact01","EXPECTED_STEPS=INFINITE"),
        ("empty","EXPECTED_STEPS=INFINITE")
    ]:
        run("279_dfa_file_expected_hitting_time",paths[name],expected=expected)

    # Reproducible uniform samples: deterministic with the same seed,
    # valid as accepted words, and exact accepted-word counts.
    for name,model in models[:8]:
        path=paths[name]
        for length in range(0,9):
            accepted=[w for w in product_strings(length) if accepts(model,w)]
            for seed in (0,1,42,2026):
                out=run("280_dfa_file_uniform_sampler",path,length,seed)
                if not accepted:
                    assert out.strip()=="NO_ACCEPTED_WORDS",(name,length,seed,out)
                    continue
                assert f"TOTAL={len(accepted)} SEED={seed}" in out
                sampled=out.split("WORD=",1)[1].split(" TOTAL=",1)[0]
                assert sampled in accepted,(name,length,sampled)
                checks+=1
                if seed==42:
                    again=run("280_dfa_file_uniform_sampler",path,length,seed)
                    assert again==out
    run("280_dfa_file_uniform_sampler",paths["all"],51,1,
        expected="Length must be 0..50",rc=2)
    run("280_dfa_file_uniform_sampler",paths["all"],5,-1,
        expected="Invalid seed",rc=2)

    invalid=save("invalid.dfa","2 0\n0 1\n0 1\n")
    for n,name,args in [
        (271,"dfa_file_factor_closure",[]),(272,"dfa_file_subsequence_closure",[]),
        (273,"dfa_file_supersequence_closure",[]),
        (274,"dfa_file_concatenation",[paths["all"]]),
        (275,"dfa_file_kleene_star",[]),(276,"dfa_file_access_diameter",[]),
        (277,"dfa_file_unary_periodicity",[]),
        (278,"dfa_file_length_periodicity",[]),
        (279,"dfa_file_expected_hitting_time",[]),
        (280,"dfa_file_uniform_sampler",[5,42])
    ]:
        run(f"{n}_{name}",invalid,*args,expected="Invalid DFA file",rc=2)
print(f"{checks} regression checks passed")
