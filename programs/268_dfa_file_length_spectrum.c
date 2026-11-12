/* 268: List accepted word lengths up to a specified upper bound. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=3) { fprintf(stderr,"Usage: %s MODEL.dfa MAX_LENGTH\n",argv[0]);return 2; }
    DFA d;long bound;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (!dfa_length(argv[2],10000,&bound)) {
        fprintf(stderr,"MAX_LENGTH must be 0..10000\n");return 2;
    }
    int active[DFA_MAX]={0};active[d.start]=1;
    int count=0;printf("ACCEPTED_LENGTHS=");
    for (long length=0;length<=bound;length++) {
        int accepted=0;
        for (int q=0;q<d.n;q++)if (active[q]&&d.final[q])accepted=1;
        if (accepted) {
            printf("%s%ld",count?",":"",length);count++;
        }
        if (length<bound) {
            int next[DFA_MAX]={0};
            for (int q=0;q<d.n;q++)if (active[q])
                for (int bit=0;bit<2;bit++)next[d.go[q][bit]]=1;
            for (int q=0;q<d.n;q++)active[q]=next[q];
        }
    }
    if (!count)printf("<none>");
    printf("\nCOUNT=%d\n",count);return 0;
}
