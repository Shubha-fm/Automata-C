/* Program 227: Count parses in the ambiguous grammar S -> SS | a via dynamic programming. C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s A_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>20){fprintf(stderr,"Maximum 20 symbols\n");return 2;}
    unsigned long long count[21]={0};
    count[1]=1;
    for(size_t length=2;length<=n;length++)
        for(size_t split=1;split<length;split++)
            count[length]+=count[split]*count[length-split];
    for(size_t i=0;i<n;i++)if(s[i]!='a'){
        printf("PARSES=0 AMBIGUOUS=NO\n");return 0;
    }
    unsigned long long total=n?count[n]:0;
    printf("PARSES=%llu AMBIGUOUS=%s\n",
           total,total>1?"YES":"NO");
    return 0;
}

