/*
 * Filename: circular_queue_test.cc
 * Created on: May 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include "doctest.h"

#include "circular_queue.h"

#define QUEUE_MIN_LENGTH_TEST 10

TEST_CASE("Enfileira e desenfileira")
{
    CircularQueue<float> queue;

    std::srand(std::time(nullptr));
    int queueRandomLenght =
        (std::rand() + QUEUE_MIN_LENGTH_TEST) % CIRCULAR_QUEUE_MAX_SIZE;
    float checkArray[queueRandomLenght];
    int   randomNumber;

    // Enfileira os valores e os armazena em um array auxiliar para a verificação
    // posterior
    for (int i = 0; i < queueRandomLenght; i++)
    {
        randomNumber = std::rand();
        queue.Enqueue(randomNumber);
        checkArray[i] = randomNumber;
    }

    CHECK(!queue.IsEmpty());

    bool correct = true;

    // Desenfileira os valores
    for (int i = 0; i < queueRandomLenght; i++)
    {
        if (checkArray[i] != queue.Dequeue())
        {
            correct = false;
            break;
        }
    }

    CHECK(queue.IsEmpty());
    CHECK(correct);
}

TEST_CASE("Lançamento de exceções")
{
    CircularQueue<float> fila;

    SUBCASE("Desenfileirar fila vazia")
    {
        CHECK_THROWS_AS(fila.Dequeue(), std::underflow_error);
    }

    SUBCASE("Exceder limite da fila")
    {
        for (int i = 0; i < CIRCULAR_QUEUE_MAX_SIZE; i++)
        {
            fila.Enqueue(i);
        }
        CHECK_THROWS_AS(fila.Enqueue(333), std::overflow_error);
    }
}
