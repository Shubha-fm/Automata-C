/* Program 214: Recover a minimum-cost accepting state sequence in a weighted NFA. ISO C11. */
#include <stdio.h>
#include <string.h>
#define LIMIT 256
#define INF 100000000
static signed short predecessor[LIMIT+1][3];
static void update(int next[3],signed short back[3],int dest,int cost,int source){
    if(cost<next[dest]){next[dest]=cost;back[dest]=(signed short)source;}
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>LIMIT){fprintf(stderr,"Maximum length is 256\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
        fprintf(stderr,"Binary alphabet only\n");return 2;
    }
    int cost[3]={0,INF,INF};
    for(size_t i=0;i<n;i++){
        int next[3]={INF,INF,INF};
        signed short back[3]={-1,-1,-1};
        if(cost[0]<INF){
            update(next,back,0,cost[0]+2,0);
            if(s[i]=='0')update(next,back,1,cost[0]+1,0);
        }
        if(cost[1]<INF){
            if(s[i]=='0')update(next,back,1,cost[1]+1,1);
            else update(next,back,2,cost[1]+3,1);
        }
        if(cost[2]<INF)update(next,back,2,cost[2]+1,2);
        for(int q=0;q<3;q++){cost[q]=next[q];predecessor[i+1][q]=back[q];}
    }
    if(cost[2]>=INF){puts("NO_ACCEPTING_PATH");return 0;}
    int states[LIMIT+1];states[n]=2;
    for(size_t i=n;i>0;i--){
        int prev=predecessor[i][states[i]];
        if(prev<0)return 1;
        states[i-1]=prev;
    }
    printf("MIN_COST=%d PATH=",cost[2]);
    for(size_t i=0;i<=n;i++)printf("%sq%d",i?"->":"",states[i]);
    putchar('\n');return 0;
}
