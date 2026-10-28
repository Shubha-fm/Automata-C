/* 125: Binary strings containing both 010 and 101. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { for(const char*p=s;*p;p++)if(*p!='0'&&*p!='1')return 0;return strstr(s,"010")!=NULL&&strstr(s,"101")!=NULL; }
int main(int argc,char **argv) {
 char buf[4096];const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}
 puts(accepts(s)?"ACCEPT":"REJECT");return 0;
}
