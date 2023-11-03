/*
 * Filename: tuple_excpt.cc
 * Created on: October 29, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "tuple_excpt.h"

const char* tplexcpt::InvalidIndex::what() const throw()
{
    return "ERROR: Invalid index";
}
