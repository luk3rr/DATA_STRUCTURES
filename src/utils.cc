#include "utils.hh"

namespace utils {
    void ancestorMsg(int i, int j, bool awsner) {
        std::cout << i << " é ancestral de " << j << " ? " << awsner << std::endl;
    }

    int min(int i, int j) {
        if (i < j)
            return i;
        else
            return j;
    }

    int min(int i, int j, int k, int l) {
        int min1 = utils::min(i, j);
        int min2 = utils::max(k, l);

        return utils::min(min1, min2);
    }

    int min(int i, int j, int k, int l, int m, int n) {
        int min1 = utils::min(i, j, k, l);
        int min2 = utils::min(m, n);

        return utils::min(min1, min2);
    }

    int max(int i, int j) {
        if (i > j)
            return i;
        else
            return j;
    }
} // namespace utils
