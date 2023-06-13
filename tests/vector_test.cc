/*
* Filename: vector_test.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "vector.h"

#define VECTOR_TEST_MAX_SIZE 1000

TEST_CASE("Redimensionamento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < VECTOR_START_SIZE * 3; i++) {
        vector.PushBack(i);
    }

    CHECK(vector.Size() == VECTOR_START_SIZE * 3);
}

TEST_CASE("Acessar um elemento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < 50; i++) {
        vector.PushBack(i);
    }

    REQUIRE(vector.Size() == 50);
    CHECK(vector[10] == 10);
}

TEST_CASE("Alterar um elemento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < 50; i++) {
        vector.PushBack(i);
    }

    REQUIRE(vector.Size() == 50);
    vector[10] = 99;
    CHECK(vector[10] == 99);
}

TEST_CASE("Swap de elementos do vector") {
    Vector<int> vector;

    vector.PushBack(5);
    vector.PushBack(10);
    vector.Swap(0, 1);

    CHECK((vector[0] == 10 and vector[1] == 5));
}

TEST_CASE("Verificar igualdade entre vectors") {
    Vector<int> vector1, cpVector1, vector2;

    for (unsigned int i = 0; i < 10; i++) {
        vector1.PushBack(i);
        cpVector1.PushBack(i);
        vector2.PushBack(i);
    }

    vector2.PushBack(99);

    CHECK(vector1 == cpVector1);
    CHECK(!(vector1 == vector2));
}
