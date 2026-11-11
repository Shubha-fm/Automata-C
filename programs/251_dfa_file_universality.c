/* Program 251: Determine DFA universality and produce a shortest rejected word. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]); return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n"); return 2; }
    int queue[DFA_MAX],parent[DFA_MAX],edge[DFA_MAX],seen[DFA_MAX]={0};
    for (int q=0;q<d.n;q++) { parent[q]=-1; edge[q]=-1; }
    int head=0,tail=1,goal=-1;
    queue[0]=d.start; seen[d.start]=1;
    while (head<tail) {
        int q=queue[head++];
        if (!d.final[q]) { goal=q; break; }
        for (int b=0;b<2;b++) {
            int next=d.go[q][b];
            if (!seen[next]) {
                seen[next]=1;parent[next]=q;edge[next]=b;queue[tail++]=next;
            }
        }
    }
    if (goal<0) { puts("UNIVERSAL"); return 0; }
    char word[DFA_MAX+1];int n=0;
    for (int q=goal;parent[q]>=0;q=parent[q])
        word[n++]=(char)('0'+edge[q]);
    printf("NOT_UNIVERSAL WITNESS=");
    if (!n) printf("<epsilon>");
    while (n) { putchar(word[--n]); }
    putchar('\n');
    return 0;
}
