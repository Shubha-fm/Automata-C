/* Program 55: String length divisible by four. DFA over {0,1}. */
#include <stdio.h>
#include <string.h>
#define STATES 4
static const unsigned char next_state[STATES][2] = {
    {1, 1},
    {2, 2},
    {3, 3},
    {0, 0}
};
static const unsigned char accepting[STATES] = {1, 0, 0, 0};

int main(int argc, char **argv) {
    char buf[4096];
    const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [binary-string]\n", argv[0]); return 2; }
    if (argc == 2) s = argv[1];
    else {
        printf("Enter binary string: ");
        if (!fgets(buf, sizeof buf, stdin)) return 2;
        buf[strcspn(buf, "\r\n")] = '\0'; s = buf;
    }
    unsigned state = 0;
    for (size_t i = 0; s[i]; ++i) {
        if (s[i] != '0' && s[i] != '1') {
            fprintf(stderr, "Only 0 and 1 are supported\n"); return 2;
        }
        state = next_state[state][s[i]-'0'];
    }
    puts(accepting[state] ? "ACCEPT" : "REJECT");
    return 0;
}
