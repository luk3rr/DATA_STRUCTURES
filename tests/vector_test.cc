/*
* Filename: vector_test.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "vector.h"

TEST_CASE("Redimensionamento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < VECTOR_START_SIZE * 2; i++) {
        vector.PushBack(i);
    }

    CHECK(vector.GetMaxSize() > VECTOR_START_SIZE);
}

TEST_CASE("Acessar um elemento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < VECTOR_START_SIZE; i++) {
        vector.PushBack(i);
    }

    REQUIRE(vector.GetSize() == VECTOR_START_SIZE);
    CHECK(vector[10] == 10);
}

TEST_CASE("Swap de elementos do vector") {
    Vector<int> vector;

    vector.PushBack(5);
    vector.PushBack(10);
    vector.Swap(0, 1);

    CHECK((vector[0] == 10 and vector[1] == 5));
}
