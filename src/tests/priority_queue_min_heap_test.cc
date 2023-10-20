/*
* Filename: priority_queue_min_heap_test.cc
* Created on: July  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "priority_queue_heap.h"

TEST_CASE("Inserir/Remover elemento") {
    heap::PriorityQueue<int> minPQueue;

    SUBCASE("Caso 1: Lista vazia") {
        CHECK_THROWS_AS(minPQueue.Peek(), queexcpt::QueueIsEmpty);
        CHECK_THROWS_AS(minPQueue.Dequeue(), queexcpt::QueueIsEmpty);
    }

    SUBCASE("Caso 2: Lista de tamanho 1") {
        minPQueue.Enqueue(10);
        CHECK(minPQueue.Peek() == 10);
        CHECK(minPQueue.Dequeue() == 10);
    }

    SUBCASE("Caso 3: Verificar ordem de remoção") {
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
