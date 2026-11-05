/* Program 194: Breadth-first subset search for the shortest NFA-accepted word. ISO C11. */
#include <stdio.h>
static unsigned step(unsigned mask,int bit){
    unsigned out=0;
    if(mask&1u){out|=1u;if(bit==0)out|=2u;}
    if((mask&2u)&&bit==1)out|=4u;
    if(mask&4u)out|=4u;
    return out;
}
int main(void){
    int queue[8]={1},parent[8],symbol[8],seen[8]={0};
    for(int i=0;i<8;i++){parent[i]=-1;symbol[i]=-1;}
    seen[1]=1;int head=0,tail=1,goal=-1;
    while(head<tail){
        int mask=queue[head++];
        if(mask&4){goal=mask;break;}
        for(int bit=0;bit<2;bit++){
            int next=(int)step((unsigned)mask,bit);
            if(!seen[next]){
                seen[next]=1;parent[next]=mask;symbol[next]=bit;queue[tail++]=next;
            }
        }
    }
    if(goal<0){puts("EMPTY_LANGUAGE");return 0;}
    char word[9];int len=0;
    for(int p=goal;parent[p]>=0;p=parent[p])word[len++]=(char)('0'+symbol[p]);
    printf("SHORTEST=");
    if(!len)printf("<epsilon>");
    while(len)putchar(word[--len]);
    putchar('\n');
    return 0;
}
