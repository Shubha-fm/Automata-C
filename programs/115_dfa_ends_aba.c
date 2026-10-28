/* 115: Strings over a,b ending in aba. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { size_t n=strlen(s);for(size_t i=0;i<n;i++)if(s[i]!='a'&&s[i]!='b')return 0;return n>=3&&strcmp(s+n-3,"aba")==0; }
int main(int argc, char **argv) {
 char input[4096]; const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1]; else {if(!fgets(input,sizeof(input),stdin))return 2;input[strcspn(input,"\r\n")]=0;s=input;}
 puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
