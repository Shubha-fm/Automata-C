/* Pushdown automaton for balanced parentheses. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"(()())";int depth=0,ok=1;for(const char*p=s;*p;p++){if(*p=='(')depth++;else if(*p==')'){if(--depth<0)ok=0;}else ok=0;}puts(ok&&depth==0?"ACCEPT":"REJECT");return 0;}
