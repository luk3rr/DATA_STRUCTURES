/*
 * Filename: list_dlkd_test.cc
 * Created on: May 12, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>

#include "doctest.h"
#include "list_dlkd.h"
#include "list_excpt.h"

TEST_CASE("Remover elemento")
{
    dlkd::List<uint32_t> list;

    SUBCASE("Remover algo de uma lista vazia")
    {
        list.Remove(1);
        CHECK(list.Size() == 0);
    }

    SUBCASE("Remover 1 elemento")
    {
        list.PushBack(1);
        CHECK(list.Size() == 1);
        list.Remove(1);
        CHECK(list.Size() == 0);
    }

    SUBCASE("Remover 2 elemento")
    {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        list.PushBack(4);
        CHECK(list.Size() == 4);
        list.Remove(2);
        CHECK(list.Size() == 3);
        list.Remove(4);
        CHECK(list.Size() == 2);
    }
}

TEST_CASE("Pegar primeiro e último elemento")
{
    dlkd::List<uint32_t> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.Remove(1);
    CHECK(list.Front() == 2);
    CHECK(list.Back() == 4);
}

TEST_CASE("Lançamento de exceções para lista vazia")
{
    dlkd::List<uint32_t> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.Clear();
    CHECK_THROWS_AS(list.Front(), lstexcpt::ListIsEmpty);
    CHECK_THROWS_AS(list.Back(), lstexcpt::ListIsEmpty);
}

TEST_CASE("Iterator")
{
    dlkd::List<uint32_t> list;

    for (uint32_t i = 0; i <= 10; i++)
    {
        list.PushBack(i);
    }

    bool correct = true;

    SUBCASE("Variable Iterator")
    {
        dlkd::List<uint32_t>::Iterator it;
        uint32_t                       i = 0;
        for (it = list.begin(); it != list.end(); it++)
        {
            if (it->GetValue() != i)
            {
                correct = false;
                break;
            }
            i++;
        }
        CHECK(correct);
    }

    SUBCASE("foreach")
    {
        uint32_t i = 0;
        for (auto it : list)
        {
            if (it.GetValue() != i)
            {
                correct = false;
                break;
            }
            i++;
        }
        CHECK(correct);
    }
}
