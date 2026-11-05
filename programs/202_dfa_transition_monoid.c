/* Program 202: Enumerate the finite transition monoid of a sample DFA. ISO C11. */
#include <stdio.h>
#define MAX 27
static const int delta[3][2]={{1,0},{1,2},{1,0}};
static int encode(const int map[3]){
    return map[0]*9+map[1]*3+map[2];
}
int main(void){
    int known[MAX]={0},queue[MAX],head=0,tail=1;
    int id[3]={0,1,2};
    int start=encode(id);
    known[start]=1;queue[0]=start;
    while(head<tail){
        int value=queue[head++],map[3]={value/9,(value/3)%3,value%3};
        for(int b=0;b<2;b++){
            int transformed[3];
            for(int q=0;q<3;q++)transformed[q]=delta[map[q]][b];
            int next=encode(transformed);
            if(!known[next]){known[next]=1;queue[tail++]=next;}
        }
    }
    printf("MONOID_SIZE=%d\n",tail);
    for(int i=0;i<tail;i++){
        int v=queue[i];
        printf("TRANSFORM %d: %d,%d,%d\n",i,v/9,(v/3)%3,v%3);
    }
    return 0;
}
