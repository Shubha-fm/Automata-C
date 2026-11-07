/* Program 229: Recognize shuffles of the two fixed words 01 and 10. C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char*s=argv[1],*a="01",*b="10";
    size_t n=strlen(s);
    if(n!=4){
        for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
            fprintf(stderr,"Binary alphabet only\n");return 2;
        }
        puts("REJECT PATHS=0");return 0;
    }
    unsigned long long dp[3][3]={{0}};
    dp[0][0]=1;
    for(int p=0;p<4;p++){
        if(s[p]!='0'&&s[p]!='1'){
            fprintf(stderr,"Binary alphabet only\n");return 2;
        }
        unsigned long long next[3][3]={{0}};
        for(int i=0;i<=2;i++)for(int j=0;j<=2;j++){
            if(i+j!=p)continue;
            if(i<2&&s[p]==a[i])next[i+1][j]+=dp[i][j];
            if(j<2&&s[p]==b[j])next[i][j+1]+=dp[i][j];
        }
        memcpy(dp,next,sizeof dp);
    }
    printf("%s PATHS=%llu\n",dp[2][2]?"ACCEPT":"REJECT",dp[2][2]);
    return 0;
}

