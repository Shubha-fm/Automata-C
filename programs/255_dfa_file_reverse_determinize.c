/* Program 255: Reverse a DFA language and determinize it by subset construction. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_SUBSETS 1024
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (d.n>10) { fprintf(stderr,"Reversal limited to 10 input states\n");return 2; }
    static int id[MAX_SUBSETS],queue[DFA_MAX+1];
    for (int i=0;i<MAX_SUBSETS;i++)id[i]=-1;
    int initial=0;
    for (int q=0;q<d.n;q++) if (d.final[q])initial|=1<<q;
    queue[0]=initial;id[initial]=0;
    int head=0,tail=1;
    DFA out={0};out.start=0;
    while (head<tail) {
        int set=queue[head++],current=id[set];
        out.final[current]=!!(set&(1<<d.start));
        for (int bit=0;bit<2;bit++) {
            int next=0;
            for (int q=0;q<d.n;q++)
                if (set&(1<<d.go[q][bit]))next|=1<<q;
            if (id[next]<0) {
                if (tail>=DFA_MAX) {
                    fprintf(stderr,"Reversal exceeds 32 output states\n");return 2;
                }
                id[next]=tail;queue[tail++]=next;
            }
            out.go[current][bit]=id[next];
        }
    }
    out.n=tail;dfa_write(&out);return 0;
}
