#define SODIUM_STATIC
#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char **argv) {
    if (argc<2) {
        printf("cannot run without args\n");
        exit(2);
    }
    if (sodium_init()<0) {
        printf("sodium didnt initialise\n");
        exit(1);
    }
    char *e;
    long max=strtol(argv[1],&e,10);
    if (max<=0) {
        printf("max cannot be zero. max was %lu\n",max);
        exit(3);
    }
    printf("%u\n",randombytes_uniform((uint32_t)max+1));
    return 0;
}
