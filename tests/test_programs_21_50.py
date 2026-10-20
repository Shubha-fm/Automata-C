#!/usr/bin/env python3
"""Regression tests for programs 21-50."""
import pathlib
import subprocess
ROOT = pathlib.Path(__file__).resolve().parents[1]
CASES = [{"name":"21_contains_010","kind":"contains","pattern":"010","sym":null,"mod":null},{"name":"22_contains_110","kind":"contains","pattern":"110","sym":null,"mod":null},{"name":"23_contains_0010","kind":"contains","pattern":"0010","sym":null,"mod":null},{"name":"24_contains_0110","kind":"contains","pattern":"0110","sym":null,"mod":null},{"name":"25_contains_1001","kind":"contains","pattern":"1001","sym":null,"mod":null},{"name":"26_contains_000","kind":"contains","pattern":"000","sym":null,"mod":null},{"name":"27_contains_111","kind":"contains","pattern":"111","sym":null,"mod":null},{"name":"28_contains_0101","kind":"contains","pattern":"0101","sym":null,"mod":null},{"name":"29_contains_1010","kind":"contains","pattern":"1010","sym":null,"mod":null},{"name":"30_contains_0011","kind":"contains","pattern":"0011","sym":null,"mod":null},{"name":"31_ends_010","kind":"suffix","pattern":"010","sym":null,"mod":null},{"name":"32_ends_110","kind":"suffix","pattern":"110","sym":null,"mod":null},{"name":"33_ends_0010","kind":"suffix","pattern":"0010","sym":null,"mod":null},{"name":"34_ends_0110","kind":"suffix","pattern":"0110","sym":null,"mod":null},{"name":"35_ends_1001","kind":"suffix","pattern":"1001","sym":null,"mod":null},{"name":"36_ends_000","kind":"suffix","pattern":"000","sym":null,"mod":null},{"name":"37_ends_111","kind":"suffix","pattern":"111","sym":null,"mod":null},{"name":"38_ends_0101","kind":"suffix","pattern":"0101","sym":null,"mod":null},{"name":"39_ends_1010","kind":"suffix","pattern":"1010","sym":null,"mod":null},{"name":"40_ends_0011","kind":"suffix","pattern":"0011","sym":null,"mod":null},{"name":"41_starts_010","kind":"prefix","pattern":"010","sym":null,"mod":null},{"name":"42_starts_110","kind":"prefix","pattern":"110","sym":null,"mod":null},{"name":"43_starts_0010","kind":"prefix","pattern":"0010","sym":null,"mod":null},{"name":"44_starts_1011","kind":"prefix","pattern":"1011","sym":null,"mod":null},{"name":"45_starts_0001","kind":"prefix","pattern":"0001","sym":null,"mod":null},{"name":"46_count_0_multiple_4","kind":"count","pattern":null,"sym":0,"mod":4},{"name":"47_count_1_multiple_4","kind":"count","pattern":null,"sym":1,"mod":4},{"name":"48_count_0_multiple_5","kind":"count","pattern":null,"sym":0,"mod":5},{"name":"49_count_1_multiple_5","kind":"count","pattern":null,"sym":1,"mod":5},{"name":"50_count_0_multiple_6","kind":"count","pattern":null,"sym":0,"mod":6}]
def expected(c, s):
    if c['kind'] == 'contains': return c['pattern'] in s
    if c['kind'] == 'suffix': return s.endswith(c['pattern'])
    if c['kind'] == 'prefix': return s.startswith(c['pattern'])
    return s.count(str(c['sym'])) % c['mod'] == 0
checks = 0
for c in CASES:
    exe = ROOT / 'bin' / c['name']
    for s in ['', '0', '1', '0010', '010101', '111000', '10110101']:
        run = subprocess.run([str(exe), s], capture_output=True, text=True)
        assert run.returncode == 0, (c['name'], s, run.stderr)
        assert run.stdout.strip() == ('ACCEPT' if expected(c,s) else 'REJECT'), (c['name'],s,run.stdout)
        checks += 1
    bad = subprocess.run([str(exe), '10a1'],capture_output=True,text=True)
    assert bad.returncode == 2,(c['name'],bad.stderr)
    checks += 1
print(f'{checks} new-program tests passed')
