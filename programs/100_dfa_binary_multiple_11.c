/* Binary-number DFA modulo 11. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"1011";int q=0,ok=1;for(const char*p=s;*p;p++){if(*p!='0'&&*p!='1'){ok=0;break;}q=(q*2+(*p-'0'))%11;}puts(ok&&q==0?"ACCEPT":"REJECT");return 0;}
