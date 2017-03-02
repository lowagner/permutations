#include "permutations.h"
#include <algorithm>
#include <iostream>

Permutation::Permutation(Int N) {
    setSize(N);
    for (Int i=0; i<N; ++i)
        array.push_back(i);
}

Permutation::Permutation(const std::vector<Index> &a) {
    fromVector(a);
}

Permutation::Permutation(const char *c) {
    if (fromString(c) == nullptr)
        throw std::invalid_argument("bad initializer string for Permutation");
}

Int Permutation::size() const {
    return array.size();
}

std::ostream &operator << (std::ostream &os, const Permutation &p) {
    return os << "Permutation(" << p.array << ")";
}
 
void Permutation::fromVector(const std::vector<Index> &a) {
    const Int N = a.size();
    setSize(N);
    for (Int i=0; i<N; ++i) {
        array.push_back(0);
        if (a[i] >= N) 
            throw std::out_of_range("invalid vector with which to initialize Permutation");
    }
    for (Int i=0; i<N; ++i) {
        if (array[a[i]] == 0)
            array[a[i]] = 1;
        else
            throw std::logic_error("multiple inputs map to the same output, invalid Permutation");
    }
    for (Int i=0; i<N; ++i)
        array[i] = a[i];
}

const char *Permutation::fromString(const char *c) {
    c = matchUpTo(c, "Permutation({");
    if (!c)
        return nullptr;
    Int value = 0;
    bool seen_numbers = false;
    bool seen_space = false;
    std::vector<Index> trial;
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
    if (*++c != ')')
        return nullptr;
    // expect one last number
    if (!seen_numbers)
        return nullptr;
    trial.push_back(value);
    fromVector(trial);
    return ++c;
}

void Permutation::fromOrder(BigInt o) {
    std::vector<Index> indicesToRemainingIndices;
    const Int N = array.size();
    indicesToRemainingIndices.reserve(N);
    for (Int i=0; i<N; ++i)
        indicesToRemainingIndices.push_back(0);
    for (Int f=2; f<=N; ++f) {
        Int i = N - f;
        BigInt index = o % f;
        o /= f;
        indicesToRemainingIndices[i] = index.get_ui(); // safely between 0 and f-1.
    }

    std::vector<Index> remainingIndices;
    remainingIndices.reserve(N);
    for (Int i=0; i<N; ++i)
        remainingIndices.push_back(i);
    for (Int i=0; i<N; ++i) {
        Int index = indicesToRemainingIndices[i];
        array[i] = remainingIndices[index];
        remainingIndices.erase(remainingIndices.begin()+index, remainingIndices.begin()+index+1);
    }
}

BigInt Permutation::order() const {
    // give the number in [0, array.size()!) (Factorial) which corresponds to this Permutation
    std::vector<Index> remainingIndices;
    const Int N = array.size();
    remainingIndices.reserve(N);
    BigInt result = 0;
    BigInt factorial = 1;
    if (array[0] == 0) { // special case so as not to multiply one final factorial multiplicand
        for (Int i=2; i<N-1; ++i)
            factorial *= i;
        for (Int i=1; i<N; ++i)
            remainingIndices.push_back(i);
    } else {
        for (Int i=2; i<N; ++i)
            factorial *= i;
        result += array[0]*factorial;
        factorial /= N-1;
        for (Int i=0; i<array[0]; ++i)
            remainingIndices.push_back(i);
        for (Int i=array[0]+1; i<N; ++i)
            remainingIndices.push_back(i);
    }
    for (Int i=1; i<N-1; ++i) {
        // find index of array[i] in remainingIndices
        Int find = array[i];
        Int lo = 0, hi = remainingIndices.size();
        while (lo + 1 < hi) {
            Int mid = (lo + hi)/2;
            if (remainingIndices[mid] > find)
                hi = mid;
            else
                lo = mid;
        }
        if (remainingIndices[lo] != find) {
            std::cerr << "remaining indices  " << remainingIndices << "\n";
            std::cerr << " at index " << lo << " we have " << (Int)remainingIndices[lo] << ", expected " << find << "\n";
            throw std::out_of_range("Permutation elements don't make sense, maybe some repeats.");
        }
        remainingIndices.erase(remainingIndices.begin()+lo, remainingIndices.begin()+lo+1);
        // the index corresponds to how much multiplication the factorial needs:
        result += lo*factorial;
        factorial /= N-i-1;
    }
    return result;
}

Index Permutation::operator [] (Int i) const {
    return array.at(i); // bounds checking, throws error if outside
}

Index Permutation::operator () (Int i) const {
    const Int N = array.size();
    return array[((i%N)+N)%N]; // puts it into bounds
}

void Permutation::swap(Int i, Int j) {
    std::swap(array.at(i), array.at(j));
}

Permutation Permutation::operator () (const Permutation &other) const {
    Int N = size();
    if (N != other.size())
        throw std::out_of_range("unmatched Permutation sizes, cannot compose");
    Permutation p(2);
    p.setSize(N);
    for (Int i=0; i<N; ++i)
        p.array.push_back(array[other.array[i]]);
    return p;
}

bool Permutation::operator == (const Permutation &other) const {
    return (array == other.array);
}

bool Permutation::operator != (const Permutation &other) const {
    return (array != other.array);
} 

Permutation Permutation::next() const {
    Permutation theNext = *this;
    theNext.makeNext();
    return theNext;
}

MaybeDone Permutation::makeNext() {
    Int i = array.size()-2;
    // find first "inversion" from the end of the array.
    // an inversion happens when array[i] < array[i+1].
    if (array[i] < array[i+1]) {
        std::swap(array[i], array[i+1]);
        return NotDone;
    }
    while (true) {
        if (--i < 0) {
            // full backwards sequence, reverse it all.
            reverseFromIndexOn(0);
            return Done; // indicate we've gone through all permutations
        }
        if (array[i] < array[i+1])
            break;
    }
    // array[i] < array[i+1], but array[i+1] and beyond is sorted in decreasing way.
    reverseFromIndexOn(i+1);
    Index j = findNextLargestValueFromIndexOn(array[i], i+1);
    std::swap(array[i], array[j]);
    return NotDone;
}

void Permutation::setSize(Int N) {
    array.clear();
    if (N < 2)
        throw std::out_of_range("permutation is nonexistent or trivial -- boring!");
    if (N > MAX_PERMUTATION_SIZE)
        throw std::out_of_range("can't make Permutation that big");
    array.reserve(N);
}

Index Permutation::findValueFromIndexOn(Index value, Index index) const {
    Int last = array.size();
    while (index + 1 < last) {
        Int mid = (index+last)/2;
        if (array[mid] < value)
            index = mid;
        else
            last = mid;
    }
    return index;
};

Index Permutation::findNextLargestValueFromIndexOn(Index value, Index index) const {
    index = findValueFromIndexOn(++value, index);
    if (array[index] >= value)
        return index;
    if (++index >= array.size())
        throw std::out_of_range("couldn't find next largest");
    return index;
}

void Permutation::reverseFromIndexOn(Index index) {
    Int start = index-1;
    Int last = array.size();
    while (++start < --last){
        std::swap(array[start], array[last]);
    }
}
