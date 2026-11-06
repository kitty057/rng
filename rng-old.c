// this version of `rng` is compatible with windows if the correct compilation steps are followed.
#define SODIUM_STATIC
#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc,char **argv) {
    if (argc < 2) {
        printf("can't run without args\n");
        exit(48);
    }
    if (sodium_init() < 0) {
        printf("sodium didn't initialise\n");
        exit(48);
    }
    char *r;
    unsigned int max = strtol(argv[1],&r,0);
    if (max <= 0) {
        printf("max cannot be zero, UINT32_MAX, or a negative number. it was '%d'",max);
        exit(48);
    }
    printf("%d\n",randombytes_uniform((uint32_t)max+1));
    return 0;
}
