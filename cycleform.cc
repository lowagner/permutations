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

Cycle::Cycle(const char *s) {
    if (fromString(s) == nullptr)
        throw std::invalid_argument("bad initializer for cycle");
}

std::ostream &operator << (std::ostream &os, const Cycle &p) {
    return os << p.array;
}

const char *Cycle::fromString(const char *s) {
    std::vector<Index> trial;
    if (!(s=getArrayFromString(trial, s)))
        return nullptr;
    array = trial;
    return s;
}

void Cycle::push(Index value) {
    array.push_back(value);
}

Index Cycle::pop() {
    Index result = array[array.size()-1];
    array.pop_back();
    return result;
}
