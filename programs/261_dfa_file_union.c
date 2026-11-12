/* 261: Construct the DFA product recognizing union of two binary languages. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=3) { fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2; }
    DFA a,b;
    if (!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)) {
        fprintf(stderr,"Invalid DFA file\n");return 2;
    }
    if (a.n*b.n>DFA_MAX) {
        fprintf(stderr,"Product exceeds 32 states\n");return 2;
    }
    DFA out={0};out.n=a.n*b.n;out.start=a.start*b.n+b.start;
    for (int q=0;q<a.n;q++)for (int r=0;r<b.n;r++) {
        int p=q*b.n+r;
        out.final[p]=a.final[q]||b.final[r];
        for (int bit=0;bit<2;bit++)
            out.go[p][bit]=a.go[q][bit]*b.n+b.go[r][bit];
    }
    dfa_write(&out);
    return 0;
}
