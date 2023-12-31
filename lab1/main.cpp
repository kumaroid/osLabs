#include "parent.hpp"

int main() {
    if (getenv("PATH_TO_CHILD") == nullptr) {
        std::cerr << "PATH_TO_CHILD not defined.\n";
        exit(EXIT_FAILURE);
    }
    ParentRoutine(getenv("PATH_TO_CHILD"), std::cin);
}
