#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "stack.hh"

TEST_CASE("Teste empilha e desempilha") {
    Stack<float> pilha;

    std::srand(std::time(nullptr));
    int stackRandomLenght = std::rand() % MAX_SIZE;
    float vt[stackRandomLenght];

    int randomNumber;
    for (int i = 0; i < stackRandomLenght; i++) {
        randomNumber = std::rand();
        pilha.push(randomNumber);
        vt[i] = randomNumber;
    }

    CHECK(!pilha.isEmpty());

    bool correct = true;
    // Desempilhar os valores
    int i = stackRandomLenght - 1;
    while (!pilha.isEmpty()) {
        if (vt[i] != pilha.pop()) {
            correct = false;
            break;
        }
        i--;
    }

    CHECK(pilha.isEmpty());
    CHECK(correct);
}
