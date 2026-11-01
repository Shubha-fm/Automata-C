/* 169: Find shortest distinguishing words for every DFA state pair. ISO C11. */
#include <stdio.h>
static const int delta[4][2]={{1,2},{1,3},{1,2},{3,3}};
static const int final[4]={0,1,0,1};
static void witness(int a,int b){
    int queue[16]={0},seen[16]={0},parent[16],edge[16],head=0,tail=1;
    for(int i=0;i<16;i++)parent[i]=-1;
    int start=4*a+b,goal=-1;queue[0]=start;seen[start]=1;
    while(head<tail){
        int p=queue[head++],x=p/4,y=p%4;
        if(final[x]!=final[y]){goal=p;break;}
        for(int bit=0;bit<2;bit++){
            int z=4*delta[x][bit]+delta[y][bit];
            if(!seen[z]){seen[z]=1;parent[z]=p;edge[z]=bit;queue[tail++]=z;}
        }
    }
    printf("q%d,q%d=",a,b);
    if(goal<0){puts("EQUIVALENT");return;}
    char word[16];int n=0;
    for(int p=goal;parent[p]>=0;p=parent[p])word[n++]=(char)('0'+edge[p]);
    if(n==0)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');
}
int main(void){for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)witness(i,j);return 0;}
