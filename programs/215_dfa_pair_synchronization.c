/* Program 215: Check pair mergeability as a synchronizing-DFA criterion. ISO C11. */
#include <stdio.h>
#include <string.h>
static int delta[4][2];
static int shortest_merge(int a,int b,char word[17]){
    int seen[16]={0},queue[16],parent[16],symbol[16];
    for(int k=0;k<16;k++){parent[k]=-1;symbol[k]=-1;}
    int start=4*a+b,head=0,tail=1,goal=-1;
    seen[start]=1;queue[0]=start;
    while(head<tail){
        int p=queue[head++],x=p/4,y=p%4;
        if(x==y){goal=p;break;}
        for(int bit=0;bit<2;bit++){
            int next=4*delta[x][bit]+delta[y][bit];
            if(!seen[next]){
                seen[next]=1;parent[next]=p;symbol[next]=bit;queue[tail++]=next;
            }
        }
    }
    if(goal<0)return -1;
    int n=0;
    for(int p=goal;parent[p]>=0;p=parent[p])word[n++]=(char)('0'+symbol[p]);
    for(int i=0;i<n/2;i++){
        char ch=word[i];word[i]=word[n-1-i];word[n-1-i]=ch;
    }
    word[n]='\0';return n;
}
int main(int argc,char**argv){
    if(argc>2||(argc==2&&strcmp(argv[1],"permutation"))){
        fprintf(stderr,"Usage: %s [permutation]\n",argv[0]);return 2;
    }
    int permutation=argc==2;
    for(int q=0;q<4;q++){
        delta[q][0]=permutation?(q+1)%4:(q==0?0:q-1);
        delta[q][1]=permutation?(q^1):(q+1)%4;
    }
    int mergeable=0;
    for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){
        char word[17];int n=shortest_merge(a,b,word);
        printf("PAIR(q%d,q%d)=%s\n",a,b,n<0?"NO_MERGE":word);
        if(n>=0)mergeable++;
    }
    printf("MERGEABLE_PAIRS=%d/6 SYNCHRONIZING=%s\n",
           mergeable,mergeable==6?"YES":"NO");
    return 0;
}
