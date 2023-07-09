/*
* Filename: queue_slkd_test.cc
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "queue_excpt.h"
#include "queue_slkd.h"

#define QUEUE_MAX_LENGTH_TEST 10000
#define QUEUE_MIN_LENGTH_TEST 10

TEST_CASE("Enfileira e desenfileira") {
    slkd::Queue<float> queue;

    std::srand(std::time(nullptr));
    int queueRandomLenght = (std::rand() + QUEUE_MIN_LENGTH_TEST) % QUEUE_MAX_LENGTH_TEST;
    float checkArray[queueRandomLenght];
    int randomNumber;

    CHECK(queue.IsEmpty());

    // Enfileira os valores e os armazena em um array auxiliar para a verificação posterior
    for (int i = 0; i < queueRandomLenght; i++) {
        randomNumber = std::rand();
        queue.Enqueue(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!queue.IsEmpty());

    bool correct = true;

    // Desenfileira os valores e verifica se foram enfileirados na ordem correta
    for (int i = 0; i < queueRandomLenght; i++) {
        if (checkArray[i] != queue.Dequeue()) {
            correct = false;
            break;
        }
    }

    CHECK(queue.IsEmpty());
    CHECK(correct);
}

TEST_CASE("Lançamento de exceções") {
    slkd::Queue<float> queue;

    SUBCASE("Desenfileirar fila vazia") {
        CHECK_THROWS_AS(queue.Dequeue(), queexcpt::QueueIsEmpty);
    }
}
