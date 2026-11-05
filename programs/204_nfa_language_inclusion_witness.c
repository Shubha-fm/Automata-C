/* Program 204: Exact NFA language inclusion against a DFA using a product-state BFS. ISO C11. */
#include <stdio.h>
/* NFA: contains 01; DFA: contains 00. We search for NFA \ DFA. */
static unsigned nfa_step(unsigned mask,int bit){
    unsigned next=0;
    if(mask&1u){next|=1u;if(bit==0)next|=2u;}
    if((mask&2u)&&bit==1)next|=4u;
    if(mask&4u)next|=4u;
    return next;
}
static const int dfa[3][2]={{1,0},{2,0},{2,2}};
int main(void){
    int queue[24]={3},seen[24]={0},parent[24],edge[24];
    for(int i=0;i<24;i++){parent[i]=-1;edge[i]=-1;}
    int head=0,tail=1,goal=-1;seen[3]=1;
    while(head<tail){
        int state=queue[head++],mask=state/3,q=state%3;
        if((mask&4)&&q!=2){goal=state;break;}
        for(int bit=0;bit<2;bit++){
            int next=3*(int)nfa_step((unsigned)mask,bit)+dfa[q][bit];
            if(!seen[next]){seen[next]=1;parent[next]=state;edge[next]=bit;queue[tail++]=next;}
        }
    }
    if(goal<0){puts("INCLUDED");return 0;}
    char word[25];int len=0;
    for(int s=goal;parent[s]>=0;s=parent[s])
        word[len++]=(char)('0'+edge[s]);
    printf("NOT_INCLUDED WITNESS=");
    if(len==0)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');return 0;
}
