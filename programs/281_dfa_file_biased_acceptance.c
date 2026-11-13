/* Program 281: Acceptance probability after N independent biased input symbols. ISO C11. */
#include "../include/dfa_io.h"
#include <math.h>
int main(int argc,char **argv){
 if(argc!=4){fprintf(stderr,"Usage: %s MODEL.dfa LENGTH PROBABILITY_OF_ONE\n",argv[0]);return 2;}
 DFA d;long length;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(!dfa_length(argv[2],100000,&length)){fprintf(stderr,"Length must be 0..100000\n");return 2;}
 errno=0;char *end=NULL;double p=strtod(argv[3],&end);
 if(errno==ERANGE||end==argv[3]||*end||!isfinite(p)||p<0||p>1){
  fprintf(stderr,"Probability must be within [0,1]\n");return 2;
 }
 double states[DFA_MAX]={0};states[d.start]=1;
 for(long k=0;k<length;k++){
  double next[DFA_MAX]={0};
  for(int q=0;q<d.n;q++){
   next[d.go[q][0]]+=states[q]*(1-p);
   next[d.go[q][1]]+=states[q]*p;
  }
  for(int q=0;q<d.n;q++)states[q]=next[q];
 }
 double accepted=0;
 for(int q=0;q<d.n;q++)if(d.final[q])accepted+=states[q];
 printf("P_ACCEPT=%.9f\n",accepted);return 0;
}
