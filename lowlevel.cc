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

void firstNonSpace(const char *&c) {
    while (*c == ' ' or *c == '\t' or *c == '\n')
        ++c;
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

void getArrayFromString(std::vector<Index> &trial, const char *&c) {
    const char *original_c = c;
    matchUpTo(c, "{");
    Int value = 0;
    bool seen_numbers = false;
    bool seen_space = false;
    while (*c != '}') {
        if (*c == 0) {
            c = original_c;
            throw std::invalid_argument("not an array, no closing bracket");
        }
        switch (*c) {
            case '\t':
            case '\n':
            case ' ':
                seen_space = true;
                break; 
            case ',':
                if (!seen_numbers || value >= MAX_PERMUTATION_SIZE) {
                    c = original_c;
                    throw std::invalid_argument("no number between two commas");
                }
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
                if (seen_space and seen_numbers) {
                    c = original_c;
                    throw std::invalid_argument("two numbers separated by space, no comma");
                }
                seen_numbers = true;
                seen_space = false;
                value *= 10;
                value += (*c)-'0';
                break;
            default:
                c = original_c;
                throw std::invalid_argument("unrecognized character; not a number, space, brace, or comma");
        }
        ++c;
    }
    // expect one last number
    if (!seen_numbers) {
        c = original_c;
        throw std::invalid_argument("needed one last number after last comma, before brace");
    }
    trial.push_back(value);
    c++;
}

std::ostream &operator << (std::ostream &os, const std::vector<Index> &p) {
    if (!p.size())
        return os << "{}";
    os << "{" << (int)p[0];
    for (int i=1; i<p.size(); ++i)
        os << ", " << (int)p[i];
    return os << "}";
}
