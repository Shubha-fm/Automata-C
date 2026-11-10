/* Program 250: Export a complete file-based DFA as Graphviz DOT. C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 puts("digraph DFA {");puts("  rankdir=LR;");puts("  start [shape=point];");
 printf("  start -> q%d;\n",d.start);
 for(int q=0;q<d.n;q++)
  printf("  q%d [shape=%s];\n",q,d.final[q]?"doublecircle":"circle");
 for(int q=0;q<d.n;q++)for(int b=0;b<2;b++)
  printf("  q%d -> q%d [label=\"%d\"];\n",q,d.go[q][b],b);
 puts("}");return 0;
}
