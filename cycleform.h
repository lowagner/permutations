#pragma once
#include "mapping.h"
#include "permutation.h"

class Cycle {
private:
    std::vector<Index> array;

public:
    Cycle();
    Cycle(Index index);
    Cycle(const std::vector<Index> &a);
    Cycle(const char *&c);
    Cycle(const char *&&c);

    friend std::ostream &operator << (std::ostream &os, const Cycle &p);
    
    void fromVector(const std::vector<Index> &a);
    void fromString(const char *&s);

    Index operator [] (Int i) const;
    Index operator () (Int i) const;

    void push(Index value);
    Index pop();
    Int size() const;

    typedef std::vector<Index>::iterator iterator;
    iterator begin();
    iterator end();
    typedef std::vector<Index>::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
};

class CycleForm : public Mapping {
private:
    std::vector<Cycle> cycles;
    Int _size;

public:
    CycleForm(Int N=MAX_PERMUTATION_SIZE);
    CycleForm(const Mapping &p);
    CycleForm(const Cycle &c);
    CycleForm(const std::vector< std::vector<Index> > &a);
    CycleForm(const char *&c);
    CycleForm(const char *&&c);

    friend std::ostream &operator << (std::ostream &os, const CycleForm &p);
    
    void fromVectorVector(const std::vector< std::vector<Index> > &vectorvector);
    void fromString(const char *&s);

    Index operator [] (Int i) const;
    Index operator () (Int i) const;
    
    void swap(Int i, Int j);

    CycleForm operator () (const Mapping &other) const;
    
    typedef std::vector<Cycle>::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

    Int size() const;
private:
    void setSize(Int N);
    void validate();
    
    Index get(Index i) const;
};

