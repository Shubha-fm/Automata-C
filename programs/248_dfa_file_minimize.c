/* Program 248: Minimize a file-based DFA using partition refinement. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int reachable[DFA_MAX]={0},queue[DFA_MAX],h=0,t=1;
 reachable[d.start]=1;queue[0]=d.start;
 while(h<t){int q=queue[h++];
  for(int b=0;b<2;b++){int z=d.go[q][b];
   if(!reachable[z]){reachable[z]=1;queue[t++]=z;}
  }
 }
 int classid[DFA_MAX],next[DFA_MAX],representative[DFA_MAX];
 for(int q=0;q<d.n;q++)classid[q]=d.final[q];
 for(int round=0;round<2*d.n+2;round++){
  int count=0;
  for(int q=0;q<d.n;q++)if(reachable[q]){
   int k=0;
   for(;k<count;k++){
    int r=representative[k];
    if(classid[q]==classid[r]&&
     classid[d.go[q][0]]==classid[d.go[r][0]]&&
     classid[d.go[q][1]]==classid[d.go[r][1]])break;
   }
   if(k==count)representative[count++]=q;
   next[q]=k;
  }
  int changed=0;
  for(int q=0;q<d.n;q++)if(reachable[q]&&classid[q]!=next[q])changed=1;
  for(int q=0;q<d.n;q++)if(reachable[q])classid[q]=next[q];
  if(!changed)break;
 }
 int repr[DFA_MAX],classes=0;
 for(int q=0;q<d.n;q++)if(reachable[q]){
  int seen=0;
  for(int k=0;k<classes;k++)if(classid[repr[k]]==classid[q])seen=1;
  if(!seen)repr[classes++]=q;
 }
 int map[DFA_MAX];for(int i=0;i<DFA_MAX;i++)map[i]=-1;
 for(int i=0;i<classes;i++)map[classid[repr[i]]]=i;
 DFA out={0};out.n=classes;out.start=map[classid[d.start]];
 for(int i=0;i<classes;i++){
  int q=repr[i];out.final[i]=d.final[q];
  for(int b=0;b<2;b++)out.go[i][b]=map[classid[d.go[q][b]]];
 }
 dfa_write(&out);return 0;
}
