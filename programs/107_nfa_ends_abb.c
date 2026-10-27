/* 107: NFA bitset simulation for strings ending abb. Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){unsigned state=1;for(;*s;s++){unsigned next=0;if(*s!='a'&&*s!='b')return 0;if(state&1){next|=1;if(*s=='a')next|=2;}if((state&2)&&*s=='b')next|=4;if((state&4)&&*s=='b')next|=8;state=next;}return (state&8)!=0;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
