/* Program 213: Find the next accepted same-length word in lexicographic order. ISO C11. */
#include <stdio.h>
#include <string.h>
#define LIMIT 60
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>LIMIT){fprintf(stderr,"Maximum length is 60\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='0'&&s[i]!='1'){
        fprintf(stderr,"Binary input only\n");return 2;
    }
    unsigned long long ways[LIMIT+1][2]={{0}};
    ways[0][0]=1;
    for(size_t k=1;k<=n;k++)for(int p=0;p<2;p++)
        ways[k][p]=ways[k-1][p]+ways[k-1][p^1];
    int prefix[LIMIT+1]={0};
    for(size_t i=0;i<n;i++)prefix[i+1]=prefix[i]^(s[i]=='1');
    char next[LIMIT+1];
    for(size_t pos=n;pos>0;pos--){
        size_t i=pos-1;
        if(s[i]!='0')continue;
        int parity=prefix[i]^1;
        if(!ways[n-i-1][parity])continue;
        memcpy(next,s,i);next[i]='1';
        for(size_t j=i+1;j<n;j++){
            size_t remaining=n-j-1;
            if(ways[remaining][parity])next[j]='0';
            else{next[j]='1';parity^=1;}
        }
        next[n]='\0';
        printf("NEXT=%s\n",next);
        return 0;
    }
    puts("NO_SUCCESSOR");return 0;
}
