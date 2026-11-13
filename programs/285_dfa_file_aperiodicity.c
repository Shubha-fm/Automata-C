/* Program 285: Decide transition-monoid aperiodicity of a DFA with at most 5 states. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_MONOID 3125
static int seen[MAX_MONOID],queue[MAX_MONOID];
static int encode(const int *map,int n){
 int result=0;for(int q=0;q<n;q++)result=result*n+map[q];return result;
}
static void decode(int code,int n,int *map){
 for(int q=n-1;q>=0;q--){map[q]=code%n;code/=n;}
}
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>5){fprintf(stderr,"Aperiodicity limited to 5 states\n");return 2;}
 int identity[5],map[5],h=0,t=1;
 for(int q=0;q<d.n;q++)identity[q]=q;
 int initial=encode(identity,d.n);seen[initial]=1;queue[0]=initial;
 while(h<t){
  decode(queue[h++],d.n,map);
  for(int bit=0;bit<2;bit++){
   int next[5];
   for(int q=0;q<d.n;q++)next[q]=d.go[map[q]][bit];
   int key=encode(next,d.n);
   if(!seen[key]){seen[key]=1;queue[t++]=key;}
  }
 }
 int bad=0;
 for(int i=0;i<t;i++){
  int generator[5],power[5],next[5];
  decode(queue[i],d.n,generator);
  for(int q=0;q<d.n;q++)power[q]=q;
  for(int k=0;k<d.n;k++){
   for(int q=0;q<d.n;q++)next[q]=generator[power[q]];
   for(int q=0;q<d.n;q++)power[q]=next[q];
  }
  for(int q=0;q<d.n;q++)next[q]=generator[power[q]];
  if(encode(next,d.n)!=encode(power,d.n)){bad=1;break;}
 }
 printf("MONOID_SIZE=%d APERIODIC=%s\n",t,bad?"NO":"YES");
 return 0;
}
