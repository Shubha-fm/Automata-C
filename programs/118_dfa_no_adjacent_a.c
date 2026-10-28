/* 118: No consecutive a symbols. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { char prev=0;for(;*s;s++){if(*s!='a'&&*s!='b')return 0;if(*s=='a'&&prev=='a')return 0;prev=*s;}return 1; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
