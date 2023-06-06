/*
* Filename: list_excpt.cc
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "list_excpt.h"

const char* lstexcpt::ListIsEmpty::what() const throw() {
    return "ERRO: A lista está vazia";
}
