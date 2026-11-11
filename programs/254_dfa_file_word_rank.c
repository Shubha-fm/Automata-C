/* Program 254: Rank or unrank accepted words of a given length in a file-based DFA. ISO C11. */
#include "../include/dfa_io.h"
#define MAXLEN 60
static unsigned long long ways[MAXLEN+1][DFA_MAX];
static void prepare(const DFA *d,size_t n) {
    for (int q=0;q<d->n;q++) ways[0][q]=(unsigned long long)d->final[q];
    for (size_t k=1;k<=n;k++)
        for (int q=0;q<d->n;q++)
            ways[k][q]=ways[k-1][d->go[q][0]]+ways[k-1][d->go[q][1]];
}
static int parse_rank(const char*s,unsigned long long*out) {
    if (!*s||*s=='-')return 0;
    errno=0;char *end=NULL;
    unsigned long long value=strtoull(s,&end,10);
    if (errno==ERANGE||end==s||*end)return 0;
    *out=value;return 1;
}
int main(int argc,char **argv) {
    if (argc!=4 && argc!=5) {
        fprintf(stderr,"Usage: %s MODEL.dfa rank WORD | MODEL.dfa unrank LENGTH INDEX\n",argv[0]);
        return 2;
    }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (argc==4 && strcmp(argv[2],"rank")==0) {
        const char *word=argv[3];size_t n=strlen(word);
        if (n>MAXLEN) { fprintf(stderr,"Maximum word length is 60\n");return 2; }
        prepare(&d,n);
        unsigned long long rank=0;
        int q=d.start;
        for (size_t i=0;i<n;i++) {
            int bit=word[i]-'0';
            if (bit!=0&&bit!=1) { fprintf(stderr,"Binary word required\n");return 2; }
            if (bit==1) rank+=ways[n-i-1][d.go[q][0]];
            q=d.go[q][bit];
        }
        if (!d.final[q]) { puts("REJECT");return 0; }
        printf("RANK=%llu TOTAL=%llu\n",rank,ways[n][d.start]);
        return 0;
    }
    if (argc==5 && strcmp(argv[2],"unrank")==0) {
        long length;
        unsigned long long index;
        if (!dfa_length(argv[3],MAXLEN,&length)||!parse_rank(argv[4],&index)) {
            fprintf(stderr,"Length 0..60 and nonnegative rank required\n");return 2;
        }
        prepare(&d,(size_t)length);
        unsigned long long total=ways[length][d.start];
        if (index>=total) { fprintf(stderr,"Rank out of range; TOTAL=%llu\n",total);return 2; }
        int q=d.start;
        char word[MAXLEN+1];
        for (long i=0;i<length;i++) {
            unsigned long long zero=ways[length-i-1][d.go[q][0]];
            int bit=index>=zero;
            if (bit) index-=zero;
            word[i]=(char)('0'+bit);q=d.go[q][bit];
        }
        word[length]='\0';
        printf("WORD=%s TOTAL=%llu\n",word,total);
        return 0;
    }
    fprintf(stderr,"Use rank WORD or unrank LENGTH INDEX\n");return 2;
}
