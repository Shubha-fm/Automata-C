/* 111: Binary number divisible by 17. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int q=0;for(;*s;s++){if(*s!='0'&&*s!='1')return 0;q=(q*2+*s-'0')%17;}return q==0; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
