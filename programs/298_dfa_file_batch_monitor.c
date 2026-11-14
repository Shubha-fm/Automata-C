/* Program 298: Check binary trace lines in a file and summarize accepted and rejected cases. ISO C11. */
#include "../include/dfa_io.h"
#define LINE_SIZE 4098
int main(int argc,char**argv){
 if(argc!=3){fprintf(stderr,"Usage: %s MODEL.dfa TRACE_LINES.txt\n",argv[0]);return 2;}
 DFA d;if(!dfa_read(argv[1],&d)){fprintf(stderr,"Invalid DFA file\n");return 2;}
 FILE*f=fopen(argv[2],"r");
 if(!f){fprintf(stderr,"Unable to open trace file\n");return 2;}
 char line[LINE_SIZE];
 long total=0,accepted=0,first_rejected=0;
 while(fgets(line,sizeof line,f)){
  size_t n=strlen(line);
  if(n&&line[n-1]=='\n')line[--n]='\0';
  else if(n>4096){fclose(f);fprintf(stderr,"Trace line exceeds 4096 symbols\n");return 2;}
  if(n&&line[n-1]=='\r')line[--n]='\0';
  if(n>4096){fclose(f);fprintf(stderr,"Trace line exceeds 4096 symbols\n");return 2;}
  int q=d.start;
  for(size_t i=0;i<n;i++){
   if(line[i]!='0'&&line[i]!='1'){
    fclose(f);fprintf(stderr,"Invalid binary trace on line %ld\n",total+1);return 2;
   }
   q=d.go[q][line[i]-'0'];
  }
  total++;
  if(d.final[q])accepted++;
  else if(!first_rejected)first_rejected=total;
 }
 if(ferror(f)){fclose(f);fprintf(stderr,"Trace read failed\n");return 2;}
 fclose(f);
 printf("TOTAL=%ld ACCEPTED=%ld REJECTED=%ld FIRST_REJECTED_LINE=%ld\n",
  total,accepted,total-accepted,first_rejected);
 return 0;
}
