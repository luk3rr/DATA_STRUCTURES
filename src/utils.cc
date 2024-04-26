/*
 * Filename: utils.cc
 * Created on: May 12, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "utils.h"

namespace utils
{
    void AncestorMsg(int i, int j, bool awsner)
    {
        std::cout << i << " é ancestral de " << j << " ? " << awsner << std::endl;
    }
} // namespace utils
