/* Program 240: Construct a witness lasso visiting two Büchi acceptance sets infinitely often. ISO C11. */
#include <stdio.h>
#include <string.h>
/* Acceptance sets: F1={q1}, F2={q2}. */
static int delta[4][2]={{1,3},{1,2},{1,2},{3,3}};
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"no_cycle"))){
        fprintf(stderr,"Usage: %s [no_cycle]\n",argv[0]);return 2;
    }
    if(argc==2)delta[2][0]=2;
    int queue[8]={1},seen[8]={0},parent[8],symbol[8];
    int head=0,tail=1,goal=-1;
    for(int i=0;i<8;i++){parent[i]=-1;symbol[i]=-1;}
    seen[1]=1; /* product state 4*seenF2 + DFA state; starts in F1. */
    while(head<tail){
        int p=queue[head++],q=p%4,seen_f2=p/4;
        if(q==1&&seen_f2){goal=p;break;}
        for(int b=0;b<2;b++){
            int next_state=delta[q][b];
            int next=4*(seen_f2||(next_state==2))+next_state;
            if(!seen[next]){
                seen[next]=1;parent[next]=p;symbol[next]=b;queue[tail++]=next;
            }
        }
    }
    if(goal<0){puts("GENERALIZED_BUCHI_NONEMPTY=NO");return 0;}
    char cycle[9];int n=0;
    for(int p=goal;parent[p]>=0;p=parent[p])cycle[n++]=(char)('0'+symbol[p]);
    printf("GENERALIZED_BUCHI_NONEMPTY=YES PREFIX=0 CYCLE=");
    while(n)putchar(cycle[--n]);
    putchar('\n');return 0;
}
