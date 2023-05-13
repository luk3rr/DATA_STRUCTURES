#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "queue_excpt.hh"
#include "queue_singly_linked.hh"

#define QUEUE_MAX_LENGTH_TEST 10000
#define QUEUE_MIN_LENGTH_TEST 10

TEST_CASE("Enfileira e desenfileira") {
    slkd::Queue<float> queue;

    std::srand(std::time(nullptr));
    int queueRandomLenght = (std::rand() + QUEUE_MIN_LENGTH_TEST) % QUEUE_MAX_LENGTH_TEST;
    float checkArray[queueRandomLenght];
    int randomNumber;

    CHECK(queue.isEmpty());

    // Enfileira os valores e os armazena em um array auxiliar para a verificação posterior
    for (int i = 0; i < queueRandomLenght; i++) {
        randomNumber = std::rand();
        queue.enqueue(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!queue.isEmpty());

    bool correct = true;

    // Desenfileira os valores e verifica se foram enfileirados na ordem correta
    for (int i = 0; i < queueRandomLenght; i++) {
        if (checkArray[i] != queue.dequeue()) {
            correct = false;
            break;
        }
    }

    CHECK(queue.isEmpty());
    CHECK(correct);
}

TEST_CASE("Lançamento de exceções") {
    slkd::Queue<float> queue;

    SUBCASE("Desenfileirar fila vazia") {
        CHECK_THROWS_AS(queue.dequeue(), queexcpt::QueueIsEmpty);
    }
}
