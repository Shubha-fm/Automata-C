"""Smoke tests for programs 111-120. Run make first."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
cases=[["111_dfa_binary_mod_17","10001","10010"],["112_dfa_decimal_mod_7","49","50"],["113_dfa_ternary_mod_5","12","11"],["114_dfa_a_count_mod_4","aaaab","aaab"],["115_dfa_ends_aba","baba","abba"],["116_dfa_contains_bbaa","abbaab","babab"],["117_dfa_even_a_and_ends_b","aabb","ab"],["118_dfa_no_adjacent_a","ababa","aaba"],["119_dfa_exactly_two_b","abba","abbb"],["120_dfa_length_mod_5","ababa","abab"]]
for name,accepted,rejected in cases:
 for word,wanted in ((accepted,"ACCEPT"),(rejected,"REJECT")):
  p=subprocess.run([str(root/"bin"/name),word],capture_output=True,text=True,timeout=5)
  assert p.returncode==0 and p.stdout.strip()==wanted,(name,word,p.stdout,p.stderr)
print("20 checks passed")
