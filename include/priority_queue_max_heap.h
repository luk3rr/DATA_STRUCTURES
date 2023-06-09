/*
* Filename: priority_queue_max_heap.h
* Created on: July  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Implementação da fila de prioridade máxima em cima de um heap
*
* Complexidade no pior caso:
* Enqueue: O(1 + log n) -> log n é o tempo de execução do MaxHeapifyDown
* Dequeue: O(1 + log n) -> log n é o tempo de execução do MaxHeapifyUp
* Peek:    O(1)
*/

#ifndef PRIORITY_QUEUE_MAX_HEAP_H_
#define PRIORITY_QUEUE_MAX_HEAP_H_

#include "priority_queue.h"
#include "queue_excpt.h"
#include "vector.h"

// Heap namespace
namespace heap {
    template <typename typeT>
    class MaxPQueue : public PriorityQueue<typeT> {
        private:
            Vector<typeT> m_heap;

            /**
             * @brief Reajusta o heap após a remoção de um elemento
             * @param index Índice do elemento que foi removido
             **/
            void MaxHeapifyDown(unsigned int index);

            /**
             * @brief Reajusta o heap após a inserção de um elemento
             * @param index Índice do elemento que foi inserido
             **/
            void MaxHeapifyUp(unsigned int index);

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
            * @return O elemento de menor prioridade
            **/
            typeT Peek() override;

            /**
            * @brief Deleta o elemento de maior prioridade
            * @return O elemento de menor prioridade
            **/
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
    MaxPQueue<typeT>::MaxPQueue() { }

    template<typename typeT>
    MaxPQueue<typeT>::~MaxPQueue() { }

    template<typename typeT>
    void MaxPQueue<typeT>::MaxHeapifyDown(unsigned int index) {
        unsigned int left = 2 * index + 1;
        unsigned int right = 2 * index + 2;
        unsigned int largest = index;

        if (left < this->m_heap.Size() and this->m_heap[left] > this->m_heap[largest])
            largest = left;

        if (right < this->m_heap.Size() and this->m_heap[right] > this->m_heap[largest])
            largest = right;

        if (largest != index) {
            this->m_heap.Swap(index, largest);
            this->MaxHeapifyDown(largest);
        }
    }

    template<typename typeT>
    void MaxPQueue<typeT>::MaxHeapifyUp(unsigned int index) {
        unsigned int parent = (index - 1) / 2;

        while (index > 0 and this->m_heap[index] > this->m_heap[parent]) {
            this->m_heap.Swap(index, parent);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    template<typename typeT>
    void MaxPQueue<typeT>::Enqueue(typeT element) {
        this->m_heap.PushBack(element);
        this->MaxHeapifyUp(this->m_heap.Size() - 1);
    }

    template<typename typeT>
    typeT MaxPQueue<typeT>::Peek() {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        return this->m_heap[0];
    }

    template<typename typeT>
    typeT MaxPQueue<typeT>::Dequeue() {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        typeT max = this->m_heap[0];
        this->m_heap.Swap(0, this->m_heap.Size() - 1);
        this->m_heap.PopBack();
        this->MaxHeapifyDown(0);

        return max;
    }

    template<typename typeT>
    bool MaxPQueue<typeT>::IsEmpty() {
        return this->m_heap.IsEmpty();
    }

    template<typename typeT>
    unsigned int MaxPQueue<typeT>::Size() {
        return this->m_heap.Size();
    }

    template<typename typeT>
    void MaxPQueue<typeT>::Clear() {
        this->m_heap.Clear();
    }
}

#endif // PRIORITY_QUEUE_MAX_HEAP_H_
