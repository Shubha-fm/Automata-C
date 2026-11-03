/* Program 181: Minimum accepting cost of a nondeterministic weighted finite automaton. C11. */
#include <stdio.h>
#include <limits.h>
#define INF (INT_MAX/4)
static void minimum(int *dst,int value){if(value<*dst)*dst=value;}
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    int cost[3]={0,INF,INF};
    for(const char *s=argv[1];*s;s++){
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
        int next[3]={INF,INF,INF};
        if(cost[0]<INF){
            minimum(&next[0],cost[0]+2);
            if(*s=='0')minimum(&next[1],cost[0]+1);
        }
        if(cost[1]<INF){
            if(*s=='0')minimum(&next[1],cost[1]+1);
            else minimum(&next[2],cost[1]+3);
        }
        if(cost[2]<INF)minimum(&next[2],cost[2]+1);
        for(int i=0;i<3;i++)cost[i]=next[i];
    }
    if(cost[2]==INF)puts("NO_ACCEPTING_PATH");
    else printf("MIN_COST=%d\n",cost[2]);
    return 0;
}
