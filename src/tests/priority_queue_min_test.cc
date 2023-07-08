/*
* Filename: priority_queue_min_test.cc
* Created on: July  7, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "priority_queue_min.h"

TEST_CASE("Inserir/Remover elemento") {
    MinPQueue<int> pqueue;

    SUBCASE("Caso 1: Lista vazia") {
        CHECK_THROWS_AS(pqueue.Get(), queexcpt::QueueIsEmpty);
        CHECK_THROWS_AS(pqueue.Delete(), queexcpt::QueueIsEmpty);
    }

    SUBCASE("Caso 2: Lista de tamanho 1") {
        pqueue.Insert(10);
        CHECK(pqueue.Get() == 10);
        CHECK(pqueue.Delete() == 10);
    }

    SUBCASE("Caso 3: Verificar ordem de remoção") {
        pqueue.Insert(2);
        pqueue.Insert(4);
        pqueue.Insert(1);
        pqueue.Insert(6);
        pqueue.Insert(3);
        pqueue.Insert(3);
        pqueue.Insert(10);
        pqueue.Insert(0);

        CHECK(pqueue.Delete() == 0);
        CHECK(pqueue.Delete() == 1);
        CHECK(pqueue.Delete() == 2);
        CHECK(pqueue.Delete() == 3);
        CHECK(pqueue.Delete() == 3);
        CHECK(pqueue.Delete() == 4);
        CHECK(pqueue.Delete() == 6);
        CHECK(pqueue.Delete() == 10);
        CHECK(pqueue.IsEmpty());
    }
}
