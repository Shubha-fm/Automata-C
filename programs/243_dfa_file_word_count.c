/* Program 243: File-based accepted-word counting modulo 1,000,000,007. C11. */
#include "../include/dfa_io.h"
#define MOD 1000000007ULL
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa LENGTH\n",argv[0]);return 2;}
 DFA d;long n;
 if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(!dfa_length(argv[2],100000,&n)){fprintf(stderr,"Length must be 0..100000\n");return 2;}
 unsigned long long dp[DFA_MAX]={0};dp[d.start]=1;
 for(long i=0;i<n;i++){
  unsigned long long next[DFA_MAX]={0};
  for(int q=0;q<d.n;q++)for(int b=0;b<2;b++){
   int z=d.go[q][b];next[z]=(next[z]+dp[q])%MOD;
  }
  for(int q=0;q<d.n;q++)dp[q]=next[q];
 }
 unsigned long long total=0;
 for(int q=0;q<d.n;q++)if(d.final[q])total=(total+dp[q])%MOD;
 printf("ACCEPTED_MOD=%llu\n",total);return 0;
}
