/* Program 294: Compute exact edit distance from a word to a regular language. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_LEN 40
#define VERTICES ((MAX_LEN+1)*DFA_MAX)
#define INF 1000000
static int distance[VERTICES],used[VERTICES];
static void relax(int from,int to,int cost){
 if(distance[from]+cost<distance[to])distance[to]=distance[from]+cost;
}
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa BINARY_WORD\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 const char*s=argv[2];size_t n=strlen(s);
 if(n>MAX_LEN){fprintf(stderr,"Maximum word length is 40\n");return 2;}
 for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
  fprintf(stderr,"Binary word required\n");return 2;
 }
 int nodes=((int)n+1)*d.n;
 for(int i=0;i<nodes;i++)distance[i]=INF;
 distance[d.start]=0;
 for(int iteration=0;iteration<nodes;iteration++){
  int p=-1;
  for(int i=0;i<nodes;i++)if(!used[i]&&(p<0||distance[i]<distance[p]))p=i;
  if(p<0||distance[p]==INF)break;
  used[p]=1;
  int pos=p/d.n,q=p%d.n;
  if(pos<(int)n){
   relax(p,(pos+1)*d.n+q,1); /* delete next input symbol */
   for(int bit=0;bit<2;bit++)
    relax(p,(pos+1)*d.n+d.go[q][bit],bit!=(s[pos]-'0'));
  }
  for(int bit=0;bit<2;bit++)
   relax(p,pos*d.n+d.go[q][bit],1); /* insert automaton symbol */
 }
 int best=INF;
 for(int q=0;q<d.n;q++)if(d.final[q]){
  int candidate=distance[(int)n*d.n+q];
  if(candidate<best)best=candidate;
 }
 if(best==INF){puts("EMPTY_LANGUAGE");return 0;}
 printf("EDIT_DISTANCE=%d\n",best);return 0;
}
