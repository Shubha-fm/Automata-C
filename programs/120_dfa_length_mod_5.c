/* 120: Word length divisible by five over a,b. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int n=0;for(;*s;s++){if(*s!='a'&&*s!='b')return 0;n=(n+1)%5;}return n==0; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
