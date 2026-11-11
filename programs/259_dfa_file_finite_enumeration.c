/* Program 259: Enumerate up to 1000 lexicographically sorted words of a finite DFA language. ISO C11. */
#include "../include/dfa_io.h"
#define DISPLAY_LIMIT 1000
static DFA d;
static int reach[DFA_MAX],productive[DFA_MAX],color[DFA_MAX],done[DFA_MAX];
static unsigned long long count[DFA_MAX],shown=0;
static char word[DFA_MAX+1];
static void mark(int q) {
    reach[q]=1;
    for (int b=0;b<2;b++) {
        int z=d.go[q][b];if (!reach[z])mark(z);
    }
}
static int cycle(int q) {
    color[q]=1;
    for (int b=0;b<2;b++) {
        int z=d.go[q][b];
        if (!reach[z]||!productive[z])continue;
        if (color[z]==1) return 1;
        if (color[z]==0&&cycle(z))return 1;
    }
    color[q]=2;return 0;
}
static void compute(int q) {
    if (done[q])return;
    done[q]=1;count[q]=d.final[q]?1ULL:0ULL;
    for (int b=0;b<2;b++) {
        int z=d.go[q][b];if (!productive[z])continue;
        compute(z);count[q]+=count[z];
    }
}
static void emit(int q,int n) {
    if (shown>=DISPLAY_LIMIT)return;
    word[n]='\0';
    if (d.final[q]) {
        printf("WORD=%s\n",n?word:"<epsilon>");
        shown++;
    }
    for (int b=0;b<2&&shown<DISPLAY_LIMIT;b++) {
        int z=d.go[q][b];
        if (!productive[z])continue;
        word[n]=(char)('0'+b);
        emit(z,n+1);
    }
}
int main(int argc,char **argv) {
    if (argc!=2) { fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2; }
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    mark(d.start);
    for (int q=0;q<d.n;q++)productive[q]=d.final[q];
    int change;
    do {
        change=0;
        for (int q=0;q<d.n;q++)for (int b=0;b<2;b++) {
            int z=d.go[q][b];
            if (productive[z]&&!productive[q]) {
                productive[q]=1;change=1;
            }
        }
    } while (change);
    if (productive[d.start]&&cycle(d.start)) {
        puts("INFINITE_LANGUAGE");return 0;
    }
    if (productive[d.start]) {
        compute(d.start);emit(d.start,0);
    }
    printf("COUNT=%llu SHOWN=%llu TRUNCATED=%s\n",
           count[d.start],shown,count[d.start]>DISPLAY_LIMIT?"YES":"NO");
    return 0;
}
