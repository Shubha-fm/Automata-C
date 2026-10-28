/* 127: a count multiple of 3 and b count even. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int a=0,b=0;for(;*s;s++){if(*s=='a')a=(a+1)%3;else if(*s=='b')b^=1;else return 0;}return a==0&&b==0; }
int main(int argc,char **argv) {
 char buf[4096];const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}
 puts(accepts(s)?"ACCEPT":"REJECT");return 0;
}
