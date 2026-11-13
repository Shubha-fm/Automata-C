#!/usr/bin/env python3
"""Independent reference tests for DFA tools 281-290, requiring only Python stdlib."""
from itertools import product
from pathlib import Path
from random import Random
from collections import deque
import subprocess
import tempfile

BIN = Path(__file__).resolve().parents[1] / "bin"
checks = 0
def run(name, *args, expected=None, rc=0):
    global checks
    cmd = [str(BIN / name), *map(str, args)]
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=12)
    assert p.returncode == rc, (cmd, p.returncode, p.stdout, p.stderr)
    result = p.stdout if rc == 0 else p.stderr
    if expected is not None:
        assert expected in result, (cmd, expected, p.stdout, p.stderr)
    checks += 1
    return p.stdout

def encode(final, go, start=0):
    n = len(final)
    return f"{n} {start}\n" + " ".join(map(str,final)) + "\n" + \
           "".join(f"{a} {b}\n" for a,b in go)

def decode(text):
    values = list(map(int,text.split()))
    n,start = values[:2]
    assert 1<=n<=32 and 0<=start<n and len(values)==2+3*n,values
    final=values[2:2+n]
    go=[tuple(values[2+n+2*i:2+n+2*i+2]) for i in range(n)]
    assert all(x in (0,1) for x in final)
    assert all(0<=x<n for row in go for x in row)
    return n,start,final,go

def state(model,word,start=None):
    n,default,final,go=decode(model)
    q=default if start is None else start
    for letter in word:q=go[q][int(letter)]
    return q

def accepts(model,word):
    _,_,final,_=decode(model)
    return bool(final[state(model,word)])

def words(maxlength):
    for length in range(maxlength+1):
        for bits in product("01",repeat=length):
            yield "".join(bits)

def exact_words(length):
    return ("".join(bits) for bits in product("01",repeat=length))

def weighted_probability(model,length,predicate,p):
    total=0.0
    for word in exact_words(length):
        if predicate(word):
            ones=word.count("1")
            total+=(p**ones)*((1-p)**(length-ones))
    return total

def hit(model,word):
    return any(accepts(model,word[:k]) for k in range(len(word)+1))

def accepted_prefixes(model,word):
    return sum(accepts(model,word[:k]) for k in range(len(word)+1))

def enumerate_monoid(model):
    n,_,_,go=decode(model)
    initial=tuple(range(n))
    seen={initial}
    queue=[initial]
    for transform in queue:
        for bit in (0,1):
            nxt=tuple(go[transform[q]][bit] for q in range(n))
            if nxt not in seen:
                seen.add(nxt);queue.append(nxt)
    return queue

def is_aperiodic(model):
    n,_,_,go=decode(model)
    for f in enumerate_monoid(model):
        p=tuple(range(n))
        for k in range(n):
            p=tuple(f[p[q]] for q in range(n))
        if tuple(f[p[q]] for q in range(n))!=p:
            return False
    return True

def compare_language(produced,predicate,max_length=6):
    global checks
    decode(produced)
    for word in words(max_length):
        assert accepts(produced,word)==predicate(word),(word,produced)
        checks+=1

def possible_right_quotient(a,b,word):
    # First consume the candidate left part in A, then search the product
    # for a regular suffix accepted simultaneously by both automata.
    na,_,fa,ga=decode(a)
    nb,sb,fb,gb=decode(b)
    q=state(a,word)
    seen={(q,sb)}
    queue=[(q,sb)]
    for x,y in queue:
        if fa[x] and fb[y]:return True
        for bit in (0,1):
            z=(ga[x][bit],gb[y][bit])
            if z not in seen:
                seen.add(z);queue.append(z)
    return False

def possible_left_quotient(a,b,word):
    # Pair exploration produces all A-states reached by any B-accepted word.
    na,sa,fa,ga=decode(a)
    nb,sb,fb,gb=decode(b)
    seen={(sa,sb)}
    queue=[(sa,sb)]
    for x,y in queue:
        for bit in (0,1):
            z=(ga[x][bit],gb[y][bit])
            if z not in seen:
                seen.add(z);queue.append(z)
    return any(fa[state(a,word,start=x)] for x,y in queue if fb[y])

