#pragma once
#include "config.h"

class Permutation
{
private:
    std::vector<Index> array;

    void setSize(int N);
    void reverseFromIndexOn(Index index);
    Index findValueFromIndexOn(Index value, Index index) const;
    Index findNextLargestValueFromIndexOn(Index value, Index index) const;

public:
    Permutation(int N=MAX_PERMUTATION_SIZE);
    Permutation(const std::vector<Index> &a);
    Permutation(const char *c);

    friend std::ostream &operator << (std::ostream &os, const Permutation &p);
    int size();
    
    void fromVector(const std::vector<Index> &a);
    const char *fromString(const char *s);
    void fromOrder(BigInt o);
    BigInt order();

    bool operator == (const Permutation &other);
    bool operator != (const Permutation &other);
    
    Permutation next();
    MaybeDone makeNext();
};
