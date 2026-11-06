#ifndef CCF_H
#define CCF_H
#include <stddef.h>
#include <stdint.h>
__uint128_t statfilesize(const char *fin);
__uint128_t rng(const __uint128_t u);
__uint128_t rbr(void);
typedef struct rbi  {
    const char *(*imn)(void); // required, imn = implementation number.
    __uint128_t (*rand)(void); // required
    void (*stir)(void); // optional
    __uint128_t (*un)(const __uint128_t u); // optinal; default implication used if null. 
    void (*buf)(void* const bf, const size_t si); // required, bf = buffer, si = size, u = max.
    int  (*clo)(void); // optional
} rbi;
#endif
