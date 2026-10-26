#include <sodium.h>
int main(int argc,char *argv[0]) {
    if (argc<2) {
        printf("cannot run without args\n");
        exit(2);
    }
    if (sodium_init()<0) {
        return 0;
        exit(1);
    }
    int max=atoi(argv[1]);
    if (max<=0) {
        printf("max cannot be zero. max was %d\n",max);
        exit(0);
    }
    printf("%d\n",randombytes_uniform((uint32_t)max+1));
    return 0;
}
