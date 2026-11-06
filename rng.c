#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <ccf.h>
#include <ctype.h>
__uint128_t strtou128(const char *in) {
    __uint128_t out = 0;
    // omit leading whitespace.
    while (isspace((unsigned char)*in))in++;
    // transubstantiate string into __uint128_t.
    while (isdigit((unsigned char)*in)) {
        out = (out*10)+(*in- '0');
        in++;
    }
    return out;
}
void printf128(__uint128_t input) {
    if (input == 0) {
        printf("0");
        return;
    }
    char bf[40]; // 39 char max for 2^128 - 1.
    int placeholder = 0;
    while (input > 0) {
        bf[placeholder++] = (char)((input%10)+'0');
        input /= 10;
    }
    // print buffer in reverse.
    while (placeholder > 0) {
        putchar(bf[--placeholder]);
    }
    // putchar('\n');
}
static __uint128_t srngf(void) {
    __uint128_t r;
    // lin getrandom syscall
    if (getrandom(&r, sizeof(r), 0)!=sizeof(r)) {
        perror("failed for some reason sorry");
        exit(48);
    }
    return r;
}
static void sbf(void* const bf, const size_t si) {
    if (getrandom(bf,si,0)!=(ssize_t)si) {
        perror("");
        exit(48);
    }
}
static const rbi srng={
    .imn = NULL, //o
    .rand = srngf,
    .stir = NULL, //o
    .un = NULL, //o
    .buf = sbf,
    .clo = NULL //o
};
static const rbi *imm=&srng;
__uint128_t rbr(void) {
    return imm->rand();
}
__uint128_t rng(const __uint128_t u) {
    __uint128_t m;
    __uint128_t r;
    if (imm->un!=NULL) {
        return imm->un(u);
    }
    if (u < 2) {
        return 0;
    }
    m=((__uint128_t)+~u)%u; // 2^128-1 mod max, u.
    do {
        r=rbr();
    } while (r < m);
    return r%u;
}
int32_t main(int argc,char **argv) {
    __uint128_t UINT128_MAX = (__uint128_t)-1;
    if (argc<2) {
        printf("cannot run without args\n");
        exit(2);
    }
    __uint128_t max=strtou128(argv[1]);
    if (max<=0||max>=UINT128_MAX) {
        printf("max was a funky number or a string, change it. max was '");
        printf128(max);
        printf("'\n");
        exit(3);
    }
    printf128(rng(max+1));
    printf("\n");
    return 0;
}
