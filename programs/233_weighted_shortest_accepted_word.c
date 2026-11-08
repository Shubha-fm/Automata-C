/* Program 233: Dijkstra search for the least-cost word accepted by a weighted automaton. ISO C11. */
#include <stdio.h>
#include <string.h>
#define N 4
#define INF 1000000
typedef struct{int from,to,cost;char symbol;}Edge;
static const Edge edges[]={
    {0,1,2,'0'},{0,2,5,'1'},{1,1,1,'0'},
    {1,3,1,'1'},{2,2,2,'1'},{2,3,1,'0'}
};
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"unreachable"))){
        fprintf(stderr,"Usage: %s [unreachable]\n",argv[0]);return 2;
    }
    int blocked=(argc==2);
    int distance[N],parent[N],visited[N]={0};
    char symbol[N];
    for(int i=0;i<N;i++){distance[i]=INF;parent[i]=-1;symbol[i]=0;}
    distance[0]=0;
    for(int iteration=0;iteration<N;iteration++){
        int q=-1;
        for(int i=0;i<N;i++)
            if(!visited[i]&&(q<0||distance[i]<distance[q]))q=i;
        if(q<0||distance[q]==INF)break;
        visited[q]=1;
        for(size_t i=0;i<sizeof(edges)/sizeof(edges[0]);i++){
            Edge e=edges[i];
            if(e.from!=q||(blocked&&e.to==3))continue;
            if(distance[q]+e.cost<distance[e.to]){
                distance[e.to]=distance[q]+e.cost;
                parent[e.to]=q;symbol[e.to]=e.symbol;
            }
        }
    }
    if(distance[3]==INF){puts("NO_ACCEPTED_WORD");return 0;}
    char word[N+1];int length=0;
    for(int q=3;parent[q]>=0;q=parent[q])word[length++]=symbol[q];
    printf("MIN_COST=%d WORD=",distance[3]);
    while(length)putchar(word[--length]);
    putchar('\n');return 0;
}
