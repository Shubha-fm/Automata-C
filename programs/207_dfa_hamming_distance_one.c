/* Program 207: Hamming-distance-one language recognizer for a supplied binary target. ISO C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s BINARY_TARGET BINARY_WORD\n",argv[0]);return 2;}
    const char*target=argv[1],*word=argv[2];
    size_t n=strlen(target),m=strlen(word);
    if(n>4096||m>4096){fprintf(stderr,"Maximum length is 4096\n");return 2;}
    for(int k=1;k<=2;k++)
        for(const char*s=argv[k];*s;s++)
            if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
    if(n!=m){puts("DISTANCE=UNDEFINED REJECT");return 0;}
    int distance=0;
    for(size_t i=0;i<n;i++)if(target[i]!=word[i])distance++;
    printf("DISTANCE=%d %s\n",distance,distance<=1?"ACCEPT":"REJECT");
    return 0;
}
