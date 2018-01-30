#include "permutation.h"
#include "cycleform.h"

#define TEST(x) try { \
    test##x(); \
} catch (std::exception &e) { \
    std::cerr << "test"#x" failed\n" << e.what() << "\n"; return 1; \
} \
std::cout << "test"#x" passed\n";

#define TESTSHOULDFAIL(x) try { \
    test##x(); \
    std::cerr << "test"#x" FAILED.  it executed without error; when it should have thrown an exception.\n"; return 1; \
} catch (std::exception &e) { \
    std::cerr << "test"#x" passed, as it threw an exception (and it was supposed to).\n";\
}

class TestError : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Test Failed\n";
    }
};

void error(const char *c) {
    std::cerr << "TestError: " << c << "\n";
    throw TestError();
}

void testCopy() {
    Permutation p({0, 1, 3, 2, 5, 4});
    std::cout << "p = " << p << "\n";
    Permutation q = p;
    std::cout << "q = " << q << "\n";
    if (p != q)
        error("expected p == q.\n");
    q.makeNext();
    std::cout << "now q = " << q << "\n";
    if (p == q)
        error("expected two different permutations.\n");
}

void testNextWithSize(int N) {
    Permutation p(N);
    int n = N;
    if (N < 6) {
        for (int i=2; i<N; ++i)
            n *= i;
    }
    int i=0;
    std::cout << p << "\n";
    for (; i<2*n; ++i) {
        if (p.makeNext() == Done)
            break;
        else if (N == 4)
            std::cout << p << "\n";
    }
    if (N < 6) {
        if (i > n)
            error("expected permutations to be Done before this happened");
    } else {
        if (i < N)
            error("expected permutations to be NotDone up to this point");
    }
}

void testNext() {
    for (int N=2; N<7; ++N) {
        try {
            testNextWithSize(N);
        } catch (std::exception &e) {
            std::cerr << "had problems at N = " << N << ": \n" << e.what() << "\n";
            throw TestError();
        }
    }
}

void testVector() {
    Permutation p({0, 1, 3, 2, 5, 4});
    std::cout << p << "\n";
}

void testVectorRepeatNumbersFail() {
    Permutation p({0, 1, 3, 3, 2, 5, 4});
    std::cout << p << "\n";
}

void testVectorMissingNumber() {
    Permutation p({0, 1, 7, 3, 2, 5, 4});
    std::cout << p << "\n";
}

void testString() {
    Permutation p("Permutation({5, 3, 4, 2, 1, 0}) ");
    std::cout << p << "\n";
    if (p.size() != 6)
        error("expected 6 elements in this permutation");
}

void testStringLeadingSpace() {
    Permutation p(" \n \t Permutation(\n{5, 3, 4, 2, 6, 1, 0} )");
    std::cout << p << "\n";
    if (p.size() != 7)
        error("expected 7 elements in this permutation");
}

void testStringExtraCommaFail() {
    Permutation p("Permutation({5, 4, 0, 3, 2, 1,})");
    std::cout << p << "\n";
}

void testStringRepeatCommasFail() {
    Permutation p("Permutation({5, 4,, 3, 2, 1})");
    std::cout << p << "\n";
}

void testStringRepeatNumbersFail() {
    Permutation p("Permutation({5, 5, 4 3, 2, 1, 0})");
    std::cout << p << "\n";
}

void testStringSpaceBetweenNumbersFail() {
    Permutation p("Permutation({5, 5, 4 3, 2, 1, 0})");
    std::cout << p << "\n";
}

void testStringUnclosedBracesFail() {
    Permutation p("Permutation({5, 5, 4 3, 2, 1, 0)");
    std::cout << p << "\n";
}

void testStringUnclosedBracketsFail() {
    Permutation p("Permutation({5, 5, 4 3, 2, 1, 0}");
    std::cout << p << "\n";
}

void testStringMultiple() {
    const char *s =  "\n \t Permutation({3, 2, 4, 1, 0})Permutation({1, 0})";
    Permutation p(s);
    Permutation q(s);
    std::cout << p << "\n";
    std::cout << q << "\n";
    if (p.size() != 5 or q.size() != 2)
        error("expected different numbers of elements in these permutations");
}

void testOrder() {
    Permutation p({1, 2, 3, 0, 4, 5});
    BigInt o = p.order();
    std::cout << p << " order is " << o << "\n";
    Permutation q(6);
    while (o-- > 0)
        q.makeNext(); 
    if (p == q)
        return;
    std::cerr << "expected " << q << " == " << p << "\n";
    throw TestError();
}

