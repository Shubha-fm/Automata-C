#!/usr/bin/env python3
import pathlib, subprocess
root = pathlib.Path(__file__).resolve().parents[1]
cases = [
("01_even_zeros","11","0"),("02_odd_ones","1","11"),
("03_ends_01","1101","1110"),("04_ends_10","0110","0011"),
("05_contains_00","1001","101"),("06_contains_11","0110","0101"),
("07_no_consecutive_ones","10101","0110"),("08_no_consecutive_zeros","0101","1001"),
("09_binary_divisible_3","110","100"),("10_binary_divisible_5","101","110"),
("11_zeros_mod_3","000","00"),("12_ones_mod_3","111","11"),
("13_even_zeros_odd_ones","1","0"),("14_even_zeros_even_ones","0011","1"),
("15_start_1","101","001"),("16_exactly_two_ones","101","111"),
("17_at_least_three_zeros","000","00"),("18_contains_101","11010","111"),
("19_ends_001","1001","1000"),("20_even_length","01","1")
]
count = 0
for name, yes, no in cases:
    exe = root / "bin" / name
    for s, expected, code in [(yes,"ACCEPT",0),(no,"REJECT",0),("xyz",None,2)]:
        p = subprocess.run([str(exe),s],capture_output=True,text=True)
        assert p.returncode == code, (name,s,p.stderr)
        if expected: assert p.stdout.strip() == expected,(name,s,p.stdout)
        count += 1
print(f"{count} tests passed")
