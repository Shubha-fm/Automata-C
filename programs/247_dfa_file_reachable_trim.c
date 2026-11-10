/* Program 247: Remove unreachable states and renumber the DFA by BFS. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int id[DFA_MAX],queue[DFA_MAX],h=0,t=1;
 for(int q=0;q<d.n;q++)id[q]=-1;
 id[d.start]=0;queue[0]=d.start;
 while(h<t){
  int q=queue[h++];
  for(int b=0;b<2;b++){int z=d.go[q][b];
   if(id[z]<0){id[z]=t;queue[t++]=z;}
  }
 }
 DFA out={0};out.n=t;out.start=0;
 for(int i=0;i<t;i++){
  int q=queue[i];out.final[i]=d.final[q];
  for(int b=0;b<2;b++)out.go[i][b]=id[d.go[q][b]];
 }
 dfa_write(&out);return 0;
}
