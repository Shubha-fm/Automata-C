/* DFA for ASCII identifiers [A-Za-z_][A-Za-z0-9_]*. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"automata_1";int ok=((*s>='a'&&*s<='z')||(*s>='A'&&*s<='Z')||*s=='_');for(const char*p=s+(*s!='\0');*p;p++)if(!((*p>='a'&&*p<='z')||(*p>='A'&&*p<='Z')||(*p>='0'&&*p<='9')||*p=='_'))ok=0;puts(ok?"ACCEPT":"REJECT");return 0;}
