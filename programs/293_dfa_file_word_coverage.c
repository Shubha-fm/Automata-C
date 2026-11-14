/* Program 293: Count states and transitions visited by a DFA execution. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa BINARY_WORD\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 size_t n=strlen(argv[2]);
 if(n>4096){fprintf(stderr,"Maximum word length is 4096\n");return 2;}
 int q=d.start,states[DFA_MAX]={0},edges[DFA_MAX][2]={{0}};
 states[q]=1;
 for(size_t i=0;i<n;i++){
  char ch=argv[2][i];
  if(ch!='0'&&ch!='1'){fprintf(stderr,"Binary word required\n");return 2;}
  int bit=ch-'0';
  edges[q][bit]=1;q=d.go[q][bit];states[q]=1;
 }
 int visited=0,covered=0;
 for(int i=0;i<d.n;i++){
  visited+=states[i];
  for(int bit=0;bit<2;bit++)covered+=edges[i][bit];
 }
 printf("VISITED_STATES=%d/%d COVERED_TRANSITIONS=%d/%d FINAL_STATE=q%d VERDICT=%s\n",
  visited,d.n,covered,2*d.n,q,d.final[q]?"ACCEPT":"REJECT");
 return 0;
}
