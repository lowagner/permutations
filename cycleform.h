#pragma once
#include "mapping.h"

class Cycle {
private:
    std::vector<Index> array;

public:
    Cycle();
    Cycle(Index index);
    Cycle(std::vector<Index> &a);
    Cycle(const char *c);
    
    friend std::ostream &operator << (std::ostream &os, const Cycle &p);
    
    const char *fromString(const char *s);

    void push(Index value);
    Index pop();
};

class CycleForm : public Mapping {
private:
    std::vector<Cycle> cycles;
    Int _size;

    void push(Cycle &c);
public:
    CycleForm(Int N=MAX_PERMUTATION_SIZE);
    CycleForm(const std::vector< std::vector<Index> > &a);
    CycleForm(const char *c);

    friend std::ostream &operator << (std::ostream &os, const CycleForm &p);
    Int size() const;
    
    void fromVector(const std::vector<Index> &a);
    const char *fromString(const char *s);

    Index operator [] (Int i) const;
    Index operator () (Int i) const;
    
    void swap(Int i, Int j);

    CycleForm operator () (const CycleForm &other) const;
};

