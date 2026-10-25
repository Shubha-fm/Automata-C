/* Recognition of regex 0(1)* (fixed Thompson-language example). Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"0111";int ok=*s=='0';if(ok)for(const char*p=s+1;*p;p++)if(*p!='1')ok=0;puts(ok?"ACCEPT":"REJECT");return 0;}
