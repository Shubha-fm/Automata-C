/* 122: Even number of 10 occurrences. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int count=0;char prev=0;for(;*s;s++){if(*s!='0'&&*s!='1')return 0;if(prev=='1'&&*s=='0')count^=1;prev=*s;}return count==0; }
int main(int argc,char **argv) {
 char buf[4096];const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}
 puts(accepts(s)?"ACCEPT":"REJECT");return 0;
}
