#!/usr/bin/env python3
"""Independent regression and randomized property checks for Automata-C 291-300."""
from collections import deque
from itertools import product
from pathlib import Path
from random import Random
from heapq import heappush, heappop
import re
import subprocess
import tempfile

BIN = Path(__file__).resolve().parents[1] / "bin"
checks = 0

def run(name, *args, expected=None, rc=0):
    global checks
    cmd = [str(BIN / name), *map(str, args)]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=12)
    assert result.returncode == rc, (cmd, rc, result.returncode, result.stdout, result.stderr)
    out = result.stdout if rc == 0 else result.stderr
    if expected is not None:
        assert expected in out, (cmd, expected, result.stdout, result.stderr)
    checks += 1
    return result.stdout

def encode(final, go, start=0):
    n=len(final)
    return f"{n} {start}\n"+" ".join(map(str,final))+"\n"+\
           "".join(f"{a} {b}\n" for a,b in go)

def decode(source):
    parts=list(map(int,source.split()))
    n,start=parts[:2]
    assert 1<=n<=32 and 0<=start<n and len(parts)==2+3*n
    final=parts[2:2+n]
    go=[tuple(parts[2+n+2*q:2+n+2*q+2]) for q in range(n)]
    assert all(x in (0,1) for x in final)
    assert all(0<=z<n for row in go for z in row)
    return n,start,final,go

def state(source, word, initial=None):
    _,start,_,go=decode(source)
    q=start if initial is None else initial
    for bit in word:q=go[q][int(bit)]
    return q

def accept(source, word):
    _,_,final,_=decode(source)
    return final[state(source,word)]==1

def words(max_length):
    for n in range(max_length+1):
        for symbols in product("01",repeat=n):
            yield "".join(symbols)

def exact_words(length):
    return ("".join(symbols) for symbols in product("01",repeat=length))

def reached(source):
    _,start,_,go=decode(source)
    result={start};queue=[start]
    for q in queue:
        for z in go[q]:
            if z not in result:
                result.add(z);queue.append(z)
    return result

def shortest_suffix(source,prefix,accepting=True):
    _,start,final,go=decode(source)
    q=state(source,prefix)
    queue=deque([(q,"")]);seen={q}
    while queue:
        state_,word=queue.popleft()
        if bool(final[state_])==accepting:return word
        for bit in range(2):
            z=go[state_][bit]
            if z not in seen:
                seen.add(z);queue.append((z,word+str(bit)))
    return None

def distance(source,input_):
    n,start,final,go=decode(source)
    initial=(0,start)
    distances={initial:0};heap=[(0,initial)]
    while heap:
        dist,(position,q)=heappop(heap)
        if dist!=distances[(position,q)]:continue
        if position==len(input_) and final[q]:return dist
        transitions=[((position,go[q][b]),1) for b in range(2)]
        if position<len(input_):
            transitions.append(((position+1,q),1))
            transitions.extend(((position+1,go[q][b]),int(str(b)!=input_[position]))
                               for b in range(2))
        for next_state,cost in transitions:
            nd=dist+cost
            if nd<distances.get(next_state,10**8):
                distances[next_state]=nd
                heappush(heap,(nd,next_state))
    return None

def myhill_nerode(source):
    n,start,final,go=decode(source)
    distinct=[[final[q]!=final[r] for r in range(n)] for q in range(n)]
    changed=True
    while changed:
        changed=False
        for q in range(n):
            for r in range(n):
                if not distinct[q][r] and any(distinct[go[q][b]][go[r][b]] for b in range(2)):
                    distinct[q][r]=distinct[r][q]=True
                    changed=True
    representatives=[]
    for q in sorted(reached(source)):
        if not any(not distinct[q][other] for other in representatives):
            representatives.append(q)
    return len(reached(source)),len(representatives),distinct

def buchi_oracle(source):
    _,start,final,go=decode(source)
    for accepted in reached(source):
        if not final[accepted]:continue
        queue=deque([accepted]);seen={accepted}
        while queue:
            q=queue.popleft()
            for z in go[q]:
                if z==accepted:return True
                if z not in seen:
                    seen.add(z);queue.append(z)
    return False

def coverage(source,word):
    n,q,final,go=decode(source)
    visited={q};transitions=set()
    for bit in word:
        transitions.add((q,int(bit)))
        q=go[q][int(bit)]
        visited.add(q)
    return f"VISITED_STATES={len(visited)}/{n} COVERED_TRANSITIONS={len(transitions)}/{2*n} FINAL_STATE=q{q} VERDICT={'ACCEPT' if final[q] else 'REJECT'}"

