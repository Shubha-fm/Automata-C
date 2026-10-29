/* Program 131: Binary integer divisible by 23. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { int r=0;for(;*s;s++){if(*s!='0'&&*s!='1')return 0;r=(2*r+*s-'0')%23;}return r==0; }
int main(int argc, char **argv) {
    char buffer[4096]; const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [word]\n", argv[0]); return 2; }
    if (argc == 2) s=argv[1];
    else { if (!fgets(buffer,sizeof buffer,stdin)) return 2; buffer[strcspn(buffer,"\r\n")]=0; s=buffer; }
    puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
