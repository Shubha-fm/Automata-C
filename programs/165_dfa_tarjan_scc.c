/* 165: Compute strongly connected components of a DFA using Tarjan's algorithm. ISO C11. */
#include <stdio.h>
static const int delta[6][2]={{1,0},{2,1},{1,3},{4,3},{5,4},{4,5}};
static int index_of[6],low[6],onstack[6],stack[6],depth=0,time_id=0,count=0;
static void visit(int v){
    index_of[v]=low[v]=time_id++;
    stack[depth++]=v;onstack[v]=1;
    for(int b=0;b<2;b++){
        int w=delta[v][b];
        if(index_of[w]<0){
            visit(w);
            if(low[w]<low[v])low[v]=low[w];
        }else if(onstack[w]&&index_of[w]<low[v])low[v]=index_of[w];
    }
    if(low[v]==index_of[v]){
        printf("SCC %d:",count++);
        int w;
        do{w=stack[--depth];onstack[w]=0;printf(" q%d",w);}while(w!=v);
        putchar('\n');
    }
}
int main(void){
    for(int i=0;i<6;i++)index_of[i]=-1;
    for(int i=0;i<6;i++)if(index_of[i]<0)visit(i);
    printf("SCC_COUNT=%d\n",count);return 0;
}
