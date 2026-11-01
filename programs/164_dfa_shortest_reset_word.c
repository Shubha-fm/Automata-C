/* 164: Find a shortest synchronizing word by subset BFS. ISO C11. */
#include <stdio.h>
static const int delta[3][2]={{1,0},{2,0},{2,1}};
static unsigned apply(unsigned mask,int bit){
    unsigned result=0;
    for(int q=0;q<3;q++)if(mask&(1u<<q))result|=1u<<delta[q][bit];
    return result;
}
int main(void){
    unsigned queue[8]={7},head=0,tail=1,seen[8]={0};
    int parent[8],symbol[8],goal=-1;
    for(int i=0;i<8;i++){parent[i]=-1;symbol[i]=-1;}
    seen[7]=1;
    while(head<tail){
        int m=(int)queue[head++];
        if(m&&!(m&(m-1))){goal=m;break;}
        for(int b=0;b<2;b++){
            int z=(int)apply((unsigned)m,b);
            if(!seen[z]){seen[z]=1;parent[z]=m;symbol[z]=b;queue[tail++]=(unsigned)z;}
        }
    }
    if(goal<0){puts("NOT_SYNCHRONIZING");return 0;}
    char word[8];int n=0;
    for(int s=goal;parent[s]>=0;s=parent[s])word[n++]=(char)('0'+symbol[s]);
    printf("RESET_WORD=");
    if(n==0)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');return 0;
}
