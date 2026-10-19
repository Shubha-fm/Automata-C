/* 20_even_length: Even-length binary strings. Binary alphabet {0,1}. */
#include <stdio.h>
#include <string.h>

#define STATE_COUNT 2
static const int transition[STATE_COUNT][2] = {
    {1, 1},
    {0, 0}
};
static const int accepting[STATE_COUNT] = { 1, 0 };

static int accepts(const char *s) {
    int state = 0;
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] != '0' && s[i] != '1') return -1;
        state = transition[state][s[i] - '0'];
    }
    return accepting[state];
}

int main(int argc, char **argv) {
    char buffer[4096];
    const char *input;
    if (argc > 2) { fprintf(stderr, "Usage: %s [binary-string]\n", argv[0]); return 2; }
    if (argc == 2) input = argv[1];
    else {
        printf("Enter a binary string (empty string allowed): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) return 2;
        buffer[strcspn(buffer, "\r\n")] = '\0';
        input = buffer;
    }
    int result = accepts(input);
    if (result < 0) { fprintf(stderr, "Invalid symbol: only 0 and 1 are allowed\n"); return 2; }
    puts(result ? "ACCEPT" : "REJECT");
    return 0;
}
