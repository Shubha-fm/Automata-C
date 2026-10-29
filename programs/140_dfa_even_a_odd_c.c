/* Program 140: Strings over abc with even a count and odd c count. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int a=0,c=0;for(;*s;s++){if(*s=='a')a^=1;else if(*s=='c')c^=1;else if(*s!='b')return 0;}return !a&&c; }
int main(int argc, char **argv) {
    char buffer[4096]; const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [word]\n", argv[0]); return 2; }
    if (argc == 2) s=argv[1];
    else { if (!fgets(buffer,sizeof buffer,stdin)) return 2; buffer[strcspn(buffer,"\r\n")]=0; s=buffer; }
    puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
