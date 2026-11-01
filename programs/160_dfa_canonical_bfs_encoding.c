/* Program 160: Canonical reachable-state renumbering of a sample DFA. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* Unreachable state 3 is discarded; other states are numbered by BFS. */
static const int delta[4][2]={{2,1},{1,2},{2,1},{3,3}};
static const int accepting[4]={0,1,0,1};
int main(void){
    int id[4]={-1,-1,-1,-1},queue[4]={0},h=0,t=1;
    id[0]=0;
    while(h<t){
        int s=queue[h++];
        for(int bit=0;bit<2;bit++){
            int z=delta[s][bit];
            if(id[z]<0){id[z]=t;queue[t++]=z;}
        }
    }
    printf("REACHABLE_STATES=%d\n",t);
    for(int i=0;i<t;i++){
        int s=queue[i];
        printf("S%d: 0->S%d 1->S%d final=%d\n",
               i,id[delta[s][0]],id[delta[s][1]],accepting[s]);
    }
    return 0;
}
