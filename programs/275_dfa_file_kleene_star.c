/* Program 275: Construct a DFA for Kleene star using epsilon transitions. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
static DFA d;
static int close_mask(int mask){
 for(int q=0;q<d.n;q++)if((mask&(1<<q))&&d.final[q]){
  mask|=1<<d.start;break;
 }
 return mask;
}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>9){fprintf(stderr,"Kleene star limited to 9 input states\n");return 2;}
 int initial=(1<<d.n)|(1<<d.start);
 int id[LIMIT],subsets[DFA_MAX],h=0,t=1;
 for(int i=0;i<LIMIT;i++)id[i]=-1;
 id[initial]=0;subsets[0]=initial;DFA out={0};
 while(h<t){
  int mask=subsets[h++],index=id[mask];
  if(mask&(1<<d.n))out.final[index]=1;
  for(int q=0;q<d.n;q++)if((mask&(1<<q))&&d.final[q])out.final[index]=1;
  for(int bit=0;bit<2;bit++){
   int next=0;
   for(int q=0;q<d.n;q++)if(mask&(1<<q))next|=1<<d.go[q][bit];
   next=close_mask(next);
   if(id[next]<0){
    if(t>=DFA_MAX){fprintf(stderr,"Kleene star exceeds 32 output states\n");return 2;}
    id[next]=t;subsets[t++]=next;
   }
   out.go[index][bit]=id[next];
  }
 }
 out.n=t;out.start=0;dfa_write(&out);return 0;
}
