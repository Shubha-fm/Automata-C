/* Export a user-provided binary DFA as Graphviz DOT. */
#include <stdio.h>
#define MAX 32
int main(int argc,char **argv){
 if(argc!=2){fprintf(stderr,"Usage: %s DFA_FILE\n",argv[0]);return 2;}
 FILE*f=fopen(argv[1],"r");if(!f){perror("open");return 2;}
 int n,start,k,final[MAX]={0},tr[MAX][2],ok=1;
 if(fscanf(f,"%d%d%d",&n,&start,&k)!=3||n<1||n>MAX||start<0||start>=n||k<0||k>n)ok=0;
 if(ok)for(int i=0;i<k;i++){int s;if(fscanf(f,"%d",&s)!=1||s<0||s>=n){ok=0;break;}final[s]=1;}
 if(ok)for(int i=0;i<n;i++)for(int b=0;b<2;b++)if(fscanf(f,"%d",&tr[i][b])!=1||tr[i][b]<0||tr[i][b]>=n)ok=0;
 fclose(f);if(!ok){fprintf(stderr,"Invalid DFA file\n");return 2;}
 puts("digraph DFA {");puts("  rankdir=LR;");puts("  node [shape=circle];");
 puts("  start [shape=point];");printf("  start -> q%d;\n",start);
 for(int i=0;i<n;i++)if(final[i])printf("  q%d [shape=doublecircle];\n",i);
 for(int i=0;i<n;i++)for(int b=0;b<2;b++)printf("  q%d -> q%d [label=\"%d\"];\n",i,tr[i][b],b);
 puts("}");return 0;
}
