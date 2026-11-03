/* Program 185: Inverse of bit-stuffing transducer with malformed-input rejection. C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s STUFFED_BINARY_WORD\n",argv[0]);return 2;}
    const char *s=argv[1];size_t n=strlen(s);
    for(size_t i=0;i<n;i++)
        if(s[i]!='0'&&s[i]!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
    /* Validate first, so invalid sequences never produce partial output. */
    int ones=0;
    for(size_t i=0;i<n;i++){
        if(ones==5){
            if(s[i]!='0'){fprintf(stderr,"Missing stuffed zero\n");return 2;}
            ones=0;continue;
        }
        ones=s[i]=='1'?ones+1:0;
    }
    if(ones==5){fprintf(stderr,"Missing terminal stuffed zero\n");return 2;}
    printf("UNSTUFFED=");
    ones=0;
    for(size_t i=0;i<n;i++){
        if(ones==5){ones=0;continue;}
        putchar(s[i]);ones=s[i]=='1'?ones+1:0;
    }
    putchar('\n');return 0;
}
