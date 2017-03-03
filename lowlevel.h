#pragma once
#include "config.h"

#include <gmpxx.h>
#include <stdint.h>
#include <iostream>
#include <vector>

#if MAX_PERMUTATION_SIZE <= 1
#error "Permutations should be bigger."
#elif MAX_PERMUTATION_SIZE <= 256
typedef uint8_t Index;
typedef uint_fast8_t Uint;
typedef int_fast16_t Int;
#elif MAX_PERMUTATION_SIZE <= 65536
typedef uint16_t Index;
typedef uint_fast16_t Uint;
typedef int_fast32_t Int;
#elif MAX_PERMUTATION_SIZE <= 4294967296
typedef uint32_t Index;
typedef uint_fast32_t Uint;
typedef int_fast64_t Int;
#else
#error "Permutations this big will probably run you out of memory."
#endif

void warn(const char *c);

typedef enum {
    Done,
    NotDone
} MaybeDone;

typedef mpz_class BigInt;

void firstNonSpace(const char *&c);
void matchUpTo(const char *&c, const char *format);
void getArrayFromString(std::vector<Index> &trial, const char *&c);

std::ostream &operator << (std::ostream &os, const std::vector<Index> &p);
