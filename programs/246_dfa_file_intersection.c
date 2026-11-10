/* Program 246: Emit the product DFA for the intersection of two languages. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 DFA a,b;if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){
  fprintf(stderr,"Invalid DFA file\n");return 2;
 }
 if(a.n*b.n>DFA_MAX){fprintf(stderr,"Product exceeds 32 states\n");return 2;}
 DFA d={0};d.n=a.n*b.n;d.start=a.start*b.n+b.start;
 for(int q=0;q<a.n;q++)for(int r=0;r<b.n;r++){
  int p=q*b.n+r;d.final[p]=a.final[q]&&b.final[r];
  for(int x=0;x<2;x++)d.go[p][x]=a.go[q][x]*b.n+b.go[r][x];
 }
 dfa_write(&d);return 0;
}
