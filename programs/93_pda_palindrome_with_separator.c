/* Pushdown recognition of w#w^R. Demonstration accepts one optional string argument. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){if(argc>2){fprintf(stderr,"Usage: %s [input]\n",argv[0]);return 2;}const char*s=argc>1?argv[1]:"101#101";const char*sep=strchr(s,'#');int ok=sep!=NULL;if(ok){size_t n=(size_t)(sep-s),m=strlen(sep+1);ok=n==m;for(size_t i=0;i<n&&ok;i++)if((s[i]!='0'&&s[i]!='1')||s[i]!=sep[1+n-1-i])ok=0;}puts(ok?"ACCEPT":"REJECT");return 0;}
