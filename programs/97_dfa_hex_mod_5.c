/* Hexadecimal digit DFA modulo 5. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"A";int q=0,ok=1;for(const char*p=s;*p;p++){int d;if(*p>='0'&&*p<='9')d=*p-'0';else if(*p>='A'&&*p<='F')d=*p-'A'+10;else if(*p>='a'&&*p<='f')d=*p-'a'+10;else{ok=0;break;}q=(16*q+d)%5;}puts(ok&&q==0?"ACCEPT":"REJECT");return 0;}
