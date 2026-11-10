/* Program 249: Generate shortest distinguishing words for every DFA state pair. C11. */
#include "../include/dfa_io.h"
#define PAIRS (DFA_MAX*DFA_MAX)
static DFA d;
static void witness(int a,int b){
 int seen[PAIRS]={0},parent[PAIRS],edge[PAIRS],queue[PAIRS];
 for(int i=0;i<d.n*d.n;i++){parent[i]=-1;edge[i]=-1;}
 int start=a*d.n+b,h=0,t=1,goal=-1;
 queue[0]=start;seen[start]=1;
 while(h<t){
  int p=queue[h++],q=p/d.n,r=p%d.n;
  if(d.final[q]!=d.final[r]){goal=p;break;}
  for(int x=0;x<2;x++){
   int z=d.go[q][x]*d.n+d.go[r][x];
   if(!seen[z]){seen[z]=1;parent[z]=p;edge[z]=x;queue[t++]=z;}
  }
 }
 printf("q%d,q%d=",a,b);
 if(goal<0){puts("EQUIVALENT");return;}
 char word[PAIRS+1];int n=0;
 for(int p=goal;parent[p]>=0;p=parent[p])word[n++]=(char)('0'+edge[p]);
 if(!n)printf("<epsilon>");
 while(n)putchar(word[--n]);putchar('\n');
}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 for(int q=0;q<d.n;q++)for(int r=q+1;r<d.n;r++)witness(q,r);
 return 0;
}
