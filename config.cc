#include "config.h"

#if DEBUG >= 2
class Warning : public std::exception {
    virtual const char* what() const throw() {
        return "Warning is an error.\n";
    }
};

void warn(const char *c) {
    std::cerr << "WarningError: " << c << "\n";
    throw Warning();
}
#else
void warn(const char *c) {
    std::cerr << "Warning: " << c << "\n";
}
#endif

const char *firstNonSpace(const char *c) {
    while (*c == ' ' or *c == '\t' or *c == '\n')
        ++c;
    return c;
}

const char *matchUpTo(const char *c, const char *format) {
    c = firstNonSpace(c);
    format = firstNonSpace(format);
    while (*format) {
        if (*c++ != *format++)
            return nullptr;
    }
    return c;
}

std::ostream &operator << (std::ostream &os, const std::vector<Index> &p) {
    if (!p.size())
        return os << "{}";
    os << "{" << (int)p[0];
    for (int i=1; i<p.size(); ++i)
        os << ", " << (int)p[i];
    return os << "}";
}

const char *getArrayFromString(std::vector<Index> &trial, const char *c) {
    if (!(c=matchUpTo(c, "{")))
        return nullptr;
    Int value = 0;
    bool seen_numbers = false;
    bool seen_space = false;
    while (*c != '}') {
        if (*c == 0)
            return nullptr;
        switch (*c) {
            case '\t':
            case '\n':
            case ' ':
                seen_space = true;
                break; 
            case ',':
                if (!seen_numbers || value >= MAX_PERMUTATION_SIZE)
                    return nullptr;
                trial.push_back(value);
                value = 0;
                seen_numbers = false;
                seen_space = false;
                break; 
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (seen_space and seen_numbers)
                    return nullptr;
                seen_numbers = true;
                seen_space = false;
                value *= 10;
                value += (*c)-'0';
                break;
            default:
                return nullptr;
        }
        ++c;
    }
    // expect one last number
    if (!seen_numbers)
        return nullptr;
    trial.push_back(value);
    return ++c;
}

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
