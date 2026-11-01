/* Program 158: Find the shortest distinguishing word for two Mealy machines. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


static const int next_a[2][2]={{0,1},{0,1}};
static const int next_b[2][2]={{0,1},{0,1}};
static const int out_a[2][2]={{0,1},{0,1}};
static const int out_b[2][2]={{0,1},{0,0}};
int main(void){
    int seen[4]={1,0,0,0},parent[4]={-1,-1,-1,-1},q[4]={0};
    char symbol[4]={0},word[6];
    int h=0,t=1,goal=-1,bad=-1;
    while(h<t&&goal<0){
        int p=q[h++],a=p/2,b=p%2;
        for(int bit=0;bit<2;bit++){
            if(out_a[a][bit]!=out_b[b][bit]){goal=p;bad=bit;break;}
            int np=2*next_a[a][bit]+next_b[b][bit];
            if(!seen[np]){
                seen[np]=1;q[t++]=np;parent[np]=p;symbol[np]=(char)('0'+bit);
            }
        }
    }
    if(goal<0){puts("EQUIVALENT");return 0;}
    int n=0;word[n++]=(char)('0'+bad);
    for(int p=goal;parent[p]>=0;p=parent[p])word[n++]=symbol[p];
    printf("WITNESS=");
    while(n)putchar(word[--n]);
    putchar('\n');
    return 0;
}
