/* 264: Construct the right quotient of a DFA language by a binary word. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=3) { fprintf(stderr,"Usage: %s MODEL.dfa SUFFIX\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    size_t n=strlen(argv[2]);
    if (n>4096) { fprintf(stderr,"Maximum suffix length is 4096\n");return 2; }
    for (size_t i=0;i<n;i++)
        if (argv[2][i]!='0'&&argv[2][i]!='1') {
            fprintf(stderr,"Binary suffix required\n");return 2;
        }
    DFA out=d;
    for (int q=0;q<d.n;q++) {
        int state=q;
        for (size_t i=0;i<n;i++)state=d.go[state][argv[2][i]-'0'];
        out.final[q]=d.final[state];
    }
    dfa_write(&out);
    return 0;
}
