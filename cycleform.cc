#include "cycleform.h"
#include <algorithm>
#include <iostream>

Cycle::Cycle() {
}

Cycle::Cycle(Index index) {
    array.push_back(index);
}

Cycle::Cycle(std::vector<Index> &a) {
    array = a;
}
    
Cycle::Cycle(const char *&s) {
    fromString(s);
}

Cycle::Cycle(const char *&&s) {
    fromString(s);
}

std::ostream &operator << (std::ostream &os, const Cycle &p) {
    return os << p.array;
}

void Cycle::fromString(const char *&s) {
    std::vector<Index> trial;
    getArrayFromString(trial, s);
    array = trial;
}
    
Index Cycle::operator [] (Int i) {
    return array.at(i); // bounds checking
}

Index Cycle::operator () (Int i) {
    Int N=array.size();
    return array[((i%N)+N)%N];
}

void Cycle::push(Index value) {
    array.push_back(value);
}

Index Cycle::pop() {
    Index result = array[array.size()-1];
    array.pop_back();
    return result;
}
    
Int Cycle::size() const {
    return array.size();
}

Cycle::iterator Cycle::begin()  {
    return array.begin();
}

Cycle::iterator Cycle::end() {
    return array.end();
}

// end Cycle
// start CycleForm

CycleForm::CycleForm(Int N) {
    setSize(N);
}

CycleForm::CycleForm(const std::vector< std::vector<Index> > &a) {
    fromVectorVector(a);
}

CycleForm::CycleForm(const char *&c) {
    fromString(c);
}

CycleForm::CycleForm(const char *&&c) {
    fromString(c);
}

void CycleForm::fromVectorVector(const std::vector< std::vector<Index> > &vectorvector) {
    Int N = 0;
    for (auto cycle : vectorvector)
        for (auto index : cycle) {
            if (index+1 > N)
                N = index+1;
        }
    setSize(N);
    for (auto cycle : vectorvector)
        if (cycle.size())
            cycles.push_back(Cycle(cycle));
    validate();
}

void CycleForm::fromString(const char *&c) {
    std::vector< std::vector<Index> > a;
    // TODO
    fromVectorVector(a);
}
 
Index CycleForm::operator [] (Int i) const {
    if (i < 0 || i >= _size)
        throw std::out_of_range("bad index in CycleForm");
    return get(i);
}

Index CycleForm::operator () (Int i) const {
    return get(((i%_size)+_size)%_size);
}

Index CycleForm::get(Index i) const {
    // brute force it for now.  TODO sort cycles in some smart way.
    for (auto cycle : cycles)
        for (Int j; j<cycle.size(); ++j) {
            if (cycle[j] == i) {
                if (j+1 >= cycle.size())
                    return cycle[0];
                else
                    return cycle[j+1];
            }
        }
    // if we couldn't find it in the cycles list, it is a fixed point.
    return i;
}

Int CycleForm::size() const {
    return _size;
}

void CycleForm::setSize(Int N) {
    if (N <= 0)
        throw std::invalid_argument("non-positive size for CycleForm");
    cycles.clear();
    _size = N;    
}

void CycleForm::validate() {
    std::vector<Index> values;
    values.reserve(_size);
    for (int i=0; i<_size; ++i)
        values.push_back(0);
    Int total = 0;
    Int cycle_index = 0;
    while (cycle_index < cycles.size()) {
        for (auto i : cycles[cycle_index]) {
            if (values.at(i) == 0) // check bounds here
                values[i] = 1;
            else
                throw std::invalid_argument("CycleForm invalid, repeated numbers");
            ++total;
        }
    }
}
