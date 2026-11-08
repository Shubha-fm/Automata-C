CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
SOURCES := $(wildcard programs/*.c)
TARGETS := $(patsubst programs/%.c,bin/%,$(SOURCES))

.PHONY: test-231-240 test-221-230 test-211-220 test-201-210 test-191-200 test-181-190 all test-171-180 test test-new test-161-170 clean
all: $(TARGETS)
bin/%: programs/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@
test: all
	python3 tests/run_tests.py
test-new: all
	python3 tests/test_programs_151_160.py
test-161-170: all
	python3 tests/test_programs_161_170.py
test-171-180: all
	python3 tests/test_programs_171_180.py
test-181-190: $(patsubst programs/%.c,bin/%,$(wildcard programs/18[1-9]_*.c programs/190_*.c))
	python3 tests/test_programs_181_190.py
test-191-200: $(patsubst programs/%.c,bin/%,$(wildcard programs/19[1-9]_*.c programs/200_*.c))
	python3 tests/test_programs_191_200.py
test-201-210: $(patsubst programs/%.c,bin/%,$(wildcard programs/20[1-9]_*.c programs/210_*.c))
	python3 tests/test_programs_201_210.py
test-211-220: $(patsubst programs/%.c,bin/%,$(wildcard programs/21[1-9]_*.c programs/220_*.c))
	python3 tests/test_programs_211_220.py
test-221-230: $(patsubst programs/%.c,bin/%,$(wildcard programs/22[1-9]_*.c programs/230_*.c))
	python3 tests/test_programs_221_230.py
test-231-240: $(patsubst programs/%.c,bin/%,$(wildcard programs/23[1-9]_*.c programs/240_*.c))
	python3 tests/test_programs_231_240.py
clean:
	rm -rf bin
