/* Program 286: Check isomorphism of the reachable rooted parts of two DFAs. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv){
 if(argc!=3){fprintf(stderr,"Usage: %s A.dfa B.dfa\n",argv[0]);return 2;}
 DFA a,b;
 if(!dfa_read(argv[1],&a)||!dfa_read(argv[2],&b)){
  fprintf(stderr,"Invalid DFA file\n");return 2;
 }
 int ab[DFA_MAX],ba[DFA_MAX],queue[DFA_MAX],h=0,t=1;
 for(int q=0;q<DFA_MAX;q++){ab[q]=-1;ba[q]=-1;}
 ab[a.start]=b.start;ba[b.start]=a.start;queue[0]=a.start;
 while(h<t){
  int x=queue[h++],y=ab[x];
  if(a.final[x]!=b.final[y]){puts("NOT_ISOMORPHIC");return 0;}
  for(int bit=0;bit<2;bit++){
   int nx=a.go[x][bit],ny=b.go[y][bit];
   if(ab[nx]<0&&ba[ny]<0){
    ab[nx]=ny;ba[ny]=nx;queue[t++]=nx;
   }else if(ab[nx]!=ny||ba[ny]!=nx){
    puts("NOT_ISOMORPHIC");return 0;
   }
  }
 }
 printf("ISOMORPHIC REACHABLE_STATES=%d\n",t);return 0;
}
