/* Common plain-text DFA format: N START; N final flags; N pairs of 0/1 destinations. */
#ifndef AUTOMATA_DFA_IO_H
#define AUTOMATA_DFA_IO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define DFA_MAX 32
typedef struct {int n,start,final[DFA_MAX],go[DFA_MAX][2];} DFA;
static inline int dfa_read(const char *path,DFA*d){
 FILE*f=fopen(path,"r");if(!f)return 0;
 if(fscanf(f,"%d%d",&d->n,&d->start)!=2||d->n<1||d->n>DFA_MAX||d->start<0||d->start>=d->n){fclose(f);return 0;}
 for(int q=0;q<d->n;q++)if(fscanf(f,"%d",&d->final[q])!=1||(d->final[q]!=0&&d->final[q]!=1)){fclose(f);return 0;}
 for(int q=0;q<d->n;q++)for(int b=0;b<2;b++)if(fscanf(f,"%d",&d->go[q][b])!=1||d->go[q][b]<0||d->go[q][b]>=d->n){fclose(f);return 0;}
 char extra;int ok=fscanf(f," %c",&extra)!=1;fclose(f);return ok;
}
static inline void dfa_write(const DFA*d){
 printf("%d %d\n",d->n,d->start);
 for(int q=0;q<d->n;q++)printf("%s%d",q?" ":"",d->final[q]);
 putchar('\n');
 for(int q=0;q<d->n;q++)printf("%d %d\n",d->go[q][0],d->go[q][1]);
}
static inline int dfa_length(const char*s,long max,long*out){
 errno=0;char*end;long n=strtol(s,&end,10);
 if(errno==ERANGE||end==s||*end||n<0||n>max)return 0;
 *out=n;return 1;
}
#endif
