#include "permutation.h"

int main(int narg, char **args) {
    Permutation p;
    std::cout << p << "\n";
    p.makeNext();
    std::cout << p << "\n";
    return 0;
}
