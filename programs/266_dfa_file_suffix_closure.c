/* 266: Construct the suffix closure by reachable-state NFA determinization. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_SUBSETS 1024
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (d.n>10) { fprintf(stderr,"Suffix closure limited to 10 input states\n");return 2; }
    int accessible[DFA_MAX]={0},queue_states[DFA_MAX],h=0,t=1;
    queue_states[0]=d.start;accessible[d.start]=1;
    while(h<t) {
        int q=queue_states[h++];
        for (int bit=0;bit<2;bit++) {
            int next=d.go[q][bit];
            if (!accessible[next]) {
                accessible[next]=1;queue_states[t++]=next;
            }
        }
    }
    int initial=0;
    for (int q=0;q<d.n;q++)if (accessible[q])initial|=1<<q;
    int id[MAX_SUBSETS],subsets[DFA_MAX],head=0,tail=1;
    for (int i=0;i<MAX_SUBSETS;i++)id[i]=-1;
    subsets[0]=initial;id[initial]=0;
    DFA out={0};out.start=0;
    while(head<tail) {
        int mask=subsets[head++],current=id[mask];
        int is_final=0;
        for (int q=0;q<d.n;q++)
            if ((mask&(1<<q))&&d.final[q])is_final=1;
        out.final[current]=is_final;
        for (int bit=0;bit<2;bit++) {
            int next=0;
            for (int q=0;q<d.n;q++)
                if (mask&(1<<q))next|=1<<d.go[q][bit];
            if (id[next]<0) {
                if (tail>=DFA_MAX) {
                    fprintf(stderr,"Suffix closure exceeds 32 output states\n");
                    return 2;
                }
                id[next]=tail;subsets[tail++]=next;
            }
            out.go[current][bit]=id[next];
        }
    }
    out.n=tail;dfa_write(&out);return 0;
}
