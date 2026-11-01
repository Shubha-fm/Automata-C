#!/usr/bin/env python3
"""Regression checks for automata programs 161-170."""
from pathlib import Path
import subprocess
root = Path(__file__).resolve().parents[1] / "bin"
cases = [
    ("161_regex_postfix_thompson", ["01.", "01"], "ACCEPT", 0),
    ("161_regex_postfix_thompson", ["01.", "10"], "REJECT", 0),
    ("161_regex_postfix_thompson", ["01|*", "10101"], "ACCEPT", 0),
    ("161_regex_postfix_thompson", ["0*", ""], "ACCEPT", 0),
    ("161_regex_postfix_thompson", ["0|", "0"], "Invalid", 2),
    ("162_regex_infix_to_postfix", ["(0|1)*01"], "POSTFIX=01|*0.1.", 0),
    ("162_regex_infix_to_postfix", ["01"], "POSTFIX=01.", 0),
    ("162_regex_infix_to_postfix", ["0|"], "Invalid", 2),
    ("163_dfa_transition_cover", [], "TRANSITIONS=8", 0),
    ("164_dfa_shortest_reset_word", [], "RESET_WORD=00", 0),
    ("165_dfa_tarjan_scc", [], "SCC_COUNT=4", 0),
    ("166_dfa_left_quotient", ["1", "01"], "ACCEPT", 0),
    ("166_dfa_left_quotient", ["", "10"], "REJECT", 0),
    ("166_dfa_left_quotient", ["2", "01"], "binary", 2),
    ("167_dfa_right_quotient", ["1"], "ACCEPT", 0),
    ("167_dfa_right_quotient", ["0"], "REJECT", 0),
    ("168_reversed_dfa_nfa", ["10"], "ACCEPT", 0),
    ("168_reversed_dfa_nfa", ["01"], "REJECT", 0),
    ("169_dfa_state_pair_witnesses", [], "q0,q2=EQUIVALENT", 0),
    ("169_dfa_state_pair_witnesses", [], "q1,q3=EQUIVALENT", 0),
    ("169_dfa_state_pair_witnesses", [], "q0,q1=<epsilon>", 0),
    ("170_nfa_dfa_exhaustive_crosscheck", [], "CHECKED=511 MISMATCHES=0", 0),
]
for filename, arguments, substring, code in cases:
    proc = subprocess.run([str(root / filename), *arguments],
                          capture_output=True, text=True, timeout=10)
    output = proc.stdout if code == 0 else proc.stderr
    assert proc.returncode == code and substring in output, (
        filename, arguments, code, substring, proc.returncode, proc.stdout, proc.stderr
    )
print(f"{len(cases)} tests passed")
