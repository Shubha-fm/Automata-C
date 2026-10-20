#!/usr/bin/env python3
"""Exhaustive tests for programs 51-60 on binary strings up to length 9."""
import itertools
import pathlib
import subprocess
root = pathlib.Path(__file__).resolve().parents[1]
cases = [
    ("51_binary_divisible_7", "binary_divisible_7"),
    ("52_binary_divisible_9", "binary_divisible_9"),
    ("53_zeros_multiple_of_7", "zeros_multiple_of_7"),
    ("54_exactly_three_zeros", "exactly_three_zeros"),
    ("55_length_multiple_of_4", "length_multiple_of_4"),
    ("56_alternating_bits", "alternating_bits"),
    ("57_avoid_010", "avoid_010"),
    ("58_contains_00_and_11", "contains_00_and_11"),
    ("59_even_ones_ends_01", "even_ones_ends_01"),
    ("60_no_more_than_two_ones", "no_more_than_two_ones"),
]
def expected(kind,s):
    if kind.startswith("binary_divisible_"): return int(s or "0",2)%int(kind.split("_")[-1])==0
    if kind=="zeros_multiple_of_7": return s.count("0")%7==0
    if kind=="exactly_three_zeros": return s.count("0")==3
    if kind=="length_multiple_of_4": return len(s)%4==0
    if kind=="alternating_bits": return all(a!=b for a,b in zip(s,s[1:]))
    if kind=="avoid_010": return "010" not in s
    if kind=="contains_00_and_11": return "00" in s and "11" in s
    if kind=="even_ones_ends_01": return s.endswith("01") and s.count("1")%2==0
    if kind=="no_more_than_two_ones": return s.count("1")<=2
    raise ValueError(kind)
count=0
for name,kind in cases:
    exe=root/"bin"/name
    for n in range(10):
        for bits in itertools.product("01",repeat=n):
            s="".join(bits)
            p=subprocess.run([str(exe),s],capture_output=True,text=True)
            assert p.returncode==0 and p.stdout.strip()==("ACCEPT" if expected(kind,s) else "REJECT"),(name,s,p.stderr,p.stdout)
            count+=1
    p=subprocess.run([str(exe),"10x1"],capture_output=True,text=True)
    assert p.returncode==2,name
    count+=1
print(f"{count} checks passed for programs 51-60")
