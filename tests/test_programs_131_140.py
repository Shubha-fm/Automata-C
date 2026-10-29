"""Smoke tests for C programs 131–140. First run make."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["131_dfa_binary_mod_23","10111","10110"],["132_dfa_decimal_mod_11","121","122"],["133_dfa_contains_abc","bcabca","abcaac"],["134_dfa_avoid_bb","ababa","abba"],["135_dfa_exactly_three_a","aaabb","aabb"],["136_dfa_a_count_mod_5","aaaaab","aaaab"],["137_dfa_binary_length_mod_7","1010101","10101"],["138_dfa_binary_has_exactly_one_11","0110","111"],["139_dfa_ends_ab_or_ba","aaba","aabb"],["140_dfa_even_a_odd_c","aabc","abc"]]
for name,yes,no in cases:
    for word,wanted in ((yes,"ACCEPT"),(no,"REJECT")):
        result=subprocess.run([str(root/"bin"/name),word],capture_output=True,text=True,timeout=5)
        assert result.returncode==0 and result.stdout.strip()==wanted,(name,word,result.stdout,result.stderr)
print("20 checks passed")
