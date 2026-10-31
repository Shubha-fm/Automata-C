/* Program 143: Decimal integer divisible by 13. DFA remainder states 0..12. */
#include <stdio.h>
#include <string.h>
static int digit(char c){if(c>='0'&&c<='9')return c-'0';if(c>='A'&&c<='F')return c-'A'+10;if(c>='a'&&c<='f')return c-'a'+10;return -1;}
static int accepts(const char*s){int remainder=0;if(!*s)return 0;for(;*s;s++){int d=digit(*s);if(d<0||d>=10)return 0;remainder=(remainder*10+d)%13;}return remainder==0;}
int main(int argc,char**argv){char input[4096];const char*s;if(argc>2){fprintf(stderr,"Usage: %s [number]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(input,sizeof input,stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
