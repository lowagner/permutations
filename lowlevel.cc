#include "lowlevel.h"

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

char firstNonSpace(const char *&c) {
    while (*c == ' ' or *c == '\t' or *c == '\n')
        ++c;
    return *c;
}

void matchUpTo(const char *&c, const char *format) {
    const char *original_c = c;
    firstNonSpace(c);
    firstNonSpace(format);
    while (*format) {
        if (*c++ != *format++) {
            c = original_c;
            throw std::invalid_argument("does not match here.");
        }
    }
}

Int getIntegerFromString(const char *&c) {
    firstNonSpace(c);
    const char *original_c = c;
    Int value = 0;
    bool seen_numbers = false;
    while (true) {
        switch (*c) {
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
                seen_numbers = true;
                value *= 10;
                value += (*c)-'0';
                break;
            default:
                if (seen_numbers)
                    return value;
                c = original_c;
                throw std::invalid_argument("expected a number");
        }
        ++c;
    }
}

void getArrayFromString(std::vector<Index> &trial, const char *&c) {
    const char *original_c = c;
    matchUpTo(c, "{");
    if (firstNonSpace(c) == '}')
        return;
    while (true) {
        try {
            Int value = getIntegerFromString(c);
            trial.push_back(value);
        } catch (std::exception &e) {
            c = original_c;
            throw std::invalid_argument("no next integer");
        }
        switch (firstNonSpace(c)) {
            case 0:
                c = original_c;
                throw std::invalid_argument("not an array, no closing bracket");
            case '}':
                ++c;
                return;
            case ',':
                ++c;
        }
    }
}

std::ostream &operator << (std::ostream &os, const std::vector<Index> &p) {
    if (!p.size())
        return os << "{}";
    os << "{" << (Int)p[0];
    for (int i=1; i<p.size(); ++i)
        os << ", " << (Int)p[i];
    return os << "}";
}
