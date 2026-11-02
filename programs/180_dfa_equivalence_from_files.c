/* DFA equivalence check with shortest counterexample for two DFA files. */
#include <stdio.h>
#define MAX 16
#define PAIRS (MAX*MAX)
typedef struct {int n,start,final[MAX],trans[MAX][2];} DFA;
static int load(const char*path,DFA*d){
 FILE*f=fopen(path,"r");if(!f){perror("open");return 0;}
 int k,ok=1;
 if(fscanf(f,"%d%d%d",&d->n,&d->start,&k)!=3||d->n<1||d->n>MAX||d->start<0||d->start>=d->n||k<0||k>d->n)ok=0;
 for(int i=0;i<MAX;i++)d->final[i]=0;
 if(ok)for(int i=0;i<k;i++){int s;if(fscanf(f,"%d",&s)!=1||s<0||s>=d->n){ok=0;break;}d->final[s]=1;}
 if(ok)for(int i=0;i<d->n;i++)for(int b=0;b<2;b++)if(fscanf(f,"%d",&d->trans[i][b])!=1||d->trans[i][b]<0||d->trans[i][b]>=d->n)ok=0;
 fclose(f);return ok;
}
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s FIRST_DFA SECOND_DFA\n",argv[0]);return 2;}
 DFA a,b;if(!load(argv[1],&a)||!load(argv[2],&b)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int n=a.n*b.n,seen[PAIRS]={0},queue[PAIRS],parent[PAIRS],edge[PAIRS];
 for(int i=0;i<n;i++)parent[i]=-1;
 int start=a.start*b.n+b.start,h=0,t=1,goal=-1;
 queue[0]=start;seen[start]=1;
 while(h<t){
   int p=queue[h++],x=p/b.n,y=p%b.n;
   if(a.final[x]!=b.final[y]){goal=p;break;}
   for(int bit=0;bit<2;bit++){
     int z=a.trans[x][bit]*b.n+b.trans[y][bit];
     if(!seen[z]){seen[z]=1;parent[z]=p;edge[z]=bit;queue[t++]=z;}
   }
 }
 if(goal<0){puts("EQUIVALENT");return 0;}
 char word[PAIRS+1];int count=0;
 for(int q=goal;parent[q]>=0;q=parent[q])word[count++]=(char)('0'+edge[q]);
 printf("COUNTEREXAMPLE=");if(!count)printf("<epsilon>");
 while(count)putchar(word[--count]);
 putchar('\n');return 0;
}
