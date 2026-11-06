/* Program 218: Build and simulate an NFA from a user-supplied right-linear grammar. ISO C11. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
static uint32_t transition[27][2],epsilon[27];
static int accepting[27];
static int symbol_state(const char*s){
    if(strlen(s)==1&&s[0]>='A'&&s[0]<='Z')return s[0]-'A';
    if(strcmp(s,"#")==0)return 26;
    return -1;
}
static uint32_t closure(uint32_t mask){
    uint32_t old;
    do{
        old=mask;
        for(int q=0;q<26;q++)if(mask&(UINT32_C(1)<<q))
            mask|=epsilon[q];
    }while(old!=mask);
    return mask;
}
int main(int argc,char**argv){
    if(argc!=3){fprintf(stderr,"Usage: %s GRAMMAR_FILE BINARY_WORD\n",argv[0]);return 2;}
    FILE*f=fopen(argv[1],"r");
    if(!f){perror("Grammar file");return 2;}
    char start[4];int rules;
    if(fscanf(f,"%3s%d",start,&rules)!=2||symbol_state(start)<0||
       symbol_state(start)==26||rules<0||rules>256){
        fclose(f);fprintf(stderr,"Invalid grammar header\n");return 2;
    }
    int startstate=symbol_state(start);
    for(int i=0;i<rules;i++){
        char from[4],label[4],to[4];
        if(fscanf(f,"%3s%3s%3s",from,label,to)!=3||
           strlen(label)!=1){
            fclose(f);fprintf(stderr,"Invalid grammar production\n");return 2;
        }
        int source=symbol_state(from),target=symbol_state(to);
        if(source<0||source==26||target<0){
            fclose(f);fprintf(stderr,"Invalid nonterminal\n");return 2;
        }
        if(label[0]=='e'){
            if(target==26)accepting[source]=1;
            else epsilon[source]|=UINT32_C(1)<<target;
        }else if(label[0]=='0'||label[0]=='1'){
            transition[source][label[0]-'0']|=UINT32_C(1)<<target;
        }else{
            fclose(f);fprintf(stderr,"Expected 0, 1 or e\n");return 2;
        }
    }
    char extra;
    if(fscanf(f," %c",&extra)==1){
        fclose(f);fprintf(stderr,"Unexpected grammar data\n");return 2;
    }
    fclose(f);
    uint32_t active=closure(UINT32_C(1)<<startstate);
    for(const char*s=argv[2];*s;s++){
        if(*s!='0'&&*s!='1'){fprintf(stderr,"Binary word required\n");return 2;}
        uint32_t next=0;
        for(int q=0;q<27;q++)if(active&(UINT32_C(1)<<q))
            next|=transition[q][*s-'0'];
        active=closure(next);
    }
    int accept=(active&(UINT32_C(1)<<26))!=0;
    for(int q=0;q<26;q++)if(accepting[q]&&(active&(UINT32_C(1)<<q)))
        accept=1;
    puts(accept?"ACCEPT":"REJECT");return 0;
}
