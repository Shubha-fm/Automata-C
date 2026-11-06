/* Program 211: Construct and validate a pumping decomposition for an infinite DFA language. ISO C11. */
#include <stdio.h>
#include <string.h>
static const int delta[3][2]={{1,0},{1,2},{2,2}};
static int path(int from,int to,int require_edge,char out[16]){
    int seen[6]={0},parent[6],edge[6],queue[6],h=0,t=1;
    for(int i=0;i<6;i++){parent[i]=-1;edge[i]=-1;}
    int start=2*from,goal=-1;queue[0]=start;seen[start]=1;
    while(h<t){
        int x=queue[h++],q=x/2,used=x%2;
        if(q==to&&(!require_edge||used)){goal=x;break;}
        for(int b=0;b<2;b++){
            int z=2*delta[q][b]+1;
            if(!seen[z]){seen[z]=1;parent[z]=x;edge[z]=b;queue[t++]=z;}
        }
    }
    if(goal<0)return -1;
    int n=0;
    for(int x=goal;parent[x]>=0;x=parent[x])out[n++]=(char)('0'+edge[x]);
    for(int i=0;i<n/2;i++){char c=out[i];out[i]=out[n-1-i];out[n-1-i]=c;}
    out[n]='\0';return n;
}
static int accepts(const char*s){
    int q=0;
    for(;*s;s++)q=delta[q][*s-'0'];
    return q==2;
}
int main(void){
    char x[16],y[16],z[16],word[80];
    int nx=path(0,1,0,x),ny=path(1,1,1,y),nz=path(1,2,0,z);
    if(nx<0||ny<1||nz<0){puts("NO_WITNESS");return 1;}
    printf("X=%s Y=%s Z=%s\n",x,y,z);
    for(int k=0;k<=3;k++){
        size_t used=0;word[0]='\0';
        const char*part=x;while(*part)word[used++]=*part++;
        for(int i=0;i<k;i++){part=y;while(*part)word[used++]=*part++;}
        part=z;while(*part)word[used++]=*part++;
        word[used]='\0';
        printf("k=%d WORD=%s %s\n",k,word,accepts(word)?"ACCEPT":"REJECT");
        if(!accepts(word))return 1;
    }
    return 0;
}
