/* 103: Recognize binary palindromes (CFG S->0S0|1S1|0|1|epsilon). Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){size_t n=strlen(s);for(size_t i=0;i<n;i++){if(s[i]!='0'&&s[i]!='1')return 0;if(s[i]!=s[n-1-i])return 0;}return 1;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
