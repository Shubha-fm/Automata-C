/* Program 252: Test DFA language finiteness and compute exact finite cardinality. ISO C11. */
#include "../include/dfa_io.h"
static DFA d;
static int reach[DFA_MAX],productive[DFA_MAX],color[DFA_MAX],calculated[DFA_MAX];
static int longest[DFA_MAX];
static unsigned long long number[DFA_MAX];
static void visit(int q) {
    reach[q]=1;
    for (int b=0;b<2;b++) {
        int next=d.go[q][b];
        if (!reach[next]) visit(next);
    }
}
static int has_cycle(int q) {
    color[q]=1;
    for (int b=0;b<2;b++) {
        int next=d.go[q][b];
        if (!reach[next] || !productive[next]) continue;
        if (color[next]==1) return 1;
        if (color[next]==0 && has_cycle(next)) return 1;
    }
    color[q]=2;
    return 0;
}
static void count(int q) {
    if (calculated[q]) return;
    calculated[q]=1;
    number[q]=d.final[q]?1ULL:0ULL;
    longest[q]=d.final[q]?0:-1;
    for (int b=0;b<2;b++) {
        int next=d.go[q][b];
        if (!productive[next]) continue;
        count(next);
        number[q]+=number[next];
        if (longest[next]>=0 && longest[next]+1>longest[q])
            longest[q]=longest[next]+1;
    }
}
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]); return 2; }
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n"); return 2; }
    visit(d.start);
    for (int q=0;q<d.n;q++) productive[q]=d.final[q];
    int changed;
    do {
        changed=0;
        for (int q=0;q<d.n;q++) for (int b=0;b<2;b++) {
            int next=d.go[q][b];
            if (productive[next] && !productive[q]) {
                productive[q]=1;changed=1;
            }
        }
    } while (changed);
    if (productive[d.start] && has_cycle(d.start)) {
        puts("INFINITE");return 0;
    }
    if (!productive[d.start]) {
        puts("FINITE COUNT=0 MAX_LENGTH=-1");return 0;
    }
    count(d.start);
    printf("FINITE COUNT=%llu MAX_LENGTH=%d\n",
           number[d.start],longest[d.start]);
    return 0;
}
