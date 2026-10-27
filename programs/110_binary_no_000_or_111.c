/* 110: DFA recognizer forbidding triple repeated bits. Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){int run=0;char prev=0;for(;*s;s++){if(*s!='0'&&*s!='1')return 0;run=(*s==prev)?run+1:1;if(run>=3)return 0;prev=*s;}return 1;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
