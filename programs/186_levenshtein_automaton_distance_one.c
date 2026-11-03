/* Program 186: Threshold-one Levenshtein recognizer for binary words. C11. */
#include <stdio.h>
#include <string.h>
#define LIMIT 256
static int min3(int a,int b,int c){
    int m=a<b?a:b;return m<c?m:c;
}
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s BINARY_TARGET BINARY_WORD\n",argv[0]);return 2;}
    size_t m=strlen(argv[1]),n=strlen(argv[2]);
    if(m>LIMIT||n>LIMIT){fprintf(stderr,"Maximum length 256\n");return 2;}
    for(int j=1;j<=2;j++)
        for(const char*s=argv[j];*s;s++)
            if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
    int previous[LIMIT+1],next[LIMIT+1];
    for(size_t j=0;j<=m;j++)previous[j]=(int)j;
    for(size_t i=1;i<=n;i++){
        next[0]=(int)i;
        for(size_t j=1;j<=m;j++){
            int sub=(argv[2][i-1]!=argv[1][j-1]);
            next[j]=min3(previous[j]+1,next[j-1]+1,previous[j-1]+sub);
        }
        for(size_t j=0;j<=m;j++)previous[j]=next[j];
    }
    printf("DISTANCE=%d %s\n",previous[m],previous[m]<=1?"ACCEPT":"REJECT");
    return 0;
}
