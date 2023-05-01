#include <ctime>
#include <cstdlib>
#include <random>

#include "doctest.h"
#include "queue.hh"

TEST_CASE("Teste enfileira e desenfileira") {
    CircularQueue<float> queue;

    std::srand(std::time(nullptr));
    int queueRandomLenght = std::rand() % MAXTAM;
    float vt[queueRandomLenght];

    int randomNumber;
    for (int i = 0; i < queueRandomLenght; i++) {
        randomNumber = std::rand();
        queue.enqueue(randomNumber);
        vt[i] = randomNumber;
    }

    CHECK(!queue.isEmpty());

    bool correct = true;

    // Desenfileira os valores
    for (int i = 0; i < queueRandomLenght; i++) {
        if (vt[i] != queue.dequeue()) {
            correct = false;
            break;
        }
    }

    CHECK(queue.isEmpty());
    CHECK(correct);
}
