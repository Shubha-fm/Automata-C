/* Program 277: Find preperiod and period for repeated input zero in a DFA. ISO C11. */
#include "../include/dfa_io.h"
int main(int argc,char**argv){
 if(argc!=2){fprintf(stderr,"Usage: %s MODEL.dfa\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 int first[DFA_MAX],states[DFA_MAX+1];
 for(int q=0;q<d.n;q++)first[q]=-1;
 int q=d.start,count=0;
 while(first[q]<0){
  first[q]=count;states[count++]=q;
  q=d.go[q][0];
 }
 int mu=first[q],period=count-mu;
 printf("PREPERIOD=%d PERIOD=%d\n",mu,period);
 printf("ACCEPTING_PREFIX_LENGTHS=");
 int printed=0;
 for(int i=0;i<mu;i++)if(d.final[states[i]]){
  printf("%s%d",printed?",":"",i);printed++;
 }
 if(!printed)printf("<none>");
 putchar('\n');
 printf("ACCEPTING_CYCLE_OFFSETS=");
 printed=0;
 for(int i=mu;i<count;i++)if(d.final[states[i]]){
  printf("%s%d",printed?",":"",i-mu);printed++;
 }
 if(!printed)printf("<none>");
 putchar('\n');return 0;
}
