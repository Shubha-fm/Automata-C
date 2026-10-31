"""Test new remainder-based DFA examples with independent Python arithmetic."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1]
models=[["141_dfa_binary_mod_29",2,29],["142_dfa_binary_mod_31",2,31],["143_dfa_decimal_mod_13",10,13],["144_dfa_hex_mod_7",16,7],["145_dfa_ternary_mod_7",3,7],["146_dfa_quaternary_mod_5",4,5],["147_dfa_binary_mod_37",2,37],["148_dfa_decimal_mod_17",10,17],["149_dfa_octal_mod_9",8,9],["150_dfa_hex_mod_11",16,11]]
for name,base,mod in models:
 exe=root/"bin"/name
 for v in range(200):
  symbols="0123456789ABCDEF"
  value=v
  out=""
  while value: out=symbols[value%base]+out;value//=base
  word=out or "0"
  p=subprocess.run([str(exe),word],capture_output=True,text=True)
  assert p.returncode==0 and p.stdout.strip()==("ACCEPT" if v%mod==0 else "REJECT"),(name,word,p.stdout)
 for bad in ("Z","-1",""):
  p=subprocess.run([str(exe),bad],capture_output=True,text=True)
  assert p.returncode==0 and p.stdout.strip()=="REJECT",(name,bad)
print("2030 checks passed for programs 141-150")
