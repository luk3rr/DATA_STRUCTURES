#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "stack.hh"
#include "stack_excpt.hh"

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
        pilha.push(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!pilha.isEmpty());

    bool correct = true;

    // Desempilha os valores e verifica se foram empilhados na ordem correta
    int i = stackRandomLenght - 1;
    while (!pilha.isEmpty()) {
        if (checkArray[i] != pilha.pop()) {
            correct = false;
            break;
        }
        i--;
    }

    CHECK(pilha.isEmpty());
    CHECK(correct);
}


TEST_CASE("Lançamento de exceções") {
    Stack<float> pilha;

    SUBCASE("Desempilhar pilha vazia") {
        CHECK_THROWS_AS(pilha.pop(), stkexcpt::StackIsEmpty);
    }

    SUBCASE("Exceder limite da pilha") {
        for (int i = 0; i < STACK_MAX_SIZE; i++) {
            pilha.push(i);
        }
        CHECK_THROWS_AS(pilha.push(333), stkexcpt::StackOverflow);
    }
}
