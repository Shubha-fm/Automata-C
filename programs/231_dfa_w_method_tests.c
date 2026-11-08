/* Program 231: Construct a W-method conformance suite for a three-state DFA. ISO C11. */
#include <stdio.h>
#include <string.h>
static const int delta[3][2]={{1,0},{1,2},{1,0}};
static char tests[40][12];
static int count=0;
static void add(const char*s){
    for(int i=0;i<count;i++)if(strcmp(tests[i],s)==0)return;
    if(count<40){strcpy(tests[count],s);count++;}
}
static int accepts(const char*s,int mutant){
    int q=0;
    for(;*s;s++){
        int b=*s-'0';
        if(mutant==2&&q==1&&b==1)q=0;
        else if(mutant==3&&q==2&&b==0)q=2;
        else q=delta[q][b];
    }
    return q==2||(mutant==1&&q==0);
}
int main(void){
    const char *cover[]={"","0","01"};
    const char *middle[]={"","0","1"};
    const char *characterize[]={"","1"};
    for(int p=0;p<3;p++)for(int m=0;m<3;m++)for(int w=0;w<2;w++){
        char candidate[12];
        snprintf(candidate,sizeof candidate,"%s%s%s",cover[p],middle[m],characterize[w]);
        add(candidate);
    }
    int killed=0;
    for(int m=1;m<=3;m++){
        const char*witness=NULL;
        for(int j=0;j<count;j++)
            if(accepts(tests[j],0)!=accepts(tests[j],m)){
                witness=tests[j];break;
            }
        if(witness)killed++;
        printf("MUTANT_%d=%s\n",m,witness?(*witness?witness:"<epsilon>"):"SURVIVED");
    }
    printf("TEST_COUNT=%d KILLED_MUTANTS=%d/3\n",count,killed);
    return killed==3?0:1;
}
