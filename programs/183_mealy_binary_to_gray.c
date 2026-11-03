/* Program 183: Mealy transducer converting binary digits into Gray code. C11. */
#include <stdio.h>
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    for(const char *s=argv[1];*s;s++)
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary alphabet only\n");return 2;}
    int previous=0;
    printf("GRAY=");
    for(const char *s=argv[1];*s;s++){
        int bit=*s-'0';
        putchar('0'+(bit^previous));
        previous=bit;
    }
    putchar('\n');return 0;
}
