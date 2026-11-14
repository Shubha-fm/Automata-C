/* Program 295: Find lexicographically first minimum-Hamming-distance accepted word. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 128
#define INF 1000000
static int dp[LIMIT+1][DFA_MAX];
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa BINARY_WORD\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 const char*s=argv[2];size_t n=strlen(s);
 if(n>LIMIT){fprintf(stderr,"Maximum word length is 128\n");return 2;}
 for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
  fprintf(stderr,"Binary word required\n");return 2;
 }
 for(int q=0;q<d.n;q++)dp[n][q]=d.final[q]?0:INF;
 for(size_t pos=n;pos>0;pos--){
  size_t i=pos-1;
  for(int q=0;q<d.n;q++){
   int best=INF;
   for(int bit=0;bit<2;bit++){
    int later=dp[i+1][d.go[q][bit]];
    int candidate=later==INF?INF:later+(bit!=(s[i]-'0'));
    if(candidate<best)best=candidate;
   }
   dp[i][q]=best;
  }
 }
 if(dp[0][d.start]==INF){puts("NO_ACCEPTED_WORD_OF_LENGTH");return 0;}
 char result[LIMIT+1];int q=d.start;
 for(size_t i=0;i<n;i++){
  for(int bit=0;bit<2;bit++){
   int later=dp[i+1][d.go[q][bit]];
   if(later!=INF&&later+(bit!=(s[i]-'0'))==dp[i][q]){
    result[i]=(char)('0'+bit);q=d.go[q][bit];break;
   }
  }
 }
 result[n]='\0';
 printf("HAMMING_DISTANCE=%d WORD=%s\n",dp[0][d.start],result);
 return 0;
}
