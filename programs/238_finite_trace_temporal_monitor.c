/* Program 238: Evaluate safety and bounded-response properties on finite binary traces. ISO C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_TRACE\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>4096){fprintf(stderr,"Maximum length 4096\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
        fprintf(stderr,"Binary trace required\n");return 2;
    }
    int no_11=1,has_01=0,response=1;
    for(size_t i=0;i<n;i++){
        if(i>0&&s[i-1]=='1'&&s[i]=='1')no_11=0;
        if(i>0&&s[i-1]=='0'&&s[i]=='1')has_01=1;
        if(s[i]=='1'&&(i+1>=n||s[i+1]!='0'))response=0;
    }
    printf("NO_11=%s HAS_01=%s RESPONSE=%s\n",
           no_11?"PASS":"FAIL",has_01?"YES":"NO",
           response?"PASS":"FAIL");
    return 0;
}
