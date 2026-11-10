/* Program 244: Reachable DFA SCC and accepting-cycle audit using Tarjan. C11. */
#include "../include/dfa_io.h"
static DFA d;static int reach[DFA_MAX],idx[DFA_MAX],low[DFA_MAX],stack[DFA_MAX],active[DFA_MAX];
static int stamp=0,top=0,scc=0,cyclic=0,accepting=0;
static void mark(int q){
 reach[q]=1;
 for(int b=0;b<2;b++){int z=d.go[q][b];if(!reach[z])mark(z);}
}
static void visit(int q){
 idx[q]=low[q]=++stamp;stack[top++]=q;active[q]=1;
 for(int b=0;b<2;b++){
  int z=d.go[q][b];if(!reach[z])continue;
  if(!idx[z]){visit(z);if(low[z]<low[q])low[q]=low[z];}
  else if(active[z]&&idx[z]<low[q])low[q]=idx[z];
 }
 if(low[q]==idx[q]){
  int count=0,hasfinal=0,z;
  do{z=stack[--top];active[z]=0;count++;hasfinal|=d.final[z];}while(z!=q);
  int hascycle=count>1;
  if(!hascycle)for(int b=0;b<2;b++)if(d.go[q][b]==q)hascycle=1;
  scc++;cyclic+=hascycle;accepting+=(hascycle&&hasfinal);
 }
}
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 mark(d.start);
 for(int q=0;q<d.n;q++)if(reach[q]&&!idx[q])visit(q);
 int states=0;for(int q=0;q<d.n;q++)states+=reach[q];
 printf("REACHABLE=%d SCCS=%d CYCLIC=%d ACCEPTING_CYCLIC=%d\n",
 states,scc,cyclic,accepting);return 0;
}
