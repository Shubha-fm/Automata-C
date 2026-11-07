/* Program 228: Shortest accepted word in an epsilon-NFA using zero-one BFS. C11. */
#include <stdio.h>
#define N 4
#define INF 1000000
static int best[N],parent[N],label[N],used[N];
static void improve(int from,int to,int weight,int symbol){
    if(best[from]+weight<best[to]){
        best[to]=best[from]+weight;parent[to]=from;label[to]=symbol;
    }
}
int main(void){
    for(int i=0;i<N;i++){best[i]=INF;parent[i]=-1;label[i]=-1;}
    best[0]=0;
    for(int k=0;k<N;k++){
        int current=-1;
        for(int q=0;q<N;q++)if(!used[q]&&
            (current<0||best[q]<best[current]))current=q;
        if(current<0||best[current]==INF)break;
        used[current]=1;
        if(current==0)improve(0,1,0,-1);
        if(current==1){
            improve(1,0,0,-1);improve(1,2,1,'0');
        }
        if(current==2)improve(2,3,1,'1');
    }
    if(best[3]==INF){puts("EMPTY_LANGUAGE");return 0;}
    char word[N+1];int n=0;
    for(int q=3;parent[q]>=0;q=parent[q])
        if(label[q]>=0)word[n++]=(char)label[q];
    printf("SHORTEST=");
    if(!n)printf("<epsilon>");
    while(n)putchar(word[--n]);
    printf(" LENGTH=%d\n",best[3]);
    return 0;
}

