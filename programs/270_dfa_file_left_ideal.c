/* 270: Construct the left ideal Sigma-star L using substring NFA determinization. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_SUBSETS 1024
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (d.n>10) { fprintf(stderr,"Left ideal limited to 10 input states\n");return 2; }
    int id[MAX_SUBSETS],queue[DFA_MAX],h=0,t=1;
    for (int i=0;i<MAX_SUBSETS;i++)id[i]=-1;
    int initial=1<<d.start;
    queue[0]=initial;id[initial]=0;
    DFA out={0};out.start=0;
    while(h<t) {
        int mask=queue[h++],current=id[mask],accepted=0;
        for (int q=0;q<d.n;q++)
            if ((mask&(1<<q))&&d.final[q])accepted=1;
        out.final[current]=accepted;
        for (int bit=0;bit<2;bit++) {
            int next=1<<d.start; /* allow a new candidate suffix */
            for (int q=0;q<d.n;q++)
                if (mask&(1<<q))next|=1<<d.go[q][bit];
            if (id[next]<0) {
                if (t>=DFA_MAX) {
                    fprintf(stderr,"Left ideal exceeds 32 output states\n");
                    return 2;
                }
                id[next]=t;queue[t++]=next;
            }
            out.go[current][bit]=id[next];
        }
    }
    out.n=t;dfa_write(&out);return 0;
}
