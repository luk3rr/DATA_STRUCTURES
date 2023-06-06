/*
* Filename: queue_excpt.cc
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "queue_excpt.h"

const char* queexcpt::QueueOverflow::what() const throw() {
    return "ERRO: Limite da fila excedido";
}

const char* queexcpt::QueueIsEmpty::what() const throw() {
    return "ERRO: A fila está vazia";
}
