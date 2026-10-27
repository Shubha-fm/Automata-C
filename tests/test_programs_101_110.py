"""Smoke tests for programs 101-110. Run 'make' first."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["101_dyck_two_brackets","([])","([)]"],["102_anbncn_counter","aabbcc","aabcc"],["103_cfg_palindrome","1001","1010"],["104_regex_a_star_b_plus","aaabbb","aaa"],["105_dfa_binary_mod_13","1101","1100"],["106_dfa_avoid_1011","1010","11011"],["107_nfa_ends_abb","aabb","abba"],["108_dfa_even_a_odd_b","aab","abb"],["109_pda_anb2n","aabbbb","aabbb"],["110_binary_no_000_or_111","001100","0001"]]
for name,accepted,rejected in cases:
 for s,expect in ((accepted,"ACCEPT"),(rejected,"REJECT")):
  p=subprocess.run([str(root/"bin"/name),s],capture_output=True,text=True,timeout=5)
  assert p.returncode==0 and p.stdout.strip()==expect,(name,s,p.stdout,p.stderr)
print("20 smoke tests passed")
