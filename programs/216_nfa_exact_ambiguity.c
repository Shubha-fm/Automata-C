/* Program 216: Check NFA ambiguity exactly via a product of two independent runs. ISO C11. */
#include <stdio.h>
#include <string.h>
/* The optional variant has only the transition q0 --0--> q1.
   The default also has q0 --0--> q2, creating two accepting runs. */
static int options(int q,int bit,int out[2],int variant){
    if(q!=0||bit!=0)return 0;
    out[0]=1;
    if(!variant){out[1]=2;return 2;}
    return 1;
}
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"unambiguous"))){
        fprintf(stderr,"Usage: %s [unambiguous]\n",argv[0]);return 2;
    }
    int variant=argc==2,queue[18]={0},seen[18]={0};
    int parent[18],symbol[18];
    for(int i=0;i<18;i++){parent[i]=-1;symbol[i]=-1;}
    int head=0,tail=1,goal=-1;seen[0]=1;
    while(head<tail){
        int p=queue[head++],q1=p/6,q2=(p/2)%3,diff=p%2;
        if(diff&&q1!=0&&q2!=0){goal=p;break;}
        for(int bit=0;bit<2;bit++){
            int out1[2],out2[2],n1=options(q1,bit,out1,variant);
            int n2=options(q2,bit,out2,variant);
            for(int i=0;i<n1;i++)for(int j=0;j<n2;j++){
                int diverged=diff||(out1[i]!=out2[j]);
                int next=6*out1[i]+2*out2[j]+diverged;
                if(!seen[next]){
                    seen[next]=1;parent[next]=p;symbol[next]=bit;
                    queue[tail++]=next;
                }
            }
        }
    }
    if(goal<0){puts("UNAMBIGUOUS");return 0;}
    char word[19];int n=0;
    for(int p=goal;parent[p]>=0;p=parent[p])
        word[n++]=(char)('0'+symbol[p]);
    printf("AMBIGUOUS_WORD=");
    if(!n)printf("<epsilon>");
    while(n)putchar(word[--n]);
    putchar('\n');return 0;
}
