/* Program 210: Complete a partial binary DFA by adding a rejecting sink state. ISO C11. */
#include <stdio.h>
#define MAXSTATES 32
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s PARTIAL_DFA_FILE\n",argv[0]);return 2;}
    FILE*f=fopen(argv[1],"r");
    if(!f){perror("Open DFA file");return 2;}
    int n=0,start=0,final[MAXSTATES+1]={0},transition[MAXSTATES+1][2];
    if(fscanf(f,"%d%d",&n,&start)!=2||n<1||n>MAXSTATES||
       start<0||start>=n){fclose(f);fprintf(stderr,"Invalid DFA header\n");return 2;}
    for(int i=0;i<n;i++)
        if(fscanf(f,"%d",&final[i])!=1||(final[i]!=0&&final[i]!=1)){
            fclose(f);fprintf(stderr,"Invalid accepting flags\n");return 2;
        }
    int missing=0;
    for(int i=0;i<n;i++)for(int b=0;b<2;b++){
        if(fscanf(f,"%d",&transition[i][b])!=1||
           transition[i][b]<-1||transition[i][b]>=n){
            fclose(f);fprintf(stderr,"Invalid transition\n");return 2;
        }
        if(transition[i][b]==-1)missing++;
    }
    char extra;
    if(fscanf(f," %c",&extra)==1){fclose(f);fprintf(stderr,"Unexpected trailing data\n");return 2;}
    fclose(f);
    int total=n+(missing>0);
    int sink=n;
    if(missing){
        for(int i=0;i<n;i++)for(int b=0;b<2;b++)
            if(transition[i][b]<0)transition[i][b]=sink;
        transition[sink][0]=sink;transition[sink][1]=sink;
        final[sink]=0;
    }
    printf("STATES=%d START=%d SINK=",total,start);
    if(missing)printf("%d\n",sink);else puts("NONE");
    printf("COMPLETED=%d\n",missing);
    for(int i=0;i<total;i++)printf("q%d final=%d on0=q%d on1=q%d\n",
        i,final[i],transition[i][0],transition[i][1]);
    return 0;
}
