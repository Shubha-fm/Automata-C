/* Program 241: File-based DFA inclusion and shortest counterexample. C11. */
#include "../include/dfa_io.h"
#define MAXPAIRS (DFA_MAX*DFA_MAX)
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 DFA a,b;if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int seen[MAXPAIRS]={0},parent[MAXPAIRS],edge[MAXPAIRS],queue[MAXPAIRS];
 for(int i=0;i<MAXPAIRS;i++){parent[i]=-1;edge[i]=-1;}
 int start=a.start*b.n+b.start,h=0,t=1,goal=-1;
 seen[start]=1;queue[0]=start;
 while(h<t){
  int p=queue[h++],q=p/b.n,r=p%b.n;
  if(a.final[q]&&!b.final[r]){goal=p;break;}
  for(int x=0;x<2;x++){
   int z=a.go[q][x]*b.n+b.go[r][x];
   if(!seen[z]){seen[z]=1;parent[z]=p;edge[z]=x;queue[t++]=z;}
  }
 }
 if(goal<0){puts("INCLUDED");return 0;}
 char word[MAXPAIRS+1];int n=0;
 for(int p=goal;parent[p]>=0;p=parent[p])word[n++]=(char)('0'+edge[p]);
 printf("NOT_INCLUDED WITNESS=");if(!n)printf("<epsilon>");
 while(n){putchar(word[--n]);}
 putchar('\n');return 0;
}
