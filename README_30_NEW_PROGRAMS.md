# 30 additional automata programs (21–50)

These standalone C11 DFA programs extend the original 20. All existing source files remain untouched.

## Catalog

- **21.** [contains_010](programs/21_contains_010.c): Contains substring 010
- **22.** [contains_110](programs/22_contains_110.c): Contains substring 110
- **23.** [contains_0010](programs/23_contains_0010.c): Contains substring 0010
- **24.** [contains_0110](programs/24_contains_0110.c): Contains substring 0110
- **25.** [contains_1001](programs/25_contains_1001.c): Contains substring 1001
- **26.** [contains_000](programs/26_contains_000.c): Contains substring 000
- **27.** [contains_111](programs/27_contains_111.c): Contains substring 111
- **28.** [contains_0101](programs/28_contains_0101.c): Contains substring 0101
- **29.** [contains_1010](programs/29_contains_1010.c): Contains substring 1010
- **30.** [contains_0011](programs/30_contains_0011.c): Contains substring 0011
- **31.** [ends_010](programs/31_ends_010.c): Ends with substring 010
- **32.** [ends_110](programs/32_ends_110.c): Ends with substring 110
- **33.** [ends_0010](programs/33_ends_0010.c): Ends with substring 0010
- **34.** [ends_0110](programs/34_ends_0110.c): Ends with substring 0110
- **35.** [ends_1001](programs/35_ends_1001.c): Ends with substring 1001
- **36.** [ends_000](programs/36_ends_000.c): Ends with substring 000
- **37.** [ends_111](programs/37_ends_111.c): Ends with substring 111
- **38.** [ends_0101](programs/38_ends_0101.c): Ends with substring 0101
- **39.** [ends_1010](programs/39_ends_1010.c): Ends with substring 1010
- **40.** [ends_0011](programs/40_ends_0011.c): Ends with substring 0011
- **41.** [starts_010](programs/41_starts_010.c): Starts with substring 010
- **42.** [starts_110](programs/42_starts_110.c): Starts with substring 110
- **43.** [starts_0010](programs/43_starts_0010.c): Starts with substring 0010
- **44.** [starts_1011](programs/44_starts_1011.c): Starts with substring 1011
- **45.** [starts_0001](programs/45_starts_0001.c): Starts with substring 0001
- **46.** [count_0_multiple_4](programs/46_count_0_multiple_4.c): Number of 0 symbols is divisible by 4
- **47.** [count_1_multiple_4](programs/47_count_1_multiple_4.c): Number of 1 symbols is divisible by 4
- **48.** [count_0_multiple_5](programs/48_count_0_multiple_5.c): Number of 0 symbols is divisible by 5
- **49.** [count_1_multiple_5](programs/49_count_1_multiple_5.c): Number of 1 symbols is divisible by 5
- **50.** [count_0_multiple_6](programs/50_count_0_multiple_6.c): Number of 0 symbols is divisible by 6

## Build and test

```sh
make
python3 tests/test_programs_21_50.py
./bin/21_contains_010 110101
```

Each program accepts a binary input as an argument or reads it interactively. All recognize the empty string when their language includes it. Input symbols other than 0 and 1 result in exit status 2. The repository's existing Makefile compiles all programs automatically.
