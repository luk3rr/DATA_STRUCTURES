#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "queue.hh"
#include "queue_excpt.hh"

#define QUEUE_MIN_LENGTH_TEST 10

TEST_CASE("Enfileira e desenfileira") {
    CircularQueue<float> queue;

    std::srand(std::time(nullptr));
    int queueRandomLenght = (std::rand() + QUEUE_MIN_LENGTH_TEST) % QUEUE_MAX_SIZE;
    float checkArray[queueRandomLenght];
    int randomNumber;

    // Enfileira os valores e os armazena em um array auxiliar para a verificação posterior
    for (int i = 0; i < queueRandomLenght; i++) {
        randomNumber = std::rand();
        queue.enqueue(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!queue.isEmpty());

    bool correct = true;

    // Desenfileira os valores
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
    CircularQueue<float> fila;

    SUBCASE("Desenfileirar fila vazia") {
        CHECK_THROWS_AS(fila.dequeue(), queexcpt::QueueIsEmpty);
    }

    SUBCASE("Exceder limite da fila") {
        for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
            fila.enqueue(i);
        }
        CHECK_THROWS_AS(fila.enqueue(333), queexcpt::QueueOverflow);
    }
}
