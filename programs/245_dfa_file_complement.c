/* Program 245: Emit a complete DFA for the complemented language. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 for(int q=0;q<d.n;q++)d.final[q]=1-d.final[q];
 dfa_write(&d);return 0;
}
