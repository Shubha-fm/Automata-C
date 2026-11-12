/* 263: Construct the left quotient of a DFA language by a binary word. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=3) { fprintf(stderr,"Usage: %s MODEL.dfa PREFIX\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    size_t n=strlen(argv[2]);
    if (n>4096) { fprintf(stderr,"Maximum prefix length is 4096\n");return 2; }
    int start=d.start;
    for (size_t i=0;i<n;i++) {
        char ch=argv[2][i];
        if (ch!='0'&&ch!='1') { fprintf(stderr,"Binary prefix required\n");return 2; }
        start=d.go[start][ch-'0'];
    }
    d.start=start;dfa_write(&d);
    return 0;
}
