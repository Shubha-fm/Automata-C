/* Program 242: File-based shortest accepted word via breadth-first search. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int seen[DFA_MAX]={0},parent[DFA_MAX],edge[DFA_MAX],queue[DFA_MAX];
 for(int i=0;i<d.n;i++){parent[i]=-1;edge[i]=-1;}
 int h=0,t=1,goal=-1;queue[0]=d.start;seen[d.start]=1;
 while(h<t){
  int q=queue[h++];if(d.final[q]){goal=q;break;}
  for(int b=0;b<2;b++){int z=d.go[q][b];if(!seen[z]){
   seen[z]=1;parent[z]=q;edge[z]=b;queue[t++]=z;
  }}
 }
 if(goal<0){puts("EMPTY_LANGUAGE");return 0;}
 char word[DFA_MAX+1];int n=0;
 for(int q=goal;parent[q]>=0;q=parent[q])word[n++]=(char)('0'+edge[q]);
 printf("SHORTEST=");if(!n)printf("<epsilon>");
 while(n){putchar(word[--n]);}
 putchar('\n');return 0;
}
