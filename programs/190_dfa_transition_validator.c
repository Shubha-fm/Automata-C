/* Program 190: Validate a complete deterministic binary transition table from a text file. C11. */
#include <stdio.h>
static int validate(FILE*f){
    int n=0,start=0,finals[64],transition[64][2];
    if(fscanf(f,"%d%d",&n,&start)!=2||n<1||n>64||start<0||start>=n)return 0;
    for(int i=0;i<n;i++){
        if(fscanf(f,"%d",&finals[i])!=1||
           (finals[i]!=0&&finals[i]!=1))return 0;
        for(int b=0;b<2;b++)transition[i][b]=-1;
    }
    for(int k=0;k<2*n;k++){
        int source,bit,destination;
        if(fscanf(f,"%d%d%d",&source,&bit,&destination)!=3||
           source<0||source>=n||bit<0||bit>1||
           destination<0||destination>=n||
           transition[source][bit]>=0)return 0;
        transition[source][bit]=destination;
    }
    for(int i=0;i<n;i++)for(int b=0;b<2;b++)
        if(transition[i][b]<0)return 0;
    char extra;
    if(fscanf(f," %c",&extra)==1)return 0;
    printf("VALID STATES=%d START=%d\n",n,start);
    return 1;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s DFA_TABLE_FILE\n",argv[0]);return 2;}
    FILE*f=fopen(argv[1],"r");
    if(!f){perror("Cannot open DFA table");return 2;}
    int good=validate(f);fclose(f);
    if(!good){puts("INVALID");return 1;}
    return 0;
}
