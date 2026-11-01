/* Program 154: Shortest access words for every reachable DFA state. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* BFS produces canonical shortest access strings, checking 0 before 1. */
static const int delta[5][2]={{1,2},{3,1},{2,4},{3,3},{4,4}};
int main(void) {
    int seen[5]={1},q[5]={0},parent[5]={-1,-1,-1,-1,-1};
    char edge[5]={0},word[6];
    int h=0,t=1;
    while(h<t){
        int s=q[h++];
        for(int b=0;b<2;b++){
            int z=delta[s][b];
            if(!seen[z]){seen[z]=1;q[t++]=z;parent[z]=s;edge[z]=(char)('0'+b);}
        }
    }
    for(int s=0;s<5;s++){
        if(!seen[s])continue;
        int n=0;
        for(int at=s;parent[at]>=0;at=parent[at])word[n++]=edge[at];
        printf("q%d=",s);
        if(!n)printf("<epsilon>");
        while(n)putchar(word[--n]);
        putchar('\n');
    }
    printf("REACHABLE=%d\n",t);
    return 0;
}
