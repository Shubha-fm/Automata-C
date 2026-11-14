/* Program 291: Trace every visited DFA state and final acceptance. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa BINARY_WORD\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 size_t n=strlen(argv[2]);
 if(n>4096){fprintf(stderr,"Maximum word length is 4096\n");return 2;}
 for(size_t i=0;i<n;i++)if(argv[2][i]!='0'&&argv[2][i]!='1'){
  fprintf(stderr,"Binary word required\n");return 2;
 }
 int q=d.start;
 printf("STATES=q%d",q);
 for(size_t i=0;i<n;i++){
  q=d.go[q][argv[2][i]-'0'];printf("->q%d",q);
 }
 printf("\nFINAL_STATE=q%d VERDICT=%s\n",q,d.final[q]?"ACCEPT":"REJECT");
 return 0;
}
