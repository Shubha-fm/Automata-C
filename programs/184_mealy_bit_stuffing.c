/* Program 184: Mealy-style bit stuffing: insert zero after five consecutive ones. C11. */
#include <stdio.h>
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    for(const char*s=argv[1];*s;s++)
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
    int ones=0;
    printf("STUFFED=");
    for(const char*s=argv[1];*s;s++){
        putchar(*s);
        ones=(*s=='1')?ones+1:0;
        if(ones==5){putchar('0');ones=0;}
    }
    putchar('\n');return 0;
}
