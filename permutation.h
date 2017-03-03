#pragma once
#include "mapping.h"

class Permutation : public Mapping {
private:
    std::vector<Index> array;

public:
    Permutation(Int N=MAX_PERMUTATION_SIZE);
    Permutation(const std::vector<Index> &a);
    Permutation(const char *&c);
    Permutation(const char *&&c);

    friend std::ostream &operator << (std::ostream &os, const Permutation &p);
    
    void fromVector(const std::vector<Index> &a);
    void fromString(const char *&s);
    void fromOrder(BigInt o);
    BigInt order() const;

    Index operator [] (Int i) const;
    Index operator () (Int i) const;
    
    void swap(Int i, Int j);

    Permutation operator () (const Mapping &other) const;
    
    Permutation next() const;
    MaybeDone makeNext();

    Int size() const;
private:
    void setSize(Int N);
    void reverseFromIndexOn(Index index);
    Index findValueFromIndexOn(Index value, Index index) const;
    Index findNextLargestValueFromIndexOn(Index value, Index index) const;
};
