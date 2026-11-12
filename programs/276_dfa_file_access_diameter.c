/* Program 276: Measure reachable-state access diameter and print BFS access words. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int seen[DFA_MAX]={0},distance[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX];
 int queue[DFA_MAX],h=0,t=1,diameter=0;
 for(int i=0;i<d.n;i++){parent[i]=-1;edge[i]=-1;}
 seen[d.start]=1;queue[0]=d.start;
 while(h<t){
  int q=queue[h++];
  for(int bit=0;bit<2;bit++){
   int z=d.go[q][bit];
   if(!seen[z]){
    seen[z]=1;parent[z]=q;edge[z]=bit;distance[z]=distance[q]+1;
    if(distance[z]>diameter)diameter=distance[z];
    queue[t++]=z;
   }
  }
 }
 for(int i=0;i<t;i++){
  int q=queue[i],n=0;char word[DFA_MAX+1];
  for(int p=q;parent[p]>=0;p=parent[p])word[n++]=(char)('0'+edge[p]);
  printf("q%d LENGTH=%d WORD=",q,distance[q]);
  if(!n)printf("<epsilon>");
  while(n){putchar(word[--n]);}
  putchar('\n');
 }
 printf("REACHABLE=%d ACCESS_DIAMETER=%d\n",t,diameter);return 0;
}
