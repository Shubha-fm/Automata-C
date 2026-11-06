/* Program 220: Determine finite-language cardinality or detect infinite accepted words. ISO C11. */
#include <stdio.h>
#include <string.h>
#define N 4
static int delta[N][2]={{1,3},{2,2},{3,3},{3,3}};
static const int accepting[N]={0,0,1,0};
static int reachable[N],productive[N],color[N];
static unsigned long long counts[N];
static int lengths[N];
static int has_cycle(int q){
    color[q]=1;
    for(int bit=0;bit<2;bit++){
        int t=delta[q][bit];
        if(!reachable[t]||!productive[t])continue;
        if(color[t]==1)return 1;
        if(color[t]==0&&has_cycle(t))return 1;
    }
    color[q]=2;return 0;
}
static void calculate(int q){
    if(color[q])return;
    color[q]=1;
    counts[q]=accepting[q]?1u:0u;
    lengths[q]=accepting[q]?0:-1;
    for(int bit=0;bit<2;bit++){
        int t=delta[q][bit];
        if(!productive[t])continue;
        calculate(t);
        counts[q]+=counts[t];
        if(lengths[t]>=0&&lengths[t]+1>lengths[q])
            lengths[q]=lengths[t]+1;
    }
}
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"infinite"))){
        fprintf(stderr,"Usage: %s [infinite]\n",argv[0]);return 2;
    }
    if(argc==2){delta[1][0]=1;delta[1][1]=2;}
    int queue[N]={0},h=0,t=1;reachable[0]=1;
    while(h<t){
        int q=queue[h++];
        for(int bit=0;bit<2;bit++){
            int z=delta[q][bit];
            if(!reachable[z]){reachable[z]=1;queue[t++]=z;}
        }
    }
    for(int q=0;q<N;q++)productive[q]=accepting[q];
    int changed;
    do{
        changed=0;
        for(int q=0;q<N;q++)for(int bit=0;bit<2;bit++)
            if(productive[delta[q][bit]]&&!productive[q]){
                productive[q]=1;changed=1;
            }
    }while(changed);
    if(productive[0]&&has_cycle(0)){puts("LANGUAGE=INFINITE");return 0;}
    memset(color,0,sizeof color);
    if(productive[0])calculate(0);
    printf("LANGUAGE=FINITE COUNT=%llu MAX_LENGTH=%d\n",
           counts[0],lengths[0]);
    return 0;
}
