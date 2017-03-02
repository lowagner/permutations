#pragma once
#include "config.h"

class Permutation
{
private:
    std::vector<Index> array;

    void setSize(Int N);
    void reverseFromIndexOn(Index index);
    Index findValueFromIndexOn(Index value, Index index) const;
    Index findNextLargestValueFromIndexOn(Index value, Index index) const;

public:
    Permutation(Int N=MAX_PERMUTATION_SIZE);
    Permutation(const std::vector<Index> &a);
    Permutation(const char *c);

    friend std::ostream &operator << (std::ostream &os, const Permutation &p);
    Int size();
    
    void fromVector(const std::vector<Index> &a);
    const char *fromString(const char *s);
    void fromOrder(BigInt o);
    BigInt order();

    Index operator [] (Int i);
    Index operator () (Int i);

    void swap(Int i, Int j);

    bool operator == (const Permutation &other);
    bool operator != (const Permutation &other);
    
    Permutation next();
    MaybeDone makeNext();
};