void testFromOrder() {
    Permutation p(7);
    int o=1533;
    p.fromOrder(o);
    std::cout << p << " order is " << o << "\n";
    Permutation q(7);
    while (o-- > 0)
        q.makeNext(); 
    if (p == q)
        return;
    std::cerr << "expected " << q << " == " << p << "\n";
    throw TestError();
}

void testGetValue() {
    Permutation p({1, 3, 0, 4, 2});
    std::cout << p << ", p[1] = " << (int) p[1] << "\n";
    if (p(1) != 3)
        error("did not get the right element");
}

void testGetValueFail() {
    Permutation p({1, 3, 0, 4, 2, 5});
    std::cout << p << ", p[8] = " << (int)p[8] << "\n";
}

void testGetNegativeIndex() {
    Permutation p({1, 3, 0, 4, 2, 5});
    std::cout << p << ", p(-1) = " << (int)p(-1) << "\n";
    if (p(-1) != 5)
        error("did not get the right element");
}

void testSwapIndices() {
    Permutation p({1, 3, 0, 4, 2, 5});
    std::cout << p << "\n";
    p.swap(0, 5);
    std::cout << p << "\n";
    if (p[0] != 5 or p[5] != 1)
        error("didn't swap well");
}

void testSwapInappropriateIndicesFail() {
    Permutation p({1, 3, 0, 4, 2, 5});
    std::cout << p << "\n";
    p.swap(-1, 6);
    std::cout << p << "\n";
}

void testCompose() {
    Permutation p({1, 2, 0});
    Permutation q({0, 2, 1});
    Permutation r = p(q);
    Permutation s({1, 0, 2});
    std::cout << p << "(" << q << ") = " << r << "\n";
    if (r != s)
        error("didn't compose correctly");
}

void testComposeFail() {
    Permutation p({1, 0});
    Permutation q({1, 2, 0});
    Permutation r = p(q);
}

void testCycleAndPermutationFromString() {
    const char *s = "{0, 1, 5}Permutation( {1, 5, 2, 3, 4, 0 })";
    try {
        Permutation shouldfail(s);
        error("that should have failed"); 
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << "\n";
    }
    Cycle c(s);
    std::cout << "cycle = " << c << "\n";
    Permutation p(s);
    std::cout << "permutation = " << p << "\n";
    CycleForm C(c);
    std::cout << "cycleform = " << C << "\n";
    if (C != p) {
        for (Int i=0; i<C.size(); ++i) {
            std::cout << "C["<<i<<"] = " << (int)C[i] << "\n";
        }
        for (Int i=0; i<p.size(); ++i) {
            std::cout << "p["<<i<<"] = " << (int)p[i] << "\n";
        }
        error("cycleform should be equal to permutation");
    }
}

void testCycle() {
    Cycle c;
    c.push(0);
    c.push(1);
    c.push(2);
    std::cout << "cycle = " << c << "\n";
    if (c.pop() != 2)
        error("didn't pop right");
}

void testCycleFromString() {
    Cycle c("{0, 1, 5}");
    std::cout << "cycle = " << c << "\n";
    if (c.pop() != 5)
        error("didn't pop right");
}

void testCycleFromStringFail() {
    Cycle c("{0, 1, 5,");
    std::cout << "cycle = " << c << "\n";
}

void testCycleFromPermutation() {
    Permutation p({0, 1, 5, 4, 3, 2});
    CycleForm c(p);
    std::cout << " cycleform = " << c << "\n";
    if (c != p)
        error("should have been equal to original permutation");
    Permutation P(c);
    if (c != P)
        error("should have been equal to original cycleform");
}

void testComposeCycle() {
    CycleForm a({{1, 2, 0}, {4, 3}});
    Permutation B({0, 1, 3, 4, 2});
    Permutation Ba = B(a);
    std::cout << B << "(" << a << ") = " << Ba << "\n";
    Permutation A(a);
    Permutation BA = B(A);
    if (Ba != BA)
        error("Ba != BA; those should have been equal");
    CycleForm b(B);
    CycleForm ba = b(a);
    CycleForm bA = b(A);
    if (ba != bA)
        error("ba != bA; those should have been equal");
    if (ba != BA)
        error("ba != BA; those should have been equal");
}

