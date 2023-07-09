/*
* Filename: queue_slkd.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
*
* Implementação da fila cima de uma lista ligada
*
* Implementação com complexidade no pior caso:
* Enqueue: O(1)
* Dequeue: O(1)
* Peek:    O(1)
*/

#ifndef QUEUE_SLKD_H_
#define QUEUE_SLKD_H_

#include "node_slkd.h"
#include "queue_excpt.h"

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    class Queue {
        private:
            Node<typeT> *m_first;
            Node<typeT> *m_last;
            int m_size;

            /**
            @brief Deleta o primeiro nó da fila
            @throw queexcpt::QueueIsEmpty Caso a fila esteja vazia
            */
            void DeleteFirst();

        public:
            Queue();

            ~Queue();

            /**
            @brief Quantidade de elementos na fila
            @return A quantidade de elementos na fila (tamanho)
            */
            int Size();

            /**
            @brief Enfileira um elemento
            @param element Elemento que será enfileirado
            */
            void Enqueue(typeT element);

            /**
            @brief Verifica se a fila está vazia
            @return True se a fila estiver vazia, False caso contrário
            */
            bool IsEmpty();

            /**
            @brief Desenfileira um elemento
            @return Primeira elemento da fila
            @throw queexcpt::QueueIsEmpty Caso a fila esteja vazia
            */
            typeT Dequeue();

            /**
            @brief Remove todos os elementos da fila
            */
            void Clear();
    };

    template <typename typeT>
    Queue<typeT>::Queue() {
        this->m_size = 0;
        this->m_first = this->m_last = nullptr;
    }

    template <typename typeT>
    Queue<typeT>::~Queue() {
        this->Clear();
    }

    template <typename typeT>
    int Queue<typeT>::Size() {
        return this->m_size;
    }

    template <typename typeT>
    bool Queue<typeT>::IsEmpty() {
        if (this->m_size == 0) return true;
        return false;
    }

    template <typename typeT>
    void Queue<typeT>::Enqueue(typeT element) {
        if (this->IsEmpty()) {
            this->m_first = this->m_last = new Node<typeT>(element);
        }
        else {
            Node<typeT> *aux = new Node<typeT>(element);
            this->m_last->m_next = aux;
            this->m_last = aux;
        }
        this->m_size++;
    }

    template <typename typeT>
    void Queue<typeT>::DeleteFirst() {
        if (this->IsEmpty())
            throw queexcpt::QueueIsEmpty();

        Node<typeT> *toDelete = this->m_first;
        this->m_first = this->m_first->m_next;
        delete toDelete;
        this->m_size--;
    }

    template <typename typeT>
    typeT Queue<typeT>::Dequeue() {
        if (this->IsEmpty())
            throw queexcpt::QueueIsEmpty();

        typeT element = this->m_first->m_key;
        this->DeleteFirst();
        return element;
    }

    template <typename typeT>
    void Queue<typeT>::Clear() {
        while (!this->IsEmpty()) {
            this->DeleteFirst();
        }
    }
}

#endif // QUEUE_SLKD_H_
