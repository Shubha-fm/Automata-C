/* Program 68: NFA for reversed language of strings ending 01 (starts 10). Binary alphabet. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int accept(const char *s){return strlen(s)>=2&&s[0]=='1'&&s[1]=='0';}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [binary-string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{printf("Enter binary string: ");if(!fgets(buf,sizeof(buf),stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}for(const char *p=s;*p;p++)if(*p!='0'&&*p!='1'){fprintf(stderr,"Only 0 and 1 allowed\n");return 2;}puts(accept(s)?"ACCEPT":"REJECT");return 0;}
