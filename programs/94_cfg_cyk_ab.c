/* CYK-style membership for grammar S -> AB, A -> a, B -> b. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"ab";int ok=strlen(s)==2&&s[0]=='a'&&s[1]=='b';puts(ok?"ACCEPT":"REJECT");return 0;}
