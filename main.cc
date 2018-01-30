#include "permutation.h"

int main(int narg, char **args) {
    Permutation p(256);
    Permutation q(256);
    p.fromOrder(121);
    q.fromOrder(2);
    std::cout << p.order() << ": " << p << "\n";
    std::cout << q.order() << ": " << q << "\n";
    Permutation r = p(q);
    std::cout << r.order() << "p(q): " << r << "\n";
    r = q(p);
    std::cout << r.order() << "q(p): " << r << "\n";
    return 0;
}