with tempfile.TemporaryDirectory() as folder:
    root=Path(folder)
    def save(name,contents):
        p=root/name;p.write_text(contents);return p
    predefined=[
        ("all",encode([1],[(0,0)])),
        ("empty",encode([0],[(0,0)])),
        ("epsilon",encode([1,0],[(1,1),(1,1)])),
        ("ends01",encode([0,0,1],[(1,0),(1,2),(1,0)])),
        ("contains01",encode([0,0,1],[(1,0),(1,2),(2,2)])),
        ("even",encode([1,0],[(0,1),(1,0)])),
        ("exact01",encode([0,0,1,0],[(1,3),(3,2),(3,3),(3,3)])),
        ("redundant",encode([0,1,0,1],[(1,2),(1,0),(3,0),(3,0)])),
        ("unreachable",encode([1,0,1],[(0,1),(1,0),(2,2)]))
    ]
    random=Random(291300)
    for i in range(14):
        n=random.randrange(1,6)
        predefined.append((f"random_{i}",encode(
            [random.randrange(2) for _ in range(n)],
            [(random.randrange(n),random.randrange(n)) for _ in range(n)],
            random.randrange(n)
        )))
    files={name:save(name+".dfa",model) for name,model in predefined}

    for name,model in predefined:
        path=files[name]
        n,start,final,go=decode(model)
        count=0
        for word in words(4):
            trace=run("291_dfa_file_execution_trace",path,word)
            trajectory=[start]
            for bit in word:
                trajectory.append(go[trajectory[-1]][int(bit)])
            assert "STATES="+"->".join(f"q{q}" for q in trajectory)+"\n" in trace
            assert f"FINAL_STATE=q{trajectory[-1]} VERDICT={'ACCEPT' if final[trajectory[-1]] else 'REJECT'}" in trace
            run("293_dfa_file_word_coverage",path,word,expected=coverage(model,word))
            if count<18:
                oracle=shortest_suffix(model,word)
                got=run("292_dfa_file_shortest_extension",path,word)
                if oracle is None:
                    assert got.strip()=="NO_ACCEPTED_EXTENSION",(name,word,got)
                else:
                    assert got.strip()==f"SUFFIX={oracle if oracle else '<epsilon>'} LENGTH={len(oracle)}",(name,word,got)
            count+=1

        for word in words(4):
            expected=distance(model,word)
            got=run("294_dfa_file_levenshtein_distance",path,word)
            assert got.strip()==(f"EDIT_DISTANCE={expected}" if expected is not None else "EMPTY_LANGUAGE"),(name,word,expected,got)

        for length in range(5):
            accepted=[w for w in exact_words(length) if accept(model,w)]
            for word in exact_words(length):
                got=run("295_dfa_file_nearest_hamming",path,word)
                if not accepted:
                    assert got.strip()=="NO_ACCEPTED_WORD_OF_LENGTH",(name,word,got)
                else:
                    expected=min(accepted,key=lambda w:(sum(x!=y for x,y in zip(w,word)),w))
                    d=sum(x!=y for x,y in zip(expected,word))
                    assert got.strip()==f"HAMMING_DISTANCE={d} WORD={expected}",(name,word,got)

        for pattern in ("0","1","01","101"):
            if n*(len(pattern)+1)>32:continue
            filtered=run("296_dfa_file_avoid_pattern",path,pattern)
            decode(filtered)
            for word in words(5):
                assert accept(filtered,word)==(accept(model,word) and pattern not in word),(name,pattern,word)
                checks+=1

        safety=run("297_dfa_file_safety_lasso",path)
        rejected=shortest_suffix(model,"",accepting=False)
        if rejected is None:
            assert safety.strip()=="SAFETY_PASS",(name,safety)
        else:
            match=re.fullmatch(r"SAFETY_FAIL WITNESS=(\S+) TAIL_ZEROS=(\d+) LOOP_ZEROS=(\d+)\n",safety)
            assert match,(name,safety)
            witness=match.group(1).replace("<epsilon>","")
            transient=int(match.group(2))
            period=int(match.group(3))
            assert witness==rejected,(name,witness,rejected)
            assert period>=1 and transient<=n and period<=n
            state_at_loop=state(model,witness+"0"*transient)
            assert state(model,"0"*period,initial=state_at_loop)==state_at_loop
            assert not accept(model,witness)
            checks+=1

        buchi=run("299_dfa_file_buchi_lasso",path)
        exists=buchi_oracle(model)
        if not exists:
            assert buchi.strip()=="BUCHI_EMPTY",(name,buchi)
        else:
            match=re.fullmatch(r"BUCHI_NONEMPTY PREFIX=(\S+) LOOP=([01]+) TOTAL_LENGTH=(\d+)\n",buchi)
            assert match,(name,buchi)
            prefix=match.group(1).replace("<epsilon>","")
            loop=match.group(2)
            q=state(model,prefix)
            assert final[q],(name,buchi)
            assert state(model,loop,initial=q)==q,(name,buchi)
            assert int(match.group(3))==len(prefix)+len(loop),(name,buchi)
            checks+=1

        residuals=run("300_dfa_file_residual_classes",path)
        reachable,classes,distinct=myhill_nerode(model)
        assert f"REACHABLE={reachable} RESIDUAL_CLASSES={classes} MINIMAL={'YES' if reachable==classes else 'NO'}" in residuals
        mapping={}
        for line in residuals.splitlines():
            if not line.startswith("q"):continue
            left,right=line.split("=class")
            mapping[int(left[1:])]=int(right)
        assert set(mapping)==reached(model),(name,mapping)
        for q in mapping:
            for r in mapping:
                assert (mapping[q]==mapping[r])== (not distinct[q][r]),(name,q,r,mapping,distinct[q][r])
                checks+=1

    # Batch monitoring counts empty lines as epsilon traces and CRLF is accepted.
    for name,model in predefined[:9]:
        traces=["","0","01","101","111","010101","10","11"]
        trace_file=save(name+"_traces.txt","\n".join(traces)+"\n")
        rejects=[i+1 for i,word in enumerate(traces) if not accept(model,word)]
        got=run("298_dfa_file_batch_monitor",files[name],trace_file)
        expected=f"TOTAL={len(traces)} ACCEPTED={len(traces)-len(rejects)} REJECTED={len(rejects)} FIRST_REJECTED_LINE={rejects[0] if rejects else 0}"
        assert got.strip()==expected,(name,expected,got)
    malformed=save("malformed.txt","01\n1x\n")
    run("298_dfa_file_batch_monitor",files["all"],malformed,
        expected="Invalid binary trace on line 2",rc=2)
    crlf=save("crlf.txt","01\r\n0\r\n")
    run("298_dfa_file_batch_monitor",files["all"],crlf,
        expected="TOTAL=2 ACCEPTED=2 REJECTED=0 FIRST_REJECTED_LINE=0")

    invalid=save("invalid.dfa","2 0\n0 1\n1 0\n")
    for number,slug,args in [
        (291,"dfa_file_execution_trace",["01"]),
        (292,"dfa_file_shortest_extension",["01"]),
        (293,"dfa_file_word_coverage",["01"]),
        (294,"dfa_file_levenshtein_distance",["01"]),
        (295,"dfa_file_nearest_hamming",["01"]),
        (296,"dfa_file_avoid_pattern",["01"]),
        (297,"dfa_file_safety_lasso",[]),
        (298,"dfa_file_batch_monitor",[crlf]),
        (299,"dfa_file_buchi_lasso",[]),
        (300,"dfa_file_residual_classes",[])
    ]:
        run(f"{number}_{slug}",invalid,*args,expected="Invalid DFA file",rc=2)
    for program,arg in [
        ("291_dfa_file_execution_trace","0102"),
        ("292_dfa_file_shortest_extension","0102"),
        ("293_dfa_file_word_coverage","0102"),
        ("294_dfa_file_levenshtein_distance","0102"),
        ("295_dfa_file_nearest_hamming","0102"),
        ("296_dfa_file_avoid_pattern","0102")
    ]:
        run(program,files["all"],arg,expected="Binary",rc=2)
    run("296_dfa_file_avoid_pattern",files["ends01"],"1"*11,
        expected="Pattern product exceeds 32 states",rc=2)
    run("294_dfa_file_levenshtein_distance",files["all"],"0"*41,
        expected="Maximum word length is 40",rc=2)
    run("295_dfa_file_nearest_hamming",files["all"],"0"*129,
        expected="Maximum word length is 128",rc=2)

print(f"{checks} regression checks passed")
