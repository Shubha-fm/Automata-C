/* Program 272: Construct the downward closure under scattered subsequence deletion. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
static DFA d;
static int closure(int mask){
 int previous;
 do{
  previous=mask;
  for(int q=0;q<d.n;q++)if(mask&(1<<q))
   for(int b=0;b<2;b++)mask|=1<<d.go[q][b];
 }while(previous!=mask);
 return mask;
}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>10){fprintf(stderr,"Subsequence closure limited to 10 input states\n");return 2;}
 int initial=closure(1<<d.start);
 int id[LIMIT],subsets[DFA_MAX],h=0,t=1;
 for(int i=0;i<LIMIT;i++)id[i]=-1;
 id[initial]=0;subsets[0]=initial;DFA out={0};
 while(h<t){
  int mask=subsets[h++],index=id[mask];
  for(int q=0;q<d.n;q++)if((mask&(1<<q))&&d.final[q])out.final[index]=1;
  for(int b=0;b<2;b++){
   int next=0;
   for(int q=0;q<d.n;q++)if(mask&(1<<q))next|=1<<d.go[q][b];
   next=closure(next);
   if(id[next]<0){
    if(t>=DFA_MAX){fprintf(stderr,"Subsequence closure exceeds 32 output states\n");return 2;}
    id[next]=t;subsets[t++]=next;
   }
   out.go[index][b]=id[next];
  }
 }
 out.n=t;out.start=0;dfa_write(&out);return 0;
}
