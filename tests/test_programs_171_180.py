#!/usr/bin/env python3
"""Compile with make, then run independent oracle checks on programs 171-180."""
import itertools
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / 'bin'
FIX = ROOT / 'examples'
checks = 0

def check(name, args, expected, code=0, full=True):
    global checks
    p = subprocess.run([str(BIN / name), *map(str, args)], capture_output=True,
                       text=True, timeout=10, cwd=ROOT)
    result = p.stdout.strip() if code == 0 else p.stderr.strip()
    assert p.returncode == code and (result == expected if full else expected in result), (
        name, args, expected, p.returncode, p.stdout, p.stderr)
    checks += 1

# Test first-match positions against Python string.find.
for pattern in ('0','1','01','10','001','111'):
    for length in range(6):
        for chars in itertools.product('01', repeat=length):
            word = ''.join(chars)
            where = word.find(pattern)
            check('171_kmp_binary_match', (pattern, word),
                  f'MATCH={where}' if where >= 0 else 'NOT_FOUND')
check('171_kmp_binary_match', ('', '101'), 'Pattern length', 2, False)
check('171_kmp_binary_match', ('0x','100'), '', 2)

# Aho-Corasick output, including overlapping matches, vs a simple scan.
patterns = ('001','010','111')
for length in range(7):
    for chars in itertools.product('01', repeat=length):
        word = ''.join(chars)
        matches = []
        for ending in range(len(word)):
            for pattern in patterns:
                if word[:ending+1].endswith(pattern):
                    matches.append(f'{pattern}@{ending+1-len(pattern)}')
        expected = '\n'.join([*matches, f'HITS={len(matches)}'])
        check('172_aho_binary_patterns', (word,), expected)
check('172_aho_binary_patterns', ('01z',), 'Binary input', 2, False)

for length in range(7):
    for chars in itertools.product('01', repeat=length):
        word = ''.join(chars)
        check('173_dfa_file_simulator', (FIX / 'dfa_ends_01.txt', word),
              'ACCEPT' if word.endswith('01') else 'REJECT')
        for prog, fixture in (
            ('174_nfa_file_simulator','nfa_contains_01.txt'),
            ('175_epsilon_nfa_file_simulator','enfa_contains_01.txt')):
            check(prog, (FIX / fixture, word),
                  'ACCEPT' if '01' in word else 'REJECT')

check('176_dfa_dot_export', (FIX / 'dfa_ends_01.txt',), 'digraph DFA {', 0, False)
check('176_dfa_dot_export', (FIX / 'dfa_ends_01.txt',), 'q1 -> q2 [label="1"]', 0, False)
check('177_dfa_partition_minimization', (), 'MINIMIZED_STATES=3', 0, False)
check('178_buchi_nonemptiness', (), 'CYCLIC_EXAMPLE=NONEMPTY state=q3', 0, False)
check('178_buchi_nonemptiness', (), 'ACYCLIC_EXAMPLE=EMPTY', 0, False)
check('179_moore_partition_minimization', (), 'MOORE_MINIMIZED_STATES=3', 0, False)
check('180_dfa_equivalence_from_files', (FIX/'dfa_ends_01.txt', FIX/'dfa_ends_01.txt'), 'EQUIVALENT')
check('180_dfa_equivalence_from_files', (FIX/'dfa_ends_01.txt', FIX/'dfa_ends_1.txt'), 'COUNTEREXAMPLE=1')
check('180_dfa_equivalence_from_files', (FIX/'missing.txt', FIX/'dfa_ends_1.txt'), 'Invalid DFA file', 2, False)
print(f'{checks} checks passed for programs 171-180')
