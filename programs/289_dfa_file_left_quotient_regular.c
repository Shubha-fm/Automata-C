/* Program 289: Construct L(B)^(-1)L(A) using product reachability and subset determinization. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_PAIR (DFA_MAX*DFA_MAX)
#define MAX_SUBSETS 1024
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 DFA a,b;
 if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){
  fprintf(stderr,"Invalid DFA file\n");return 2;
 }
 if(a.n>10){fprintf(stderr,"Left quotient limited to 10 states in A\n");return 2;}
 int seen[MAX_PAIR]={0},queue_pairs[MAX_PAIR],h=0,t=1;
 int initial_pair=a.start*b.n+b.start;
 queue_pairs[0]=initial_pair;seen[initial_pair]=1;
 int initial_mask=0;
 while(h<t){
  int pair=queue_pairs[h++],q=pair/b.n,r=pair%b.n;
  if(b.final[r])initial_mask|=1<<q;
  for(int bit=0;bit<2;bit++){
   int next=a.go[q][bit]*b.n+b.go[r][bit];
   if(!seen[next]){seen[next]=1;queue_pairs[t++]=next;}
  }
 }
 int ids[MAX_SUBSETS],subsets[DFA_MAX],head=0,tail=1;
 for(int i=0;i<MAX_SUBSETS;i++)ids[i]=-1;
 ids[initial_mask]=0;subsets[0]=initial_mask;
 DFA out={0};
 while(head<tail){
  int mask=subsets[head++],index=ids[mask];
  for(int q=0;q<a.n;q++)if((mask&(1<<q))&&a.final[q])out.final[index]=1;
  for(int bit=0;bit<2;bit++){
   int next=0;
   for(int q=0;q<a.n;q++)if(mask&(1<<q))next|=1<<a.go[q][bit];
   if(ids[next]<0){
    if(tail>=DFA_MAX){
     fprintf(stderr,"Left quotient exceeds 32 output states\n");return 2;
    }
    ids[next]=tail;subsets[tail++]=next;
   }
   out.go[index][bit]=ids[next];
  }
 }
 out.n=tail;out.start=0;dfa_write(&out);return 0;
}
