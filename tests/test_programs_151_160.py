"""Regression tests for programs 151–160 (run 'make' first)."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1] / "bin"

def run(name, *args):
    return subprocess.run([str(ROOT / name), *args],
                          capture_output=True, text=True, timeout=10)

tests = [
    ("151_epsilon_nfa_cycle_simulator", ["11010"], "ACCEPT", 0),
    ("151_epsilon_nfa_cycle_simulator", ["1111"], "REJECT", 0),
    ("151_epsilon_nfa_cycle_simulator", ["01"], "ACCEPT", 0),
    ("151_epsilon_nfa_cycle_simulator", ["01x"], "REJECT", 0),
    ("152_epsilon_nfa_subset_construction", [], "DFA_STATES=", 0),
    ("153_dfa_shortest_rejected_word", [], "SHORTEST_REJECTED=01", 0),
    ("154_dfa_shortest_access_words", [], "REACHABLE=5", 0),
    ("154_dfa_shortest_access_words", [], "q0=<epsilon>", 0),
    ("155_dfa_finiteness_productive_cycle", [], "FINITE_EXAMPLE=FINITE", 0),
    ("155_dfa_finiteness_productive_cycle", [], "INFINITE_EXAMPLE=INFINITE", 0),
    ("156_dfa_count_accepted_words", ["0"], "ACCEPTED=1", 0),
    ("156_dfa_count_accepted_words", ["4"], "ACCEPTED=8", 0),
    ("156_dfa_count_accepted_words", ["33"], "Length must", 2),
    ("157_nfa_count_accepting_paths", ["0101"], "ACCEPTING_PATHS=2", 0),
    ("157_nfa_count_accepting_paths", ["101"], "ACCEPTING_PATHS=1", 0),
    ("157_nfa_count_accepting_paths", ["11x"], "Binary only", 2),
    ("158_mealy_equivalence_witness", [], "WITNESS=11", 0),
    ("159_right_linear_grammar_recognizer", ["001001"], "ACCEPT", 0),
    ("159_right_linear_grammar_recognizer", ["00100"], "REJECT", 0),
    ("160_dfa_canonical_bfs_encoding", [], "REACHABLE_STATES=3", 0),
    ("160_dfa_canonical_bfs_encoding", [], "S0: 0->S1 1->S2 final=0", 0),
]
for name, args, phrase, code in tests:
    result = run(name, *args)
    output = result.stdout if code == 0 else result.stderr
    assert result.returncode == code and phrase in output, (
        name, args, code, phrase, result.stdout, result.stderr
    )
print(f"{len(tests)} regression checks passed")
