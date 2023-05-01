#include "list_excpt.hh"

const char* lstexcpt::ListIsEmpty::what() const throw() {
    return "ERRO: A lista está vazia";
}
