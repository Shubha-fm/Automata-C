/* Program 36: Ends with substring 000; alphabet: {0, 1}. */
#include <stdio.h>
#include <string.h>

#define STATES 4
static const unsigned int next_state[STATES][2] = {
    {1, 0},
    {2, 0},
    {3, 0},
    {3, 0}
};
static const unsigned int is_final[STATES] = {0, 0, 0, 1};

static int check(const char *input) {
    unsigned int state = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] != '0' && input[i] != '1') return -1;
        state = next_state[state][input[i] - '0'];
    }
    return (int)is_final[state];
}

int main(int argc, char **argv) {
    char buffer[4096];
    const char *input;
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [binary-string]\n", argv[0]);
        return 2;
    }
    if (argc == 2) input = argv[1];
    else {
        printf("Enter a binary string: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) return 2;
        buffer[strcspn(buffer, "\r\n")] = '\0';
        input = buffer;
    }
    int result = check(input);
    if (result == -1) {
        fprintf(stderr, "Invalid input: only binary digits allowed\n");
        return 2;
    }
    puts(result ? "ACCEPT" : "REJECT");
    return 0;
}
