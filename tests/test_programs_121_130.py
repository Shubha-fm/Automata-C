from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["121_dfa_count_01_mod_3","010101","01"],["122_dfa_count_10_mod_2","1010","10"],["123_dfa_ends_same_two","1100","1010"],["124_dfa_first_last_same","101","100"],["125_dfa_contains_010_and_101","0101","0100"],["126_dfa_no_010_or_101","000111","0101"],["127_dfa_a_mod_3_b_mod_2","aaabb","aab"],["128_dfa_odd_length_ends_0","110","10"],["129_dfa_binary_mod_19","10011","10100"],["130_dfa_abc_ends_ab","ccab","ccba"]]
for name,yes,no in cases:
 for word,expect in ((yes,"ACCEPT"),(no,"REJECT")):
  p=subprocess.run([str(root/"bin"/name),word],capture_output=True,text=True,timeout=5)
  assert p.returncode==0 and p.stdout.strip()==expect,(name,word,p.stdout,p.stderr)
print("20 test cases passed")
