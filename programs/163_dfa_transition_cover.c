/* 163: Construct a shortest-prefix transition coverage suite using BFS. ISO C11. */
#include <stdio.h>
static const int delta[4][2]={{1,2},{1,3},{2,3},{3,3}};
int main(void){
    int seen[4]={1},queue[4]={0},parent[4]={-1,-1,-1,-1};
    char edge[4]={0},path[6];int head=0,tail=1,covered=0;
    while(head<tail){
        int q=queue[head++];
        for(int b=0;b<2;b++){
            int next=delta[q][b];
            if(!seen[next]){
                seen[next]=1;queue[tail++]=next;
                parent[next]=q;edge[next]=(char)('0'+b);
            }
        }
    }
    for(int q=0;q<4;q++)if(seen[q]){
        int n=0,at=q;
        while(parent[at]>=0){path[n++]=edge[at];at=parent[at];}
        for(int b=0;b<2;b++){
            printf("EDGE q%d --%d--> q%d via ",q,b,delta[q][b]);
            for(int i=n-1;i>=0;i--)putchar(path[i]);
            putchar('0'+b);putchar('\n');covered++;
        }
    }
    printf("TRANSITIONS=%d\n",covered);
    return 0;
}
