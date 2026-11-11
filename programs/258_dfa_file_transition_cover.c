/* Program 258: Generate a BFS-based DFA transition coverage test suite. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    int seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX],queue[DFA_MAX];
    for (int q=0;q<d.n;q++) { parent[q]=-1;edge[q]=-1; }
    int head=0,tail=1;queue[0]=d.start;seen[d.start]=1;
    while (head<tail) {
        int q=queue[head++];
        for (int bit=0;bit<2;bit++) {
            int next=d.go[q][bit];
            if (!seen[next]) {
                seen[next]=1;parent[next]=q;edge[next]=bit;queue[tail++]=next;
            }
        }
    }
    for (int i=0;i<tail;i++) {
        int q=queue[i],length=0;
        char reverse[DFA_MAX+1];
        for (int p=q;parent[p]>=0;p=parent[p])
            reverse[length++]=(char)('0'+edge[p]);
        for (int bit=0;bit<2;bit++) {
            printf("q%d --%d--> q%d WORD=",q,bit,d.go[q][bit]);
            for (int k=length;k>0;k--) putchar(reverse[k-1]);
            putchar('0'+bit);putchar('\n');
        }
    }
    printf("COVERED_TRANSITIONS=%d\n",2*tail);
    return 0;
}
