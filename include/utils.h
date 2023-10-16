/*
* Filename: utils.h
* Created on: May 12, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

namespace utils {
    void AncestorMsg(int i, int j, bool awsner);

    int Min(int i, int j);

    int Min(int i, int j, int k, int l);

    int Min(int i, int j, int k, int l, int m, int n);

    int Max(int i, int j);

    /**
     * @brief Default less-than comparator
     */
    template<typename typeT>
    struct less {
        bool operator()(const typeT& a, const typeT& b) const {
            return a < b;
        }
    };
} // namespace utils

#endif // UTILS_H_
