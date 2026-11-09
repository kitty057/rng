#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <ctype.h>
__uint128_t statfilesize(const char *fin);
__uint128_t rng(const __uint128_t, const __uint128_t u);
__uint128_t rbr(void);
typedef struct rbi  {
    const char *(*imn)(void); //r, imn implementation number.
    __uint128_t (*rand)(void); //r
    void (*stir)(void); //o
    __uint128_t (*un)(const __uint128_t u); //o; def imp used if null. 
    void (*buf)(void* const bf, const size_t si); //r, bf buffer, si size, u upper bound.
    int  (*clo)(void); //o
} rbi;
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
    // putchar('\n'); // uncomment if you want a newline after the number.
}
static __uint128_t srngf(void) {
    __uint128_t r;
    // linux getrandom syscall
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
__uint128_t rng(const __uint128_t low, const __uint128_t high) {
    __uint128_t range = high - low + 1;
    __uint128_t threshold = ((__uint128_t)-1 - range + 1) % range;
    __uint128_t something_else;
    __uint128_t rita;
    if (imm->un!=NULL) {
        return imm->un(high);
    }
    if (high < low) {
        printf("high < low. fix it.");
        printf("\n");
        exit(48);
    }
    something_else=((__uint128_t)+~high)%high; // 2^128-1 mod max, aka high.
    do {
        rita=rbr();
    } while (rita < threshold);
    return (rita%range)+low;
}
int32_t main(int argc,char **argv) {
    /* 18-9-20-1 or 189201 is rita's name in A1Z26, and my primary exit code. */
    /* this integer is kinda just here for aesthetics though. it doesn't really do much.*/
    __uint128_t ritaExclamationMarkHere = 18+9+20+1;
    __uint128_t UINT128_MAX = (__uint128_t)-1;
    if (argc<3) {
        printf("cannot run without args\n");
        exit(48);
    }
    __uint128_t high=strtou128(argv[2]);
    __uint128_t low=strtou128(argv[1]);
    if (low<=0||low>=UINT128_MAX) {
        printf("low was a funky number or a string, change it. low was '");
        printf128(low);
        printf("'\n");
        exit(48);
    }
    if (high<=0||high>=UINT128_MAX) {
        printf("max was a funky number or a string, change it. max was '");
        printf128(high);
        printf("'\n");
        exit(48);
    }
    printf128(rng(low, high));
    printf("\n");
    return 0;
}
