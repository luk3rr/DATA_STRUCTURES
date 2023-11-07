/*
 * Filename: priority_queue_slkd_test.cc
 * Created on: June 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <stdexcept>

#include "doctest.h"

#include "priority_queue_slkd.h"
#include "utils.h"

TEST_CASE("Max Priority Queue: Inserir/Remover elemento")
{
    slkd::PriorityQueue<int, utils::greater<int>> pqueue;

    SUBCASE("Caso 1: Lista vazia")
    {
        CHECK_THROWS_AS(pqueue.Peek(), std::overflow_error);
        CHECK_THROWS_AS(pqueue.Dequeue(), std::underflow_error);
    }

    SUBCASE("Caso 2: Lista de tamanho 1")
    {
        pqueue.Enqueue(10);
        CHECK(pqueue.Peek() == 10);
        CHECK(pqueue.Dequeue() == 10);
    }

    SUBCASE("Caso 3: Verificar ordem de remoção")
    {
        pqueue.Enqueue(2);
        pqueue.Enqueue(4);
        pqueue.Enqueue(1);
        pqueue.Enqueue(6);
        pqueue.Enqueue(3);
        pqueue.Enqueue(3);
        pqueue.Enqueue(10);
        pqueue.Enqueue(0);

        CHECK(pqueue.Dequeue() == 10);
        CHECK(pqueue.Dequeue() == 6);
        CHECK(pqueue.Dequeue() == 4);
        CHECK(pqueue.Dequeue() == 3);
        CHECK(pqueue.Dequeue() == 3);
        CHECK(pqueue.Dequeue() == 2);
        CHECK(pqueue.Dequeue() == 1);
        CHECK(pqueue.Dequeue() == 0);
        CHECK(pqueue.IsEmpty());
    }
}

TEST_CASE("Min Priority Queue: Inserir/Remover elemento")
{
    slkd::PriorityQueue<int> pqueue;

    SUBCASE("Caso 1: Lista vazia")
    {
        CHECK_THROWS_AS(pqueue.Peek(), std::overflow_error);
        CHECK_THROWS_AS(pqueue.Dequeue(), std::underflow_error);
    }

    SUBCASE("Caso 2: Lista de tamanho 1")
    {
        pqueue.Enqueue(10);
        CHECK(pqueue.Peek() == 10);
        CHECK(pqueue.Dequeue() == 10);
    }

    SUBCASE("Caso 3: Verificar ordem de remoção")
    {
        pqueue.Enqueue(2);
        pqueue.Enqueue(4);
        pqueue.Enqueue(1);
        pqueue.Enqueue(6);
        pqueue.Enqueue(3);
        pqueue.Enqueue(3);
        pqueue.Enqueue(10);
        pqueue.Enqueue(0);

        CHECK(pqueue.Dequeue() == 0);
        CHECK(pqueue.Dequeue() == 1);
        CHECK(pqueue.Dequeue() == 2);
        CHECK(pqueue.Dequeue() == 3);
        CHECK(pqueue.Dequeue() == 3);
        CHECK(pqueue.Dequeue() == 4);
        CHECK(pqueue.Dequeue() == 6);
        CHECK(pqueue.Dequeue() == 10);
        CHECK(pqueue.IsEmpty());
    }
}
