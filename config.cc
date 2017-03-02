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
