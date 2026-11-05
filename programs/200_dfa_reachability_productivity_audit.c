/* Program 200: Audit reachable, productive, dead, and unreachable DFA states. ISO C11. */
#include <stdio.h>
#define N 6
static const int delta[N][2]={{1,2},{3,1},{2,2},{3,3},{4,4},{5,5}};
static const int accepting[N]={0,0,0,1,0,0};
int main(void){
    int reachable[N]={1},productive[N]={0},q[N]={0},head=0,tail=1;
    while(head<tail){
        int v=q[head++];
        for(int b=0;b<2;b++){
            int w=delta[v][b];
            if(!reachable[w]){reachable[w]=1;q[tail++]=w;}
        }
    }
    for(int i=0;i<N;i++)productive[i]=accepting[i];
    int change;
    do{
        change=0;
        for(int i=0;i<N;i++)for(int b=0;b<2;b++)
            if(productive[delta[i][b]]&&!productive[i]){
                productive[i]=1;change=1;
            }
    }while(change);
    int r=0,p=0,d=0,u=0;
    for(int i=0;i<N;i++){
        if(reachable[i]){
            r++;
            if(productive[i])p++;else d++;
        }else u++;
    }
    printf("REACHABLE=%d PRODUCTIVE=%d DEAD=%d UNREACHABLE=%d\n",r,p,d,u);
    return 0;
}
