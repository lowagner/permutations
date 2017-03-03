#pragma once
#include "config.h"

class Permutation : public Mapping {
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
    Int size() const;
    
    void fromVector(const std::vector<Index> &a);
    const char *fromString(const char *s);
    void fromOrder(BigInt o);
    BigInt order() const;

    Index operator [] (Int i) const;
    Index operator () (Int i) const;
    
    void swap(Int i, Int j);

    Permutation operator () (const Permutation &other) const;
    
    Permutation next() const;
    MaybeDone makeNext();
};
