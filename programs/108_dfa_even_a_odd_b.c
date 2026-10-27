/* 108: Product DFA: even a and odd b counts. Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){int a=0,b=0;for(;*s;s++){if(*s=='a')a^=1;else if(*s=='b')b^=1;else return 0;}return !a&&b;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
