/*
* Filename: vector_test.cc
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <cstddef>
#include "doctest.h"
#include "vector.h"

#define VECTOR_TEST_MAX_SIZE 1000

TEST_CASE("Redimensionamento automático do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < VECTOR_START_SIZE * 3; i++) {
        vector.PushBack(i);
    }

    CHECK(vector.Size() == VECTOR_START_SIZE * 3);
}

TEST_CASE("Redimensionamento manual do vector") {
    Vector<int> vector;
    std::size_t newSize = 10;

    vector.Resize(newSize);
    REQUIRE(vector.Size() == 10);
    REQUIRE(vector.GetMaxSize() == 10);

    CHECK(vector[5] == 0); // Resize deve preencher o array com 0
    CHECK_THROWS_AS(vector.At(newSize + 1), vecexcpt::InvalidIndex);

    for (unsigned int i = 0; i < newSize; i++) {
        vector[i] = i;
    }

    CHECK(vector.At(newSize - 1) == newSize - 1);
}

TEST_CASE("Acessar um elemento do vector") {
    Vector<int> vector;

    for (unsigned int i = 0; i < 50; i++) {
        vector.PushBack(i);
    }

    REQUIRE(vector.Size() == 50);
    CHECK(vector[10] == 10);
    CHECK(vector.At(10) == 10);
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

TEST_CASE("Iterator") {
    Vector<int> vec;


    for (unsigned int i = 0; i < VECTOR_START_SIZE * 3; i++)
        vec.PushBack(i);

    REQUIRE(vec.Size() == VECTOR_START_SIZE * 3);

    int value = 0;
    bool correct = true;

    Vector<int>::Iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
        if (*it != value) {
            correct = false;
            break;
        }
        value++;
    }

    value = 0;
    for (auto pos : vec) {
        if (pos != value) {
            correct = false;
            break;
        }
        value++;
    }

    CHECK(correct);
}
