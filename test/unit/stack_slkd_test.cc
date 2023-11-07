/*
* Filename: stack_slkd_test.cc
* Created on: May 14, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <ctime>
#include <cstdlib>
#include <random>
#include <stdexcept>

#include "doctest.h"

#include "stack_slkd.h"

#define STACK_MAX_LENGTH_TEST 10000
#define STACK_MIN_LENGTH_TEST 10

TEST_CASE("Empilha e desempilha") {
    slkd::Stack<float> pilha;

    std::srand(std::time(nullptr));
    int stackRandomLenght = (std::rand() + STACK_MIN_LENGTH_TEST) % STACK_MAX_LENGTH_TEST;
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
    slkd::Stack<float> pilha;

    SUBCASE("Desempilhar pilha vazia") {
        CHECK_THROWS_AS(pilha.Pop(), std::underflow_error);
    }

    SUBCASE("Espiar elemento no topo de uma pilha vazia") {
        CHECK_THROWS_AS(pilha.Peek(), std::overflow_error);
    }
}

TEST_CASE("Espiar elemento no topo") {
    slkd::Stack<int> pilha;
    pilha.Push(1);
    pilha.Push(4);
    pilha.Push(5);
    pilha.Push(7);
    pilha.Pop();
    CHECK(pilha.Peek() == 5);
}
