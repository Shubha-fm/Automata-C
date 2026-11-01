CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
SOURCES := $(wildcard programs/*.c)
TARGETS := $(patsubst programs/%.c,bin/%,$(SOURCES))

.PHONY: all test test-new clean
all: $(TARGETS)
bin/%: programs/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@
test: all
	python3 tests/run_tests.py
test-new: all
	python3 tests/test_programs_151_160.py
clean:
	rm -rf bin
