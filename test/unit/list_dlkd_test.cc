/*
 * Filename: list_dlkd_test.cc
 * Created on: May 12, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <stdexcept>

#include "doctest.h"

#include "list_dlkd.h"

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
    CHECK_THROWS_AS(list.Front(), std::overflow_error);
    CHECK_THROWS_AS(list.Back(), std::overflow_error);
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

TEST_CASE("Insert with position")
{
    dlkd::List<uint32_t> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);

    SUBCASE("Insert in the beginning")
    {
        REQUIRE(list.Size() == 4);

        list.Insert(0, 0);

        REQUIRE(list.Size() == 5);
        REQUIRE(list.Front() == 0);
        REQUIRE(list.Back() == 4);

        dlkd::List<uint32_t>::Iterator it = list.begin();

        CHECK(it->GetValue() == 0);
        it++;
        CHECK(it->GetValue() == 1);
        it++;
        CHECK(it->GetValue() == 2);
        it++;
        CHECK(it->GetValue() == 3);
        it++;
        CHECK(it->GetValue() == 4);
    }

    SUBCASE("Insert in the middle")
    {
        REQUIRE(list.Size() == 4);

        list.Insert(20, 2);

        REQUIRE(list.Size() == 5);
        REQUIRE(list.Front() == 1);
        REQUIRE(list.Back() == 4);

        dlkd::List<uint32_t>::Iterator it = list.begin();
        CHECK(it->GetValue() == 1);
        it++;
        CHECK(it->GetValue() == 2);
        it++;
        CHECK(it->GetValue() == 20);
        it++;
        CHECK(it->GetValue() == 3);
        it++;
        CHECK(it->GetValue() == 4);
    }

    SUBCASE("Insert in the end")
    {
        REQUIRE(list.Size() == 4);

        list.Insert(31, 4);

        REQUIRE(list.Size() == 5);
        REQUIRE(list.Front() == 1);
        REQUIRE(list.Back() == 31);

        dlkd::List<uint32_t>::Iterator it = list.begin();
        CHECK(it->GetValue() == 1);
        it++;
        CHECK(it->GetValue() == 2);
        it++;
        CHECK(it->GetValue() == 3);
        it++;
        CHECK(it->GetValue() == 4);
        it++;
        CHECK(it->GetValue() == 31);
    }
}
