/* Program 155: Decide language finiteness by finding productive cycles. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* A productive state is reachable from the start and can reach a final state. */
static int cycle(int state,int n,const int tr[][2],const int useful[],
                 int color[]) {
    color[state]=1;
    for(int b=0;b<2;b++){
        int z=tr[state][b];
        if(z<0||z>=n||!useful[z])continue;
        if(color[z]==1) return 1;
        if(color[z]==0 && cycle(z,n,tr,useful,color))return 1;
    }
    color[state]=2;
    return 0;
}
static int is_infinite(int n,const int tr[][2],const int final[]){
    int reach[8]={0},back[8]={0},useful[8]={0},color[8]={0};
    int queue[8]={0},h=0,t=1,changed;
    reach[0]=1;
    while(h<t){
        int s=queue[h++];
        for(int b=0;b<2;b++){
            int z=tr[s][b];
            if(!reach[z]){reach[z]=1;queue[t++]=z;}
        }
    }
    for(int s=0;s<n;s++)back[s]=final[s];
    do {
        changed=0;
        for(int s=0;s<n;s++)
            for(int b=0;b<2;b++)
                if(back[tr[s][b]]&&!back[s]){back[s]=1;changed=1;}
    } while(changed);
    for(int s=0;s<n;s++)useful[s]=reach[s]&&back[s];
    return useful[0] && cycle(0,n,tr,useful,color);
}
int main(void){
    const int finite[3][2]={{1,2},{2,2},{2,2}};
    const int f1[3]={0,1,0};
    const int infinite[2][2]={{0,1},{1,1}};
    const int f2[2]={0,1};
    printf("FINITE_EXAMPLE=%s\n",is_infinite(3,finite,f1)?"INFINITE":"FINITE");
    printf("INFINITE_EXAMPLE=%s\n",is_infinite(2,infinite,f2)?"INFINITE":"FINITE");
    return 0;
}
