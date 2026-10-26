#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sodium.h>
int rng(int max) {
    return rand() % max;
}
int main(int argc,char *argv[0]) {
    if (sodium_init<0) {
        // init fail
        return 0;
        exit(1);
    }
    srand((unsigned int)time(NULL));
    int max=atoi(argv[1]);
    uint64_t randV = randombytes_random(max);
    if (max==0) {
        printf("max cannot be zero. max was %d",max);
        exit(0);
    }
    int randN = rand()%max+1;
    printf("%d\n",randV);
    return 0;
}
