/*
 * Filename: binary_heap_test.cc
 * Created on: November  3, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include "doctest.h"

#include "binary_heap.h"

TEST_CASE("Max binary heap: Inserir/Remover elemento")
{
    bheap::BinaryHeap<int, decltype(comparators::Greater<int>)> bheap;

    SUBCASE("Caso 1: tamanho 1")
    {
        bheap.Push(10);
        CHECK(bheap.Peek() == 10);
        CHECK(bheap.Pop() == 10);

        CHECK(bheap.IsEmpty());
    }

    SUBCASE("Caso 3: Verificar ordem de remoção")
    {
        bheap.Push(2);
        bheap.Push(4);
        bheap.Push(1);
        bheap.Push(6);
        bheap.Push(3);
        bheap.Push(3);
        bheap.Push(10);
        bheap.Push(0);

        CHECK(bheap.Pop() == 10);
        CHECK(bheap.Pop() == 6);
        CHECK(bheap.Pop() == 4);
        CHECK(bheap.Pop() == 3);
        CHECK(bheap.Pop() == 3);
        CHECK(bheap.Pop() == 2);
        CHECK(bheap.Pop() == 1);
        CHECK(bheap.Pop() == 0);
        CHECK(bheap.IsEmpty());
    }
}

TEST_CASE("Min binary heap: Inserir/Remover elemento")
{
    bheap::BinaryHeap<int> bheap;

    SUBCASE("Caso 1: tamanho 1")
    {
        bheap.Push(10);
        CHECK(bheap.Peek() == 10);
        CHECK(bheap.Pop() == 10);

        CHECK(bheap.IsEmpty());
    }

    SUBCASE("Caso 3: Verificar ordem de remoção")
    {
        bheap.Push(2);
        bheap.Push(4);
        bheap.Push(1);
        bheap.Push(6);
        bheap.Push(3);
        bheap.Push(3);
        bheap.Push(10);
        bheap.Push(0);

        CHECK(bheap.Pop() == 0);
        CHECK(bheap.Pop() == 1);
        CHECK(bheap.Pop() == 2);
        CHECK(bheap.Pop() == 3);
        CHECK(bheap.Pop() == 3);
        CHECK(bheap.Pop() == 4);
        CHECK(bheap.Pop() == 6);
        CHECK(bheap.Pop() == 10);
        CHECK(bheap.IsEmpty());
    }
}
