/*
* Filename: priority_queue_max_slkd.h
* Created on: June 27, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Implementação da fila de prioridade máxima em cima de uma lista ligada
*
* Complexidade no pior caso:
* Enqueue: O(n)
* Dequeue: O(1)
* Peek:    O(1)
*/

#ifndef PRIORITY_QUEUE_MAX_SLKD_H_
#define PRIORITY_QUEUE_MAX_SLKD_H_

#include "node_slkd.h"
#include "priority_queue.h"
#include "queue_excpt.h"

// Singly linked namespace
namespace slkd {
    template<typename typeT>
    class MaxPQueue : public PriorityQueue<typeT> {
        private:
            slkd::Node<typeT> *m_head;
            unsigned int m_size;

            /**
            * @brief Remove o primeiro elemento da fila
            **/
            void RemoveHead();

        public:
            MaxPQueue();

            ~MaxPQueue();

            /**
            * @brief Insere um novo elemento na fila
            * @param element Novo elemento
            **/
            void Enqueue(typeT element) override;

            /**
            * @brief Pega o elemento de maior prioridade, sem removê-lo
            * @return O elemento de maior prioridade
            **/
            typeT Peek() override;

            /**
            * @brief Deleta o elemento de maior prioridade
            * @return O elemento de maior prioridade */
            typeT Dequeue() override;

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
    MaxPQueue<typeT>::MaxPQueue() {
        this->m_head = nullptr;
        this->m_size = 0;
    }

    template<typename typeT>
    MaxPQueue<typeT>::~MaxPQueue() {
        this->Clear();
    }

    template<typename typeT>
    void MaxPQueue<typeT>::Enqueue(typeT element) {
        slkd::Node<typeT> *newNode = new slkd::Node<typeT>(element);

        // Caso 1: Elemento atual é o de maior prioridade
        if (this->m_head == nullptr or this->m_head->m_key < element) {
            newNode->m_next = this->m_head;
            this->m_head = newNode;
        }
        else {
            slkd::Node<typeT> *current = this->m_head;

            // Caso 2: Inserir no meio/fim da fila
            while (current->m_next != nullptr and current->m_next->m_key >= element)
                current = current->m_next;

            newNode->m_next = current->m_next;
            current->m_next = newNode;
        }
        this->m_size++;
    }

    template<typename typeT>
    typeT MaxPQueue<typeT>::Peek() {
        if (this->m_size == 0)
            throw queexcpt::QueueIsEmpty();

        return this->m_head->m_key;
    }

    template<typename typeT>
    typeT MaxPQueue<typeT>::Dequeue() {
        if (this->m_size == 0)
            throw queexcpt::QueueIsEmpty();

        typeT aux = this->m_head->m_key;
        RemoveHead();
        return aux;
    }

    template<typename typeT>
    bool MaxPQueue<typeT>::IsEmpty() {
        if (this->m_size == 0)
            return true;

        return false;
    }

    template<typename typeT>
    unsigned int MaxPQueue<typeT>::Size() {
        return this->m_size;
    }

    template<typename typeT>
    void MaxPQueue<typeT>::Clear() {
        while (!this->IsEmpty())
            this->RemoveHead();
    }

    template<typename typeT>
    void MaxPQueue<typeT>::RemoveHead() {
        if (this->m_head) {
            slkd::Node<typeT> *aux;

            aux = this->m_head;
            this->m_head = this->m_head->m_next;

            this->m_size--;
            delete aux;
        }
    }
}

#endif // PRIORITY_QUEUE_MAX_SLKD_H_
