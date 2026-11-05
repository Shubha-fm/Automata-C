/* Program 192: Count accepted binary words using matrix exponentiation. ISO C11. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MOD 1000000007ULL
typedef struct {unsigned long long a[2][2];} Matrix;
static Matrix multiply(Matrix a,Matrix b){
    Matrix c={{{0,0},{0,0}}};
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)
            c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%MOD;
    return c;
}
int main(int argc,char **argv){
    if(argc!=2){fprintf(stderr,"Usage: %s NONNEGATIVE_LENGTH\n",argv[0]);return 2;}
    errno=0;char *end;
    unsigned long long len=strtoull(argv[1],&end,10);
    if(errno||end==argv[1]||*end||argv[1][0]=='-'){
        fprintf(stderr,"Invalid length\n");return 2;
    }
    /* Two states for parity of 1s. Every state has one 0 edge
       to itself and one 1 edge to the other parity state. */
    Matrix base={{{1,1},{1,1}}},result={{{1,0},{0,1}}};
    while(len){
        if(len&1ULL)result=multiply(result,base);
        base=multiply(base,base);len>>=1;
    }
    printf("ACCEPTED_MOD=%llu\n",result.a[0][0]);
    return 0;
}
