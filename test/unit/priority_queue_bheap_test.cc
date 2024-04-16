/*
 * Filename: priority_queue_bheap_test.cc
 * Created on: July  9, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <stdexcept>

#include "doctest.h"

#include "priority_queue_bheap.h"
#include "utils.h"

TEST_CASE("Max Priority Queue: Inserir/Remover elemento")
{
    bheap::PriorityQueue<int, decltype(comparators::greater<int>)> pqueue;

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
    bheap::PriorityQueue<int> minPQueue;

    SUBCASE("Caso 1: Lista vazia")
    {
        CHECK_THROWS_AS(minPQueue.Peek(), std::overflow_error);
        CHECK_THROWS_AS(minPQueue.Dequeue(), std::underflow_error);
    }

    SUBCASE("Caso 2: Lista de tamanho 1")
    {
        minPQueue.Enqueue(10);
        CHECK(minPQueue.Peek() == 10);
        CHECK(minPQueue.Dequeue() == 10);
    }

    SUBCASE("Caso 3: Verificar ordem de remoção")
    {
        minPQueue.Enqueue(2);
        minPQueue.Enqueue(4);
        minPQueue.Enqueue(1);
        minPQueue.Enqueue(6);
        minPQueue.Enqueue(3);
        minPQueue.Enqueue(3);
        minPQueue.Enqueue(10);
        minPQueue.Enqueue(0);

        CHECK(minPQueue.Dequeue() == 0);
        CHECK(minPQueue.Dequeue() == 1);
        CHECK(minPQueue.Dequeue() == 2);
        CHECK(minPQueue.Dequeue() == 3);
        CHECK(minPQueue.Dequeue() == 3);
        CHECK(minPQueue.Dequeue() == 4);
        CHECK(minPQueue.Dequeue() == 6);
        CHECK(minPQueue.Dequeue() == 10);
        CHECK(minPQueue.IsEmpty());
    }
}
