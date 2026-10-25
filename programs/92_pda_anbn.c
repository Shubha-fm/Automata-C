/* Pushdown recognition of a^n b^n (n>=0). Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"aaabbb";int n=0,phase=0,ok=1;for(const char*p=s;*p;p++){if(*p=='a'&&!phase)n++;else if(*p=='b'){phase=1;if(--n<0)ok=0;}else ok=0;}puts(ok&&n==0?"ACCEPT":"REJECT");return 0;}
