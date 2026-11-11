/* Program 253: Find a shortest DFA synchronizing word using subset BFS (at most 12 states). ISO C11. */
#include "../include/dfa_io.h"
#define MASKS 4096
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (d.n>12) { fprintf(stderr,"Synchronization limited to 12 states\n");return 2; }
    static int parent[MASKS],edge[MASKS],seen[MASKS],queue[MASKS];
    for (int i=0;i<MASKS;i++) { parent[i]=-1;edge[i]=-1; }
    int start=(1<<d.n)-1,head=0,tail=1,goal=-1;
    queue[0]=start;seen[start]=1;
    while (head<tail) {
        int mask=queue[head++];
        if (!(mask&(mask-1))) { goal=mask;break; }
        for (int bit=0;bit<2;bit++) {
            int next=0;
            for (int q=0;q<d.n;q++)
                if (mask&(1<<q)) next|=1<<d.go[q][bit];
            if (!seen[next]) {
                seen[next]=1;parent[next]=mask;edge[next]=bit;
                queue[tail++]=next;
            }
        }
    }
    if (goal<0) { puts("NOT_SYNCHRONIZING");return 0; }
    char word[MASKS+1];int n=0;
    for (int q=goal;parent[q]>=0;q=parent[q])
        word[n++]=(char)('0'+edge[q]);
    printf("RESET_WORD=");
    if (!n) printf("<epsilon>");
    while (n) { putchar(word[--n]); }
    putchar('\n');
    return 0;
}
