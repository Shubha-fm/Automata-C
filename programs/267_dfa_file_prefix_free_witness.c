/* 267: Check prefix-freeness and show two accepted words with a proper-prefix relation. ISO C11. */
#include "../include/dfa_io.h"
#define PAIRS (2*DFA_MAX)
static int continuation(const DFA *d,int start,char *out) {
    int seen[PAIRS]={0},parent[PAIRS],edge[PAIRS],queue[PAIRS];
    for (int p=0;p<PAIRS;p++) { parent[p]=-1;edge[p]=-1; }
    int first=2*start,head=0,tail=1,goal=-1;
    queue[0]=first;seen[first]=1;
    while(head<tail) {
        int p=queue[head++],q=p/2,consumed=p%2;
        if (consumed&&d->final[q]) { goal=p;break; }
        for (int bit=0;bit<2;bit++) {
            int next=2*d->go[q][bit]+1;
            if (!seen[next]) {
                seen[next]=1;parent[next]=p;edge[next]=bit;queue[tail++]=next;
            }
        }
    }
    if (goal<0)return -1;
    int n=0;
    for (int p=goal;parent[p]>=0;p=parent[p])
        out[n++]=(char)('0'+edge[p]);
    for (int i=0;i<n/2;i++) {
        char c=out[i];out[i]=out[n-i-1];out[n-i-1]=c;
    }
    out[n]='\0';return n;
}
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    int seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX],queue[DFA_MAX];
    for (int i=0;i<d.n;i++) { parent[i]=-1;edge[i]=-1; }
    queue[0]=d.start;seen[d.start]=1;int head=0,tail=1;
    while (head<tail) {
        int q=queue[head++];
        if (d.final[q]) {
            char y[PAIRS+1];
            if (continuation(&d,q,y)>0) {
                char reversed[DFA_MAX+1],x[DFA_MAX+1];
                int n=0;
                for (int p=q;parent[p]>=0;p=parent[p])
                    reversed[n++]=(char)('0'+edge[p]);
                for (int i=0;i<n;i++)x[i]=reversed[n-i-1];
                x[n]='\0';
                printf("NOT_PREFIX_FREE PREFIX=%s EXTENDED=%s%s\n",
                       n?x:"<epsilon>",x,y);
                return 0;
            }
        }
        for (int bit=0;bit<2;bit++) {
            int next=d.go[q][bit];
            if (!seen[next]) {
                seen[next]=1;parent[next]=q;edge[next]=bit;queue[tail++]=next;
            }
        }
    }
    puts("PREFIX_FREE");return 0;
}
