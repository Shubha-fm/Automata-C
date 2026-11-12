/* 269: Construct the right ideal L Sigma-star of a binary DFA language. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    for (int q=0;q<d.n;q++)if (d.final[q]) {
        d.go[q][0]=q;d.go[q][1]=q;
    }
    dfa_write(&d);return 0;
}
