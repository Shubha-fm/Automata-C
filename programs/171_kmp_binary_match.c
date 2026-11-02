/* KMP search: first occurrence of a configurable binary pattern. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    if (argc != 3) { fprintf(stderr,"Usage: %s PATTERN BINARY_WORD\n",argv[0]); return 2; }
    const char *pat=argv[1], *word=argv[2];
    size_t m=strlen(pat), n=strlen(word);
    if (!m || m>4096) { fprintf(stderr,"Pattern length must be 1..4096\n");return 2; }
    for(size_t i=0;i<m;i++)if(pat[i]!='0'&&pat[i]!='1')return 2;
    for(size_t i=0;i<n;i++)if(word[i]!='0'&&word[i]!='1')return 2;
    size_t *lps=calloc(m,sizeof *lps);
    if(!lps)return 2;
    for(size_t i=1,len=0;i<m;){
        if(pat[i]==pat[len])lps[i++]=++len;
        else if(len)len=lps[len-1];else lps[i++]=0;
    }
    for(size_t i=0,j=0;i<n;){
        if(word[i]==pat[j]){i++;j++;if(j==m){printf("MATCH=%zu\n",i-m);free(lps);return 0;}}
        else if(j)j=lps[j-1];else i++;
    }
    puts("NOT_FOUND");free(lps);return 0;
}
