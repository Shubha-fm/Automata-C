/* 109: Stack-style recognition of a^n b^(2n). Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){size_t a=0,b=0;while(s[a]=='a')a++;while(s[a+b]=='b')b++;return s[a+b]=='\0'&&b==2*a;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
