/*
* Filename: priority_queue_min.h
* Created on: June 27, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef PRIORITY_QUEUE_MIN_H_
#define PRIORITY_QUEUE_MIN_H_

#include "node_singly_linked.h"
#include "priority_queue.h"
#include "queue_excpt.h"

/**
 * Implementação com complexidade no pior caso:
 * Insert: O(n)
 * Delete: O(1)
 * Get:    O(1)
 *
 * OBS.: Implementação com Heap teria:
 * Insert: O(1 + log n)
 * Delete: O(2 * log n)
 * Get:    O(2 * log n)
 **/

template<typename typeT>
class MinPQueue : public PriorityQueue<typeT> {
    private:
        slkd::Node<typeT> *m_head;
        unsigned int m_size;

        /**
         * @brief Remove o primeiro elemento da fila
         **/
        void RemoveHead();

    public:
        MinPQueue();

        ~MinPQueue();

        /**
         * @brief Insere um novo elemento na fila
         * @param element Novo elemento
         **/
        void Insert(typeT newNode) override;

        /**
         * @brief Pega o elemento de menor prioridade
         * @return O elemento de menor prioridade
         **/
        typeT Get() override;

        /**
         * @brief Deleta o elemento de menor prioridade
         * @return O elemento de menor prioridade
         **/
        typeT Delete() override;

        /**
         * @brief Verificar se a fila está vazia
         * @return True se estiver vazia, False caso contrário
         **/
        bool IsEmpty() override;

        /**
         * @brief Pega o tamanho atual da fila
         * @return O tamanho atual da fila
         **/
        unsigned int Size() override;

        /**
         * @brief Deleta todos os nós da fila
         **/
        void Clear();
};

template<typename typeT>
MinPQueue<typeT>::MinPQueue() {
    this->m_head = nullptr;
    this->m_size = 0;
}

template<typename typeT>
MinPQueue<typeT>::~MinPQueue() {
    this->Clear();
}

template<typename typeT>
void MinPQueue<typeT>::Insert(typeT huffNode) {
    slkd::Node<typeT> *newNode = new slkd::Node<typeT>(huffNode);

    // Caso 1: Elemento atual é o de menor prioridade
    if (this->m_head == nullptr or this->m_head->m_key->m_freq > newNode->m_key->m_freq) {
        newNode->m_next = this->m_head;
        this->m_head = newNode;
    }
    else {
        slkd::Node<typeT> *current = this->m_head;

        // Caso 2: Inserir no meio/fim da fila
        while (current->m_next != nullptr and current->m_key->m_freq <= newNode->m_key->m_freq)
            current = current->m_next;

        newNode->m_next = current->m_next;
        current->m_next = newNode;
    }
    this->m_size++;
}

template<typename typeT>
typeT MinPQueue<typeT>::Get() {
    if (this->m_size == 0)
        throw queexcpt::QueueIsEmpty();

    return this->m_head->m_key;
}

template<typename typeT>
typeT MinPQueue<typeT>::Delete() {
    if (this->m_size == 0)
        throw queexcpt::QueueIsEmpty();

    typeT aux = this->m_head->m_key;
    RemoveHead();
    return aux;
}

template<typename typeT>
bool MinPQueue<typeT>::IsEmpty() {
    if (this->m_size == 0)
        return true;

    return false;
}

template<typename typeT>
unsigned int MinPQueue<typeT>::Size() {
    return this->m_size;
}

template<typename typeT>
void MinPQueue<typeT>::Clear() {
    while (not this->IsEmpty())
        this->RemoveHead();
}

template<typename typeT>
void MinPQueue<typeT>::RemoveHead() {
    if (this->m_head) {
        slkd::Node<typeT> *aux;

        aux = this->m_head;
        this->m_head = this->m_head->m_next;

        this->m_size--;
        delete aux;
    }
}

#endif // PRIORITY_QUEUE_MIN_H_
