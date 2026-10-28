/* 119: Exactly two b symbols. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int count=0;for(;*s;s++){if(*s=='b')count++;else if(*s!='a')return 0;}return count==2; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
