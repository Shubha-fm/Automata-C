/* Program 217: Earley membership for S -> a S b | epsilon. ISO C11. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 32
#define MAXITEM 256
typedef struct{short rule,dot,origin;}Item;
static Item chart[MAXLEN+1][MAXITEM];
static int count[MAXLEN+1];
static const char*rhs[]={"S","aSb",""};
static const char lhs[]={'X','S','S'};
static int add(int position,Item item){
    for(int i=0;i<count[position];i++){
        Item old=chart[position][i];
        if(old.rule==item.rule&&old.dot==item.dot&&old.origin==item.origin)return 0;
    }
    if(count[position]>=MAXITEM){fprintf(stderr,"Earley chart overflow\n");exit(1);}
    chart[position][count[position]++]=item;return 1;
}
int main(int argc,char**argv){
    if(argc!=2){fprintf(stderr,"Usage: %s AB_WORD\n",argv[0]);return 2;}
    const char*s=argv[1];size_t n=strlen(s);
    if(n>MAXLEN){fprintf(stderr,"Maximum length 32\n");return 2;}
    for(size_t i=0;i<n;i++)if(s[i]!='a'&&s[i]!='b'){
        fprintf(stderr,"Alphabet is {a,b}\n");return 2;
    }
    add(0,(Item){0,0,0});
    for(int position=0;position<=(int)n;position++){
        int changed;
        do{
            changed=0;
            for(int i=0;i<count[position];i++){
                Item item=chart[position][i];
                const char*rule=rhs[item.rule];
                int length=(int)strlen(rule);
                if(item.dot<length){
                    if(rule[item.dot]=='S'){
                        changed|=add(position,(Item){1,0,(short)position});
                        changed|=add(position,(Item){2,0,(short)position});
                    }
                }else{
                    for(int k=0;k<count[item.origin];k++){
                        Item other=chart[item.origin][k];
                        const char*body=rhs[other.rule];
                        if(other.dot<(int)strlen(body)&&body[other.dot]==lhs[item.rule]){
                            changed|=add(position,(Item){
                                other.rule,(short)(other.dot+1),other.origin
                            });
                        }
                    }
                }
            }
        }while(changed);
        if(position==(int)n)break;
        for(int i=0;i<count[position];i++){
            Item item=chart[position][i];
            const char*rule=rhs[item.rule];
            if(item.dot<(int)strlen(rule)&&rule[item.dot]==s[position])
                add(position+1,(Item){item.rule,(short)(item.dot+1),item.origin});
        }
    }
    for(int i=0;i<count[n];i++){
        Item item=chart[n][i];
        if(item.rule==0&&item.dot==1&&item.origin==0){
            printf("ACCEPT CHART_ITEMS=%d\n",count[n]);return 0;
        }
    }
    printf("REJECT CHART_ITEMS=%d\n",count[n]);return 0;
}
