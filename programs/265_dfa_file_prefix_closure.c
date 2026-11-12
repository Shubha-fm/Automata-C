/* 265: Construct the prefix closure of a regular language. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    int productive[DFA_MAX]={0},changed;
    for (int q=0;q<d.n;q++)productive[q]=d.final[q];
    do {
        changed=0;
        for (int q=0;q<d.n;q++)for (int bit=0;bit<2;bit++) {
            if (productive[d.go[q][bit]]&&!productive[q]) {
                productive[q]=1;changed=1;
            }
        }
    } while(changed);
    for (int q=0;q<d.n;q++)d.final[q]=productive[q];
    dfa_write(&d);
    return 0;
}
