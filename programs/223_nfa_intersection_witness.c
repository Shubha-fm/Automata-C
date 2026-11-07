/* Program 223: Shortest accepted word in the intersection of two NFAs. C11. */
#include <stdio.h>
static unsigned step(unsigned mask,int bit,int mode){
    unsigned next=0;
    if(mask&1u){next|=1u;if(bit==mode)next|=2u;}
    if((mask&2u)&&bit!=mode)next|=4u;
    if(mask&4u)next|=4u;
    return next;
}
int main(void){
    int queue[64]={9},seen[64]={0},parent[64],letter[64];
    int h=0,t=1,goal=-1;
    for(int i=0;i<64;i++){parent[i]=-1;letter[i]=-1;}
    seen[9]=1; /* 8*maskA+maskB, both start at singleton q0. */
    while(h<t){
        int state=queue[h++],a=state/8,b=state%8;
        if((a&4)&&(b&4)){goal=state;break;}
        for(int symbol=0;symbol<2;symbol++){
            int next=8*(int)step((unsigned)a,symbol,0)+
                     (int)step((unsigned)b,symbol,1);
            if(!seen[next]){
                seen[next]=1;parent[next]=state;letter[next]=symbol;queue[t++]=next;
            }
        }
    }
    if(goal<0){puts("EMPTY_INTERSECTION");return 0;}
    char word[65];int len=0;
    for(int state=goal;parent[state]>=0;state=parent[state])
        word[len++]=(char)('0'+letter[state]);
    printf("INTERSECTION_WITNESS=");
    if(!len)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');return 0;
}

