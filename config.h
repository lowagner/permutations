#pragma once

#include <gmpxx.h>
#include <stdint.h>
#include <iostream>
#include <vector>

#define MAX_PERMUTATION_SIZE 256

#if MAX_PERMUTATION_SIZE <= 1
#error "Permutations should be bigger."
#elif MAX_PERMUTATION_SIZE <= 256
typedef uint8_t Index;
#elif MAX_PERMUTATION_SIZE <= 65536
typedef uint16_t Index;
#elif MAX_PERMUTATION_SIZE <= 4294967296
typedef uint32_t Index;
#else
#error "Permutations this big will probably run you out of memory."
typedef uint64_t Index;
#endif

void warn(const char *c);

typedef enum {
    Done,
    NotDone
} MaybeDone;

typedef mpz_class BigInt;

const char *firstNonSpace(const char *c);
const char *matchUpTo(const char *c, const char *format);
   
std::ostream &operator << (std::ostream &os, const std::vector<Index> &p);
