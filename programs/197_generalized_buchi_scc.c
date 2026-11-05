/* Program 197: Check two-set generalized Büchi acceptance using SCCs. ISO C11. */
#include <stdio.h>
#define N 4
static const int delta[N][2]={{1,3},{2,1},{1,2},{3,3}};
static const int f1[N]={0,1,0,0},f2[N]={0,0,1,0};
static int index_of[N],low[N],stack[N],onstack[N],counter,top,found;
static int reachable[N]={1,0,0,0};
static void dfs(int v){
    index_of[v]=low[v]=++counter;
    stack[top++]=v;onstack[v]=1;
    for(int b=0;b<2;b++){
        int w=delta[v][b];
        if(!reachable[w])continue;
        if(!index_of[w]){
            dfs(w);
            if(low[w]<low[v])low[v]=low[w];
        }else if(onstack[w]&&index_of[w]<low[v])low[v]=index_of[w];
    }
    if(low[v]==index_of[v]){
        int size=0,has1=0,has2=0;
        int w;
        do{
            w=stack[--top];onstack[w]=0;
            size++;has1|=f1[w];has2|=f2[w];
        }while(w!=v);
        int cyclic=(size>1);
        if(!cyclic)for(int b=0;b<2;b++)if(delta[v][b]==v)cyclic=1;
        if(cyclic&&has1&&has2)found=1;
    }
}
int main(void){
    int q[N]={0},h=0,t=1;
    while(h<t){
        int v=q[h++];
        for(int b=0;b<2;b++){
            int w=delta[v][b];
            if(!reachable[w]){reachable[w]=1;q[t++]=w;}
        }
    }
    for(int v=0;v<N;v++)if(reachable[v]&&!index_of[v])dfs(v);
    printf("GENERALIZED_BUCHI_NONEMPTY=%s\n",found?"YES":"NO");
    return 0;
}
