/*
* Filename: stack_test.cc
* Created on: May 14, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "stack.h"
#include "stack_excpt.h"

#define STACK_MIN_LENGTH_TEST 10

TEST_CASE("Empilha e desempilha") {
    Stack<float> pilha;

    std::srand(std::time(nullptr));
    int stackRandomLenght = (std::rand() + STACK_MIN_LENGTH_TEST) % STACK_MAX_SIZE;
    float checkArray[stackRandomLenght];
    int randomNumber;

    // Empilha os valores e os armazena em um array auxiliar para a verificação posterior
    for (int i = 0; i < stackRandomLenght; i++) {
        randomNumber = std::rand();
        pilha.Push(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!pilha.IsEmpty());

    bool correct = true;

    // Desempilha os valores e verifica se foram empilhados na ordem correta
    int i = stackRandomLenght - 1;
    while (!pilha.IsEmpty()) {
        if (checkArray[i] != pilha.Pop()) {
            correct = false;
            break;
        }
        i--;
    }

    CHECK(pilha.IsEmpty());
    CHECK(correct);
}


TEST_CASE("Lançamento de exceções") {
    Stack<float> pilha;

    SUBCASE("Desempilhar pilha vazia") {
        CHECK_THROWS_AS(pilha.Pop(), stkexcpt::StackIsEmpty);
    }

    SUBCASE("Exceder limite da pilha") {
        for (int i = 0; i < STACK_MAX_SIZE; i++) {
            pilha.Push(i);
        }
        CHECK_THROWS_AS(pilha.Push(333), stkexcpt::StackOverflow);
    }
}
