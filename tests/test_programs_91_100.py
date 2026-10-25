from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["91_pda_balanced_parentheses","(()())","(()"],["92_pda_anbn","aaabbb","aabbb"],["93_pda_palindrome_with_separator","101#101","101#011"],["94_cfg_cyk_ab","ab","aa"],["95_regex_thompson_01star","011","010"],["96_dfa_decimal_mod_3","123","124"],["97_dfa_hex_mod_5","A","B"],["98_dfa_ternary_mod_4","11","12"],["99_dfa_identifier","_x3","3x"],["100_dfa_binary_multiple_11","1011","1010"]]
for name,yes,no in cases:
 for inp,out in ((yes,"ACCEPT"),(no,"REJECT")):
  p=subprocess.run([str(root/"bin"/name),inp],capture_output=True,text=True,timeout=5)
  assert p.returncode==0 and p.stdout.strip()==out,(name,inp,p.stdout,p.stderr)
print("20 checks passed")
