/* Program 195: Find the kth lexicographic word accepted by a parity DFA. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s LENGTH_0_TO_60 ZERO_BASED_RANK\n",argv[0]);return 2;}
    errno=0;char *end;
    unsigned long long n=strtoull(argv[1],&end,10);
    if(errno||end==argv[1]||*end||argv[1][0]=='-'||n>60){
        fprintf(stderr,"Length must be 0..60\n");return 2;
    }
    errno=0;
    unsigned long long rank=strtoull(argv[2],&end,10);
    if(errno||end==argv[2]||*end||argv[2][0]=='-'){
        fprintf(stderr,"Invalid rank\n");return 2;
    }
    unsigned long long ways[61][2]={{0}};
    ways[0][0]=1;
    for(unsigned i=1;i<=n;i++){
        ways[i][0]=ways[i-1][0]+ways[i-1][1];
        ways[i][1]=ways[i-1][1]+ways[i-1][0];
    }
    unsigned long long total=ways[n][0];
    if(rank>=total){fprintf(stderr,"Rank out of range; TOTAL=%llu\n",total);return 2;}
    int parity=0;
    char word[62];
    for(unsigned i=0;i<n;i++){
        unsigned rem=(unsigned)n-i-1;
        unsigned long long zeros=ways[rem][parity];
        if(rank<zeros)word[i]='0';
        else{word[i]='1';rank-=zeros;parity^=1;}
    }
    word[n]='\0';
    printf("WORD=%s TOTAL=%llu\n",word,total);
    return 0;
}
