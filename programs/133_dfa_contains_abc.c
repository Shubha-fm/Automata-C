/* Program 133: Strings over abc containing substring abc. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { for(const char*p=s;*p;p++)if(*p<'a'||*p>'c')return 0;return strstr(s,"abc")!=NULL; }
int main(int argc, char **argv) {
    char buffer[4096]; const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [word]\n", argv[0]); return 2; }
    if (argc == 2) s=argv[1];
    else { if (!fgets(buffer,sizeof buffer,stdin)) return 2; buffer[strcspn(buffer,"\r\n")]=0; s=buffer; }
    puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
