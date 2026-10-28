/* 129: Binary number divisible by 19. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int r=0;for(;*s;s++){if(*s!='0'&&*s!='1')return 0;r=(2*r+(*s-'0'))%19;}return r==0; }
int main(int argc,char **argv) {
 char buf[4096];const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}
 puts(accepts(s)?"ACCEPT":"REJECT");return 0;
}
