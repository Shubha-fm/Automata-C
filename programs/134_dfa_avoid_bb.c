/* Program 134: Strings over ab without adjacent b. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { char prev=0;for(;*s;s++){if(*s!='a'&&*s!='b')return 0;if(prev=='b'&&*s=='b')return 0;prev=*s;}return 1; }
int main(int argc, char **argv) {
    char buffer[4096]; const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [word]\n", argv[0]); return 2; }
    if (argc == 2) s=argv[1];
    else { if (!fgets(buffer,sizeof buffer,stdin)) return 2; buffer[strcspn(buffer,"\r\n")]=0; s=buffer; }
    puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
