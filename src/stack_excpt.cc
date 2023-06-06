/*
* Filename: stack_excpt.cc
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "stack_excpt.h"

const char* stkexcpt::StackOverflow::what() const throw() {
    return "ERRO: Limite da pilha excedido";
}

const char* stkexcpt::StackIsEmpty::what() const throw() {
    return "ERRO: A pilha está vazia";
}
