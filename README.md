# Automata-C: 20 Programs in C

20 standalone deterministic finite automata in ISO C11. Each uses a transition table and accepting states to recognize a binary language.

## Run
```sh
make
make test
./bin/03_ends_01 1101
```

Compile any single program:
```sh
gcc -std=c11 -Wall -Wextra -Wpedantic programs/03_ends_01.c -o automata
./automata 1101
```

Programs accept a binary string as an argument or prompt for one via standard input. Outputs are `ACCEPT` or `REJECT`. Invalid characters produce exit status 2. The alphabet is `{0,1}`; empty strings are allowed.

## Programs

| # | Source | Recognized language |
|---|---|---|
| 1 | [01_even_zeros.c](programs/01_even_zeros.c) | Even number of zeros |
| 2 | [02_odd_ones.c](programs/02_odd_ones.c) | Odd number of ones |
| 3 | [03_ends_01.c](programs/03_ends_01.c) | Ends in 01 |
| 4 | [04_ends_10.c](programs/04_ends_10.c) | Ends in 10 |
| 5 | [05_contains_00.c](programs/05_contains_00.c) | Contains 00 |
| 6 | [06_contains_11.c](programs/06_contains_11.c) | Contains 11 |
| 7 | [07_no_consecutive_ones.c](programs/07_no_consecutive_ones.c) | No adjacent ones |
| 8 | [08_no_consecutive_zeros.c](programs/08_no_consecutive_zeros.c) | No adjacent zeros |
| 9 | [09_binary_divisible_3.c](programs/09_binary_divisible_3.c) | Binary integer divisible by 3 |
| 10 | [10_binary_divisible_5.c](programs/10_binary_divisible_5.c) | Binary integer divisible by 5 |
| 11 | [11_zeros_mod_3.c](programs/11_zeros_mod_3.c) | Zero count divisible by 3 |
| 12 | [12_ones_mod_3.c](programs/12_ones_mod_3.c) | One count divisible by 3 |
| 13 | [13_even_zeros_odd_ones.c](programs/13_even_zeros_odd_ones.c) | Even zeros and odd ones |
| 14 | [14_even_zeros_even_ones.c](programs/14_even_zeros_even_ones.c) | Even zeros and even ones |
| 15 | [15_start_1.c](programs/15_start_1.c) | Starts with 1 |
| 16 | [16_exactly_two_ones.c](programs/16_exactly_two_ones.c) | Exactly two ones |
| 17 | [17_at_least_three_zeros.c](programs/17_at_least_three_zeros.c) | At least three zeros |
| 18 | [18_contains_101.c](programs/18_contains_101.c) | Contains substring 101 |
| 19 | [19_ends_001.c](programs/19_ends_001.c) | Ends in 001 |
| 20 | [20_even_length.c](programs/20_even_length.c) | Even-length binary strings |

## Test
Run `make test` to compile all 20 programs and check accepted, rejected and invalid inputs. All models are independent DFAs, not general regex engines.

## License
MIT.
