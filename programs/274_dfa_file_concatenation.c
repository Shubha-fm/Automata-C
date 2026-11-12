/* Program 274: Construct a DFA for language concatenation via an epsilon NFA. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
static DFA a,b;
static int epsilon_closure(int mask){
 int accepting_a=0;
 for(int q=0;q<a.n;q++)if((mask&(1<<q))&&a.final[q])accepting_a=1;
 if(accepting_a)mask|=1<<(a.n+b.start);
 return mask;
}
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){
  fprintf(stderr,"Invalid DFA file\n");return 2;
 }
 if(a.n+b.n>10){fprintf(stderr,"Concatenation limited to 10 combined states\n");return 2;}
 int start=epsilon_closure(1<<a.start);
 int id[LIMIT],subsets[DFA_MAX],h=0,t=1;
 for(int i=0;i<LIMIT;i++)id[i]=-1;
 id[start]=0;subsets[0]=start;DFA out={0};
 while(h<t){
  int mask=subsets[h++],index=id[mask];
  for(int q=0;q<b.n;q++)
   if((mask&(1<<(a.n+q)))&&b.final[q])out.final[index]=1;
  for(int bit=0;bit<2;bit++){
   int next=0;
   for(int q=0;q<a.n;q++)if(mask&(1<<q))next|=1<<a.go[q][bit];
   for(int q=0;q<b.n;q++)if(mask&(1<<(a.n+q)))
    next|=1<<(a.n+b.go[q][bit]);
   next=epsilon_closure(next);
   if(id[next]<0){
    if(t>=DFA_MAX){fprintf(stderr,"Concatenation exceeds 32 output states\n");return 2;}
    id[next]=t;subsets[t++]=next;
   }
   out.go[index][bit]=id[next];
  }
 }
 out.n=t;out.start=0;dfa_write(&out);return 0;
}
