/* Decimal digit DFA modulo 3. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"123";int q=0,ok=1;for(const char*p=s;*p;p++){if(*p<'0'||*p>'9'){ok=0;break;}q=(10*q+(*p-'0'))%3;}puts(ok&&q==0?"ACCEPT":"REJECT");return 0;}
