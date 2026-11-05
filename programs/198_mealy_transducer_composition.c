/* Program 198: Compose bit-complement and binary-to-Gray Mealy transducers. ISO C11. */
#include <stdio.h>
#include <string.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s BINARY_WORD\n",argv[0]);return 2;}
    const char *s=argv[1];size_t n=strlen(s);
    if(n>4096){fprintf(stderr,"Maximum length is 4096\n");return 2;}
    for(size_t i=0;i<n;i++)
        if(s[i]!='0'&&s[i]!='1'){fprintf(stderr,"Binary only\n");return 2;}
    printf("INTERMEDIATE=");
    for(size_t i=0;i<n;i++)putchar('0'+(1-(s[i]-'0')));
    printf(" COMPOSED_GRAY=");
    int previous=0;
    for(size_t i=0;i<n;i++){
        int complemented=1-(s[i]-'0');
        putchar('0'+(complemented^previous));
        previous=complemented;
    }
    putchar('\n');return 0;
}
