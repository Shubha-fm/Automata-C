/* 101: Balanced () and [] with stack. Input argument or stdin; prints ACCEPT/REJECT. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s){char stack[4096];size_t top=0;int ok=1;for(const char*p=s;*p;p++){if(*p=='('||*p=='['){if(top>=sizeof stack){ok=0;break;}stack[top++]=*p;}else if(*p==')'||*p==']'){if(!top||((*p==')'&&stack[top-1]!='(')||(*p==']'&&stack[top-1]!='['))){ok=0;break;}top--;}else{ok=0;break;}}return ok&&top==0;}
int main(int argc,char **argv){char buf[4096];const char *s;if(argc>2){fprintf(stderr,"Usage: %s [string]\n",argv[0]);return 2;}if(argc==2)s=argv[1];else{if(!fgets(buf,sizeof buf,stdin))return 2;buf[strcspn(buf,"\r\n")]=0;s=buf;}puts(accepts(s)?"ACCEPT":"REJECT");return 0;}
