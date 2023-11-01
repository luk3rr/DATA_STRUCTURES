/*
* Filename: binary_tree_excpt.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "binary_tree_excpt.h"

const char* bntexcpt::NewTreeIsEmpty::what() const throw() {
    return "ERRO: Nova árvore inexistente ou vazia";
}

const char* bntexcpt::TreeIsNotEmpty::what() const throw() {
    return "ERRO: A árvore atual não está vazia";
}
