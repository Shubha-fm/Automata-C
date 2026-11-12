/* Program 273: Construct the upward closure under inserting arbitrary input symbols. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>10){fprintf(stderr,"Supersequence closure limited to 10 input states\n");return 2;}
 int initial=1<<d.start,id[LIMIT],subsets[DFA_MAX],h=0,t=1;
 for(int i=0;i<LIMIT;i++)id[i]=-1;
 id[initial]=0;subsets[0]=initial;DFA out={0};
 while(h<t){
  int mask=subsets[h++],index=id[mask];
  for(int q=0;q<d.n;q++)if((mask&(1<<q))&&d.final[q])out.final[index]=1;
  for(int b=0;b<2;b++){
   int next=mask;
   for(int q=0;q<d.n;q++)if(mask&(1<<q))next|=1<<d.go[q][b];
   if(id[next]<0){
    if(t>=DFA_MAX){fprintf(stderr,"Supersequence closure exceeds 32 output states\n");return 2;}
    id[next]=t;subsets[t++]=next;
   }
   out.go[index][b]=id[next];
  }
 }
 out.n=t;out.start=0;dfa_write(&out);return 0;
}
