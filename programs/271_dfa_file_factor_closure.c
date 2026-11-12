/* Program 271: Construct the set of all contiguous substrings of accepted words. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>10){fprintf(stderr,"Factor closure limited to 10 input states\n");return 2;}
 int reach[DFA_MAX]={0},productive[DFA_MAX]={0},queue[DFA_MAX],h=0,t=1;
 reach[d.start]=1;queue[0]=d.start;
 while(h<t){int q=queue[h++];for(int b=0;b<2;b++){
  int z=d.go[q][b];if(!reach[z]){reach[z]=1;queue[t++]=z;}
 }}
 for(int q=0;q<d.n;q++)productive[q]=d.final[q];
 int changed;
 do{changed=0;for(int q=0;q<d.n;q++)for(int b=0;b<2;b++){
  if(productive[d.go[q][b]]&&!productive[q]){productive[q]=1;changed=1;}
 }}while(changed);
 int start=0;for(int q=0;q<d.n;q++)if(reach[q])start|=1<<q;
 int id[LIMIT],subsets[DFA_MAX],head=0,tail=1;
 for(int i=0;i<LIMIT;i++)id[i]=-1;
 id[start]=0;subsets[0]=start;DFA out={0};
 while(head<tail){
  int mask=subsets[head++],index=id[mask];
  for(int q=0;q<d.n;q++)if((mask&(1<<q))&&productive[q])out.final[index]=1;
  for(int b=0;b<2;b++){
   int next=0;for(int q=0;q<d.n;q++)if(mask&(1<<q))next|=1<<d.go[q][b];
   if(id[next]<0){
    if(tail>=DFA_MAX){fprintf(stderr,"Factor closure exceeds 32 output states\n");return 2;}
    id[next]=tail;subsets[tail++]=next;
   }
   out.go[index][b]=id[next];
  }
 }
 out.n=tail;out.start=0;dfa_write(&out);return 0;
}
