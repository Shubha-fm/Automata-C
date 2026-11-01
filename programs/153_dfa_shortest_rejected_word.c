/* Program 153: Find the shortest rejected word using BFS. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* The DFA accepts every binary word except those containing 01. */
static const int delta[3][2]={{1,0},{1,2},{2,2}};
static const int final[3]={1,1,0};
int main(void) {
    int seen[3]={1,0,0},q[3]={0},parent[3]={-1,-1,-1};
    char edge[3]={0},word[4];
    int h=0,t=1,goal=-1;
    while(h<t){
        int s=q[h++];
        if(!final[s]){goal=s;break;}
        for(int b=0;b<2;b++){
            int z=delta[s][b];
            if(!seen[z]){seen[z]=1;parent[z]=s;edge[z]=(char)('0'+b);q[t++]=z;}
        }
    }
    if(goal<0){puts("NO_REJECTED_WORD");return 0;}
    int n=0;
    for(int s=goal;parent[s]>=0;s=parent[s])word[n++]=edge[s];
    printf("SHORTEST_REJECTED=");
    if(n==0)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');
    return 0;
}
