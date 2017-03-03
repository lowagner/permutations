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

const char *firstNonSpace(const char *c);
const char *matchUpTo(const char *c, const char *format);
   
std::ostream &operator << (std::ostream &os, const std::vector<Index> &p);
const char *getArrayFromString(std::vector<Index> &trial, const char *c);

class Mapping {
public:
    virtual Int size() const;
    virtual Index operator [] (Int i) const;
    virtual Index operator () (Int i) const;
    
    bool operator == (const Mapping &other) const;
    bool operator != (const Mapping &other) const;
};
