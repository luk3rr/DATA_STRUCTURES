/*
* Filename: map_excpt.cc
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "map_excpt.h"

const char* mapexcpt::MapIsEmpty::what() const throw() {
    return "ERRO: O map está vazio";
}
