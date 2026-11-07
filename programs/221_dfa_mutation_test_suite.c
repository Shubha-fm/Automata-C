/* Program 221: Generate shortest test words that distinguish reference and mutated DFAs. C11. */
#include <stdio.h>
static const int ref[3][2]={{1,0},{1,2},{1,0}};
static int mutant_next(int m,int q,int b){
    if(m==2 && q==1 && b==1)return 0;
    return ref[q][b];
}
static int final_state(int m,int q){
    if(m==1)return q==1;
    if(m==3)return q==0||q==2;
    return q==2;
}
static void witness(int mutant){
    int queue[9]={0},seen[9]={1},parent[9],letter[9],h=0,t=1,goal=-1;
    for(int i=0;i<9;i++){parent[i]=-1;letter[i]=-1;}
    while(h<t){
        int p=queue[h++],a=p/3,b=p%3;
        if((a==2)!=final_state(mutant,b)){goal=p;break;}
        for(int x=0;x<2;x++){
            int next=3*ref[a][x]+mutant_next(mutant,b,x);
            if(!seen[next]){
                seen[next]=1;parent[next]=p;letter[next]=x;queue[t++]=next;
            }
        }
    }
    printf("MUTANT_%d=",mutant);
    if(goal<0){puts("EQUIVALENT");return;}
    char word[10];int n=0;
    for(int q=goal;parent[q]>=0;q=parent[q])word[n++]=(char)('0'+letter[q]);
    if(!n)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');
}
int main(void){for(int m=1;m<=3;m++)witness(m);return 0;}

