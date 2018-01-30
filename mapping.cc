#include "mapping.h"

Mapping::~Mapping() {}

Int Mapping::size() const {
    throw std::logic_error("shouldn't call base class Mapping size()");
}

Index Mapping::operator [] (Int i) const {
    throw std::logic_error("shouldn't call base class Mapping operator []");
}

Index Mapping::operator () (Int i) const {
    throw std::logic_error("shouldn't call base class Mapping operator ()");
}

bool Mapping::operator == (const Mapping &other) const {
    Int N = size();
    if (N != other.size())
        return false;
    for (Int i=0; i<N; ++i)
        if ((*this)[i] != other[i])
            return false;
    return true;
}

bool Mapping::operator != (const Mapping &other) const {
    Int N = size();
    if (N != other.size())
        return true;
    for (Int i=0; i<N; ++i)
        if ((*this)[i] != other[i])
            return true;
    return false;
}
