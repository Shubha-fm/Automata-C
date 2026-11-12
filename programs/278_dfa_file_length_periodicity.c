/* Program 278: Determine eventual periodicity of accepted word lengths. ISO C11. */
#include "../include/dfa_io.h"
#define LIMIT 1024
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 if(d.n>10){fprintf(stderr,"Length periodicity limited to 10 states\n");return 2;}
 int first[LIMIT],subsets[LIMIT];
 for(int i=0;i<LIMIT;i++)first[i]=-1;
 int mask=1<<d.start,count=0;
 while(first[mask]<0){
  first[mask]=count;subsets[count++]=mask;
  int next=0;
  for(int q=0;q<d.n;q++)if(mask&(1<<q))
   for(int bit=0;bit<2;bit++)next|=1<<d.go[q][bit];
  mask=next;
 }
 int mu=first[mask],period=count-mu;
 printf("PREPERIOD=%d PERIOD=%d\n",mu,period);
 printf("ACCEPTING_PREFIX_LENGTHS=");
 int printed=0;
 for(int i=0;i<mu;i++){
  int accept=0;
  for(int q=0;q<d.n;q++)if((subsets[i]&(1<<q))&&d.final[q])accept=1;
  if(accept){printf("%s%d",printed?",":"",i);printed++;}
 }
 if(!printed)printf("<none>");
 putchar('\n');
 printf("ACCEPTING_CYCLE_OFFSETS=");
 printed=0;
 for(int i=mu;i<count;i++){
  int accept=0;
  for(int q=0;q<d.n;q++)if((subsets[i]&(1<<q))&&d.final[q])accept=1;
  if(accept){printf("%s%d",printed?",":"",i-mu);printed++;}
 }
 if(!printed)printf("<none>");
 putchar('\n');return 0;
}
