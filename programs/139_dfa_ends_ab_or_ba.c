/* Program 139: Strings over ab ending ab or ba. */
#include <stdio.h>
#include <string.h>
static int accepts(const char *s) { size_t n=strlen(s);for(size_t i=0;i<n;i++)if(s[i]!='a'&&s[i]!='b')return 0;return n>=2&&s[n-1]!=s[n-2]; }
int main(int argc, char **argv) {
    char buffer[4096]; const char *s;
    if (argc > 2) { fprintf(stderr, "Usage: %s [word]\n", argv[0]); return 2; }
    if (argc == 2) s=argv[1];
    else { if (!fgets(buffer,sizeof buffer,stdin)) return 2; buffer[strcspn(buffer,"\r\n")]=0; s=buffer; }
    puts(accepts(s)?"ACCEPT":"REJECT"); return 0;
}
