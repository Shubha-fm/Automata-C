/* 117: Even a count and ends in b. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { size_t n=strlen(s);int parity=0;for(const char*p=s;*p;p++){if(*p=='a')parity^=1;else if(*p!='b')return 0;}return n>0&&!parity&&s[n-1]=='b'; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
