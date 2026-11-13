/* Program 287: Swap binary input symbols 0 and 1 in a DFA's transition table. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 for(int q=0;q<d.n;q++){
  int z=d.go[q][0];d.go[q][0]=d.go[q][1];d.go[q][1]=z;
 }
 dfa_write(&d);return 0;
}
