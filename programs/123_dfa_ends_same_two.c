/* 123: Binary strings whose last two digits agree. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { size_t n=strlen(s);for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1')return 0;return n>=2&&s[n-1]==s[n-2]; }
int main(int argc,char **argv) {
 char buf[4096];const char *s;
 if(argc>2){fprintf(stderr,"Usage: %s [word]\n",argv[0]);return 2;}
 if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}
 puts(accepts(s)?"ACCEPT":"REJECT");return 0;
}