void testCycleFormFromString() {
    CycleForm C("CycleForm({{0, 1, 2}, {5}})");
    std::cout << " C = " << C << "\n";
    if (C != Permutation({1, 2, 0, 3, 4, 5}))
        error("did not get cycleform from string correctly");
}

void testCycleFormFromStringBraceFail() {
    CycleForm C("CycleForm({{0, 1, 2}, {5})");
    std::cout << " C = " << C << "\n";
}

void testCycleFormFromStringParenthesisFail() {
    CycleForm C("CycleForm({{0, 1, 2, 3, 4}, {5}}");
    std::cout << " C = " << C << "\n";
}

void testCycleFormAndPermutationFromString() {
    const char *s = "CycleForm({{0, 1, 3}, {10, 11}})Permutation({1, 2, 3, 0, 4, 5, 10, 6, 8, 7, 9, 11})";
    CycleForm C(s);
    Permutation P(s);
    std::cout << " C = " << C << "\n";
    std::cout << " P = " << P << "\n";
}

void testCycleFormIteration() {
    CycleForm C("CycleForm({{0, 5, 4}, {6}})");
    std::cout << " C = " << C << "\n";
    for (const auto &cycle : C) {
        std::cout << " cycle " << cycle << "\n";
    }
}

void testCycleFormSwap() {
    // {0 1 3 4} -> swap 0, 2 -> {0 1 3 4} {0 2} = {0 2 1 3 4}
    CycleForm C(Cycle({0, 1, 3, 4}));
    Permutation P(C);
    std::cout << "before, C = " << C << "\n";
    C.swap(0, 2);
    std::cout << " after, C = " << C << "\n";
    P.swap(0, 2);
    if (P != C or C != CycleForm(Cycle({0, 2, 1, 3, 4})))
        error("bad swap");
}

void testCycleFormSwapFail() {
    // {0 1 3 4} -> swap 0, 2 -> {0 1 3 4} {0 2} = {0 2 1 3 4}
    CycleForm C(Cycle({0, 9, 1, 3, 4}));
    std::cout << "C = " << C << "\n";
    C.swap(3, 100);
    std::cout << "after, C = " << C << "\n";
}

void testDeltaVector() {
    Permutation P({1, 0, 2, 5, 4, 3});
    std::vector<Index> delta = P.getDeltaVector();
    std::vector<Index> expected = {1, 2, 3, 1, 1};
    if (expected != delta)
        error("invalid Delta vector");
}

int main(int narg, char **args) {
    TEST(Copy);
    TEST(Next);

    TEST(Vector);
    TESTSHOULDFAIL(VectorRepeatNumbersFail);
    TESTSHOULDFAIL(VectorMissingNumber);

    TEST(String);
    TEST(StringLeadingSpace);
    TESTSHOULDFAIL(StringExtraCommaFail);
    TESTSHOULDFAIL(StringRepeatCommasFail);
    TESTSHOULDFAIL(StringRepeatNumbersFail);
    TESTSHOULDFAIL(StringSpaceBetweenNumbersFail);
    TESTSHOULDFAIL(StringUnclosedBracesFail);
    TESTSHOULDFAIL(StringUnclosedBracketsFail);
    TEST(StringMultiple);

    TEST(Order);
    TEST(FromOrder);
   
    TEST(GetValue);
    TESTSHOULDFAIL(GetValueFail);
    TEST(GetNegativeIndex);
    
    TEST(SwapIndices);
    TESTSHOULDFAIL(SwapInappropriateIndicesFail);

    TEST(Compose);
    TESTSHOULDFAIL(ComposeFail);
    
    TEST(CycleAndPermutationFromString);
    
    TEST(Cycle);
    TEST(CycleFromString);
    TESTSHOULDFAIL(CycleFromStringFail);

    TEST(CycleFromPermutation);

    TEST(ComposeCycle);
    
    TEST(CycleFormFromString);
    TESTSHOULDFAIL(CycleFormFromStringBraceFail);
    TESTSHOULDFAIL(CycleFormFromStringParenthesisFail);
    TEST(CycleFormAndPermutationFromString);
    TEST(CycleFormIteration);

    TEST(CycleFormSwap);
    TESTSHOULDFAIL(CycleFormSwapFail);
    
    TEST(DeltaVector);

    std::cout << "All tests passed, good work.\n";
    return 0;
}
