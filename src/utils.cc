/*
* Filename: utils.cc
* Created on: May 12, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "utils.h"

namespace utils {
    void AncestorMsg(int i, int j, bool awsner) {
        std::cout << i << " é ancestral de " << j << " ? " << awsner << std::endl;
    }

    int Min(int i, int j) {
        if (i < j)
            return i;
        else
            return j;
    }

    int Min(int i, int j, int k, int l) {
        int min1 = utils::Min(i, j);
        int min2 = utils::Max(k, l);

        return utils::Min(min1, min2);
    }

    int Min(int i, int j, int k, int l, int m, int n) {
        int min1 = utils::Min(i, j, k, l);
        int min2 = utils::Min(m, n);

        return utils::Min(min1, min2);
    }

    int Max(int i, int j) {
        if (i > j)
            return i;
        else
            return j;
    }
} // namespace utils
