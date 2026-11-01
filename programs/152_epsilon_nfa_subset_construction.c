/* Program 152: Reachable DFA subsets from an epsilon-NFA. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* Four-state epsilon-NFA; subset states are bit masks. */
static unsigned epsilon_closure(unsigned s) {
    if(s & 1u) s |= 2u;
    return s;
}
static unsigned move(unsigned s,int bit) {
    unsigned next=0;
    if(s&2u) { next|=2u; if(bit==0)next|=4u; }
    if((s&4u) && bit==1) next|=8u;
    if(s&8u) next|=8u;
    return epsilon_closure(next);
}
int main(void) {
    unsigned seen[16]={0}, queue[16], head=0, tail=0;
    unsigned start=epsilon_closure(1u);
    seen[start]=1u; queue[tail++]=start;
    while(head<tail) {
        unsigned s=queue[head++];
        unsigned on0=move(s,0), on1=move(s,1);
        printf("subset=%u on0=%u on1=%u accepting=%d\n",
               s,on0,on1,(s&8u)!=0);
        if(!seen[on0]) {seen[on0]=1u;queue[tail++]=on0;}
        if(!seen[on1]) {seen[on1]=1u;queue[tail++]=on1;}
    }
    printf("DFA_STATES=%u\n",tail);
    return 0;
}
