/* Program 280: Sample accepted fixed-length binary words uniformly with a deterministic seed. ISO C11. */
#include "../include/dfa_io.h"
#include <stdint.h>
#define LENGTH_MAX 50
static uint64_t ways[LENGTH_MAX+1][DFA_MAX],rng;
static uint64_t random64(void){
 rng^=rng>>12;rng^=rng<<25;rng^=rng>>27;
 return rng*UINT64_C(2685821657736338717);
}
static uint64_t below(uint64_t bound){
 uint64_t threshold=(UINT64_C(0)-bound)%bound;
 uint64_t r;
 do{r=random64();}while(r<threshold);
 return r%bound;
}
int main(int argc,char**argv){
 if(argc!=4){fprintf(stderr,"Usage: %s MODEL.dfa LENGTH_0_TO_50 SEED\n",argv[0]);return 2;}
 DFA d;long length;
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(!dfa_length(argv[2],LENGTH_MAX,&length)){
  fprintf(stderr,"Length must be 0..50\n");return 2;
 }
 if(!*argv[3]||*argv[3]=='-'){
  fprintf(stderr,"Invalid seed\n");return 2;
 }
 errno=0;char*end=NULL;
 unsigned long long seed=strtoull(argv[3],&end,10);
 if(errno==ERANGE||end==argv[3]||*end){
  fprintf(stderr,"Invalid seed\n");return 2;
 }
 rng=(uint64_t)seed;
 if(!rng)rng=UINT64_C(0x9e3779b97f4a7c15);
 for(int q=0;q<d.n;q++)ways[0][q]=(uint64_t)d.final[q];
 for(int k=1;k<=length;k++)for(int q=0;q<d.n;q++)
  ways[k][q]=ways[k-1][d.go[q][0]]+ways[k-1][d.go[q][1]];
 uint64_t total=ways[length][d.start];
 if(!total){puts("NO_ACCEPTED_WORDS");return 0;}
 char word[LENGTH_MAX+1];int q=d.start;
 for(int k=0;k<length;k++){
  uint64_t left=ways[length-k-1][d.go[q][0]];
  uint64_t right=ways[length-k-1][d.go[q][1]];
  uint64_t choice=below(left+right);
  int bit=choice>=left;word[k]=(char)('0'+bit);q=d.go[q][bit];
 }
 word[length]='\0';
 printf("WORD=%s TOTAL=%llu SEED=%llu\n",
  word,(unsigned long long)total,seed);
 return 0;
}
