/* Program 260: Construct the inverse image of a DFA under a binary-word homomorphism. ISO C11. */
#include "../include/dfa_io.h"
static int validate_image(const char *s) {
    if (strcmp(s,"e")==0)return 1;
    size_t n=strlen(s);
    if (n==0||n>128)return 0;
    for (size_t i=0;i<n;i++)if (s[i]!='0'&&s[i]!='1')return 0;
    return 1;
}
int main(int argc,char **argv) {
    if (argc!=4) {
        fprintf(stderr,"Usage: %s MODEL.dfa IMAGE_OF_0 IMAGE_OF_1\n",argv[0]);
        return 2;
    }
    DFA d;
    if (!dfa_read(argv[1],&d)) { fprintf(stderr,"Invalid DFA file\n");return 2; }
    if (!validate_image(argv[2])||!validate_image(argv[3])) {
        fprintf(stderr,"Images must be nonempty binary words or e for epsilon, max 128\n");
        return 2;
    }
    DFA out=d;
    for (int q=0;q<d.n;q++) for (int bit=0;bit<2;bit++) {
        const char *image=argv[bit+2];
        int state=q;
        if (strcmp(image,"e")!=0)
            for (const char *p=image;*p;p++)
                state=d.go[state][*p-'0'];
        out.go[q][bit]=state;
    }
    dfa_write(&out);return 0;
}
