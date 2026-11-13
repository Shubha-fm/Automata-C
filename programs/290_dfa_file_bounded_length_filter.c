/* Program 290: Intersect a DFA with words of length at most K, or exactly K. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv){
 if(argc<3||argc>4||(argc==4&&strcmp(argv[3],"exact")!=0)){
  fprintf(stderr,"Usage: %s MODEL.dfa K [exact]\n",argv[0]);return 2;
 }
 DFA d;long length;
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(!dfa_length(argv[2],30,&length)){
  fprintf(stderr,"K must be 0..30\n");return 2;
 }
 if(d.n*(length+2)>DFA_MAX){
  fprintf(stderr,"Bounded product exceeds 32 states\n");return 2;
 }
 int exact=argc==4;
 DFA out={0};out.n=d.n*((int)length+2);
 out.start=d.start;
 for(int k=0;k<=length+1;k++)for(int q=0;q<d.n;q++){
  int state=k*d.n+q;
  out.final[state]=(k<=length)&&(!exact||k==length)&&d.final[q];
  int next_k=k<(int)length+1?k+1:k;
  for(int bit=0;bit<2;bit++)
   out.go[state][bit]=next_k*d.n+d.go[q][bit];
 }
 dfa_write(&out);return 0;
}
