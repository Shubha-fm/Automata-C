/* Program 282: Probability of reaching an accepting state within N steps. ISO C11. */
#include "../include/dfa_io.h"
#include <math.h>
int main(int argc,char **argv){
 if(argc!=4){fprintf(stderr,"Usage: %s MODEL.dfa STEPS PROBABILITY_OF_ONE\n",argv[0]);return 2;}
 DFA d;long length;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(!dfa_length(argv[2],100000,&length)){fprintf(stderr,"Steps must be 0..100000\n");return 2;}
 errno=0;char *end=NULL;double p=strtod(argv[3],&end);
 if(errno==ERANGE||end==argv[3]||*end||!isfinite(p)||p<0||p>1){
  fprintf(stderr,"Probability must be within [0,1]\n");return 2;
 }
 double active[DFA_MAX]={0};active[d.start]=1;
 double hit=0;
 for(long step=0;step<=length;step++){
  double next[DFA_MAX]={0};
  for(int q=0;q<d.n;q++){
   if(d.final[q])hit+=active[q];
   else if(step<length){
    next[d.go[q][0]]+=active[q]*(1-p);
    next[d.go[q][1]]+=active[q]*p;
   }
  }
  for(int q=0;q<d.n;q++)active[q]=next[q];
 }
 printf("P_HIT=%.9f\n",hit);return 0;
}
