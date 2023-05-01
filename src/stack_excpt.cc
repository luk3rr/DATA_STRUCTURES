#include "stack_excpt.hh"

const char* stkexcpt::StackOverflow::what() const throw() {
    return "ERRO: Limite da pilha excedido";
}

const char* stkexcpt::StackIsEmpty::what() const throw() {
    return "ERRO: A pilha está vazia";
}
