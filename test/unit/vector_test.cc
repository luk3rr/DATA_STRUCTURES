/*
 * Filename: vector_test.cc
 * Created on: June  5, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <stdexcept>

#include "doctest.h"

#include "vector.h"

#define VECTOR_TEST_MAX_SIZE 1000

TEST_CASE("Redimensionamento automático do vector")
{
    Vector<int> vector;

    for (unsigned int i = 0; i < VECTOR_START_SIZE * 3; i++)
    {
        vector.PushBack(i);
    }

    CHECK(vector.Size() == VECTOR_START_SIZE * 3);
}

TEST_CASE("Redimensionamento manual do vector")
{
    Vector<int> vector;
    std::size_t newSize = 10;

    vector.Resize(newSize);
    REQUIRE(vector.Size() == 10);
    REQUIRE(vector.GetMaxSize() == 10);

    CHECK(vector[5] == 0); // Resize deve preencher o array com 0
    CHECK_THROWS_AS(vector.At(newSize + 1), std::out_of_range);

    for (unsigned int i = 0; i < newSize; i++)
    {
        vector[i] = i;
    }

    CHECK(vector.At(newSize - 1) == newSize - 1);
}

TEST_CASE("Acessar um elemento do vector")
{
    Vector<int> vector;

    for (unsigned int i = 0; i < 50; i++)
    {
        vector.PushBack(i);
    }

    REQUIRE(vector.Size() == 50);
    CHECK(vector[10] == 10);
    CHECK(vector.At(10) == 10);
}

TEST_CASE("Alterar um elemento do vector")
{
    Vector<int> vector;

    for (unsigned int i = 0; i < 50; i++)
    {
        vector.PushBack(i);
    }

    REQUIRE(vector.Size() == 50);
    vector[10] = 99;
    CHECK(vector[10] == 99);
}

TEST_CASE("Swap de elementos do vector")
{
    Vector<int> vector;

    vector.PushBack(5);
    vector.PushBack(10);
    vector.Swap(0, 1);

    CHECK((vector[0] == 10 and vector[1] == 5));
}

TEST_CASE("Verificar igualdade entre vectors")
{
    Vector<int> vector1, cpVector1, vector2;

    for (unsigned int i = 0; i < 10; i++)
    {
        vector1.PushBack(i);
        cpVector1.PushBack(i);
        vector2.PushBack(i);
    }

    vector2.PushBack(99);

    CHECK(vector1 == cpVector1);
    CHECK(!(vector1 == vector2));
}

TEST_CASE("Iterator")
{
    Vector<int> vec;

    for (unsigned int i = 0; i < VECTOR_START_SIZE * 3; i++)
        vec.PushBack(i);

    REQUIRE(vec.Size() == VECTOR_START_SIZE * 3);

    int  value   = 0;
    bool correct = true;

    Vector<int>::Iterator it;
    for (it = vec.begin(); it != vec.end(); it++)
    {
        if (*it != value)
        {
            correct = false;
            break;
        }
        value++;
    }

    value = 0;
    for (auto pos : vec)
    {
        if (pos != value)
        {
            correct = false;
            break;
        }
        value++;
    }

    CHECK(correct);
}

TEST_CASE("Construtor com initializer list")
{
    Vector<int> vector({ 1, 2, 3, 5, 9 });

    CHECK(vector[0] == 1);
    CHECK(vector[2] == 3);
    CHECK(vector[4] == 9);
}

TEST_CASE("Obter os elementos na primeira e na última posição do vector")
{
    Vector<uint32_t> vec({ 11, 2, 90 });

    CHECK(vec.Back() == 90);
    CHECK(vec.Front() == 11);

    vec.PushBack(99);
    CHECK(vec.Back() == 99);

    vec.Clear();

    CHECK_THROWS_AS(vec.Back(), std::overflow_error);
    CHECK_THROWS_AS(vec.Front(), std::overflow_error);
}

TEST_CASE("Initialize 2D Vector with Default Values")
{
    std::size_t SQUARE_MATRIX_SIZE = 4;
    int32_t     MAX_GENERATE_VALUE = 5;
    int32_t     MIN_GENERATE_VALUE = -5;

    // Generate a random value in the specified range
    std::srand(std::time(nullptr));
    int32_t randomValue = std::rand() % (MAX_GENERATE_VALUE - MIN_GENERATE_VALUE + 1) +
                          MIN_GENERATE_VALUE;

    // Create a 2D matrix with each element initialized to the random value
    Vector<Vector<int32_t>> matrix(SQUARE_MATRIX_SIZE,
                                   Vector<int32_t>(SQUARE_MATRIX_SIZE, randomValue));

    SUBCASE("Check Matrix Size")
    {
        REQUIRE(matrix.Size() == SQUARE_MATRIX_SIZE);
    }

    bool correct = true;

    SUBCASE("Check Elements Initialization")
    {
        for (std::size_t i = 0; i < SQUARE_MATRIX_SIZE; i++)
        {
            SUBCASE("Check Subvector Size")
            {
                REQUIRE(matrix[i].Size() == SQUARE_MATRIX_SIZE);
            }

            for (std::size_t j = 0; j < SQUARE_MATRIX_SIZE; j++)
            {
                if (matrix[i][j] != randomValue)
                {
                    correct = false;
                    break;
                }
            }
        }

        CHECK(correct);
    }
}
