/* Program 288: Construct L(A)/L(B) using backward reachability in the DFA product. ISO C11. */
#include "../include/dfa_io.h"
#define MAX_PAIR (DFA_MAX*DFA_MAX)
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 DFA a,b;
 if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){
  fprintf(stderr,"Invalid DFA file\n");return 2;
 }
 int good[MAX_PAIR]={0},changed;
 for(int q=0;q<a.n;q++)for(int r=0;r<b.n;r++)
  if(a.final[q]&&b.final[r])good[q*b.n+r]=1;
 do{
  changed=0;
  for(int q=0;q<a.n;q++)for(int r=0;r<b.n;r++){
   int pair=q*b.n+r;
   if(good[pair])continue;
   for(int bit=0;bit<2;bit++){
    int next=a.go[q][bit]*b.n+b.go[r][bit];
    if(good[next]){good[pair]=1;changed=1;break;}
   }
  }
 }while(changed);
 for(int q=0;q<a.n;q++)a.final[q]=good[q*b.n+b.start];
 dfa_write(&a);return 0;
}
