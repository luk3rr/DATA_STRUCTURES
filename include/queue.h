/*
* Filename: queue.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include "queue_excpt.h"

#define QUEUE_MAX_SIZE 1000

template <typename typeT>
class CircularQueue {
    private:
        int m_size, m_front, m_back;
        typeT m_queue[QUEUE_MAX_SIZE];

    public:
        CircularQueue();

        /**
        @brief Pega o tamanho da fila
        @return Inteiro com o tamanho da fila
        */
        int Size();

        /**
        @brief Enfileira um elemento
        @param item Chave que será enfileirada
        */
        void Enqueue(typeT item);

        /**
        @brief Desenfileira um elemento
        @return Elemento que foi desenfileirado
        */
        typeT Dequeue();

        /**
        @brief Verifica se a fila está vazia
        @return True se a fila estiver vazia, False caso contrário
        */
        bool IsEmpty();

        /**
        @brief Remove todos os elementos da fila
        */
        void Clear();
};

template <typename typeT>
CircularQueue<typeT>::CircularQueue() {
    this->m_size = 0;
    this->m_front = 0;
    this->m_back = 0;
}

template <typename typeT>
int CircularQueue<typeT>::Size() {
    return this->m_size;
}

template <typename typeT>
bool CircularQueue<typeT>::IsEmpty() {
    if (this->m_size == 0) return true;
    else return false;
}

// Adiciona um item ao fim da fila
template <typename typeT>
void CircularQueue<typeT>::Enqueue(typeT item) {
    if (this->m_size == QUEUE_MAX_SIZE)
        throw queexcpt::QueueOverflow();

    this->m_queue[this->m_back] = item;
    this->m_back = (this->m_back + 1) % QUEUE_MAX_SIZE;
    this->m_size++;
}

// Remove o primeiro item da fila
template <typename typeT>
typeT CircularQueue<typeT>::Dequeue() {
    if (this->m_size == 0)
        throw queexcpt::QueueIsEmpty();

    typeT element = this->m_queue[this->m_front];
    this->m_front = (this->m_front + 1) % QUEUE_MAX_SIZE;
    this->m_size--;
    return element;
}

// Limpa a fila
template <typename typeT>
void CircularQueue<typeT>::Clear() {
    this->m_size = 0;
    this->m_front = 0;
    this->m_back = 0;
}

#endif // QUEUE_H_
