/* Program 188: Timed transition monitor: consecutive timestamps must be within ten units. C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s T0,T1,T2,...\n",argv[0]);return 2;}
    const char*p=argv[1];long previous=0;int count=0,safe=1;
    if(!*p){fprintf(stderr,"Provide at least two timestamps\n");return 2;}
    while(*p){
        errno=0;char*end=NULL;
        long current=strtol(p,&end,10);
        if(errno==ERANGE||p==end||current<0||
           (*end!=','&&*end!='\0')){
            fprintf(stderr,"Invalid nonnegative timestamp list\n");return 2;
        }
        if(count>0&&(current<previous||current-previous>10))safe=0;
        count++;previous=current;
        if(*end==','){
            p=end+1;if(!*p){fprintf(stderr,"Trailing comma\n");return 2;}
        }else p=end;
    }
    if(count<2){fprintf(stderr,"Provide at least two timestamps\n");return 2;}
    puts(safe?"SAFE":"UNSAFE");
    return 0;
}
