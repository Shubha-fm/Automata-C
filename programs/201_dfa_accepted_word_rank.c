/* Program 201: Find a binary word's zero-based lexicographic rank among even-parity words. ISO C11. */
#include <stdio.h>
#include <string.h>
#define MAXLEN 60
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];
    size_t n=strlen(s);
    if(n>MAXLEN){fprintf(stderr,"Maximum word length: 60\n");return 2;}
    unsigned long long ways[MAXLEN+1][2]={{0}};
    ways[0][0]=1;
    for(size_t k=1;k<=n;k++)for(int parity=0;parity<2;parity++)
        ways[k][parity]=ways[k-1][parity]+ways[k-1][parity^1];
    unsigned long long rank=0;int parity=0;
    for(size_t i=0;i<n;i++){
        if(s[i]!='0'&&s[i]!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
        if(s[i]=='1'){
            rank+=ways[n-i-1][parity];
            parity^=1;
        }
    }
    if(parity){puts("REJECT: odd number of ones");return 0;}
    printf("RANK=%llu TOTAL=%llu\n",rank,ways[n][0]);
    return 0;
}