with tempfile.TemporaryDirectory() as folder:
    root=Path(folder)
    def save(name,text):
        p=root/name;p.write_text(text);return p
    samples=[
        ("empty",encode([0],[(0,0)])),
        ("all",encode([1],[(0,0)])),
        ("even",encode([1,0],[(0,1),(1,0)])),
        ("contains1",encode([0,1],[(0,1),(1,1)])),
        ("ends01",encode([0,0,1],[(1,0),(1,2),(1,0)])),
        ("contains01",encode([0,0,1],[(1,0),(1,2),(2,2)])),
        ("exact01",encode([0,0,1,0],[(1,3),(3,2),(3,3),(3,3)])),
        ("permutation",encode([0,1],[(1,0),(1,0)])),
        ("unreachable",encode([0,1,1],[(1,0),(1,0),(2,2)]))
    ]
    rng=Random(281290)
    for k in range(20):
        n=rng.randrange(1,5)
        samples.append((f"random{k}",encode(
            [rng.randrange(2) for _ in range(n)],
            [(rng.randrange(n),rng.randrange(n)) for _ in range(n)],
            rng.randrange(n)
        )))
    paths={name:save(f"{name}.dfa",text) for name,text in samples}

    for name,model in samples:
        path=paths[name]
        for n in range(0,6):
            for prob in (0.0,0.25,0.5,0.8,1.0):
                actual=run("281_dfa_file_biased_acceptance",path,n,prob)
                oracle=weighted_probability(model,n,lambda w:accepts(model,w),prob)
                assert abs(float(actual.strip().split("=")[-1])-oracle)<2e-8,(name,n,prob,actual,oracle)
                checks+=1
                actual=run("282_dfa_file_hitting_probability",path,n,prob)
                oracle=weighted_probability(model,n,lambda w:hit(model,w),prob)
                assert abs(float(actual.strip().split("=")[-1])-oracle)<2e-8,(name,n,prob,actual,oracle)
                checks+=1
                actual=run("283_dfa_file_expected_prefix_accepts",path,n,prob)
                oracle=0.0
                for word in exact_words(n):
                    oracle+=accepted_prefixes(model,word)*(prob**word.count("1"))*((1-prob)**(n-word.count("1")))
                assert abs(float(actual.strip().split("=")[-1])-oracle)<2e-8,(name,n,prob,actual,oracle)
                checks+=1

        monoid=enumerate_monoid(model)
        output=run("284_dfa_file_transition_monoid",path,
                   expected=f"MONOID_SIZE={len(monoid)}")
        assert len([x for x in output.splitlines() if x.startswith("MAP_")])==len(monoid)
        checks+=1
        is_aperiodic_expected=is_aperiodic(model)
        run("285_dfa_file_aperiodicity",path,
            expected=f"MONOID_SIZE={len(monoid)} APERIODIC={'YES' if is_aperiodic_expected else 'NO'}")
        flipped=run("287_dfa_file_swap_symbols",path)
        compare_language(flipped,lambda w:accepts(model,
             "".join("1" if c=="0" else "0" for c in w)),6)

        # A genuinely different state numbering remains rooted-isomorphic.
        oldn,start,flags,jumps=decode(model)
        order=list(range(oldn));rng.shuffle(order)
        old_to_new={old:new for new,old in enumerate(order)}
        renamed=encode(
            [flags[old] for old in order],
            [(old_to_new[jumps[old][0]],old_to_new[jumps[old][1]]) for old in order],
            old_to_new[start]
        )
        renamed_path=save(f"{name}_renamed.dfa",renamed)
        run("286_dfa_file_rooted_isomorphism",path,renamed_path,
            expected="ISOMORPHIC")
        changed_final=list(flags)
        changed_final[start]^=1
        altered_path=save(f"{name}_mutant.dfa",encode(changed_final,jumps,start))
        run("286_dfa_file_rooted_isomorphism",path,altered_path,
            expected="NOT_ISOMORPHIC")

    for a_name,a in samples[:12]:
        for b_name,b in samples[:12]:
            pa,pb=paths[a_name],paths[b_name]
            right=run("288_dfa_file_right_quotient_regular",pa,pb)
            compare_language(right,
                lambda w:possible_right_quotient(a,b,w),5)
            left=run("289_dfa_file_left_quotient_regular",pa,pb)
            compare_language(left,
                lambda w:possible_left_quotient(a,b,w),5)

    for name,model in samples:
        for k in (0,1,2,3,5):
            if len(decode(model)[2])*(k+2)>32:continue
            for exact in (False,True):
                args=[paths[name],k]+(["exact"] if exact else [])
                filtered=run("290_dfa_file_bounded_length_filter",*args)
                compare_language(filtered,lambda w:(len(w)==k if exact else len(w)<=k)
                     and accepts(model,w),7)
    # Verify epsilon and impossible cases, limits, and invalid inputs.
    run("281_dfa_file_biased_acceptance",paths["all"],0,.5,
        expected="P_ACCEPT=1.000000000")
    run("282_dfa_file_hitting_probability",paths["all"],0,.5,
        expected="P_HIT=1.000000000")
    run("283_dfa_file_expected_prefix_accepts",paths["all"],3,.5,
        expected="EXPECTED_ACCEPTED_PREFIXES=4.000000000")
    for program in ("281_dfa_file_biased_acceptance",
                    "282_dfa_file_hitting_probability",
                    "283_dfa_file_expected_prefix_accepts"):
        run(program,paths["all"],3,"nan",expected="Probability must",rc=2)
        run(program,paths["all"],3,1.1,expected="Probability must",rc=2)
    overfive=save("six.dfa",encode([0]*6,[(q,q) for q in range(6)]))
    run("284_dfa_file_transition_monoid",overfive,
        expected="limited to 5 states",rc=2)
    run("285_dfa_file_aperiodicity",overfive,
        expected="limited to 5 states",rc=2)
    overten=save("eleven.dfa",encode([0]*11,[(q,q) for q in range(11)]))
    run("289_dfa_file_left_quotient_regular",overten,paths["all"],
        expected="limited to 10 states",rc=2)
    run("290_dfa_file_bounded_length_filter",paths["all"],31,
        expected="K must be 0..30",rc=2)
    run("290_dfa_file_bounded_length_filter",paths["exact01"],10,
        expected="Bounded product exceeds 32 states",rc=2)
    invalid=save("invalid.dfa","2 0\n0 1\n0 1\n")
    for program,args in [
        ("281_dfa_file_biased_acceptance",[3,.5]),
        ("282_dfa_file_hitting_probability",[3,.5]),
        ("283_dfa_file_expected_prefix_accepts",[3,.5]),
        ("284_dfa_file_transition_monoid",[]),
        ("285_dfa_file_aperiodicity",[]),
        ("286_dfa_file_rooted_isomorphism",[paths["all"]]),
        ("287_dfa_file_swap_symbols",[]),
        ("288_dfa_file_right_quotient_regular",[paths["all"]]),
        ("289_dfa_file_left_quotient_regular",[paths["all"]]),
        ("290_dfa_file_bounded_length_filter",[1])]:
        run(program,invalid,*args,expected="Invalid DFA file",rc=2)
print(f"{checks} regression checks passed")
