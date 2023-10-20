/*
* Filename: priority_queue_heap.h
* Created on: July  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Implementação da fila de prioridade mínima/máxima em cima de um heap
* OBS.: Por default a fila de prioridade é mínima. Para utilizar a máxima, use o template Compare
*       com um comparador customizado do "typeT"
*
* Complexidade no pior caso:
* Enqueue: O(1 + log n) -> log n é o tempo de execução do HeapifyDown
* Dequeue: O(1 + log n) -> log n é o tempo de execução do HeapifyUp
* Peek:    O(1)
*/

#ifndef PRIORITY_QUEUE_HEAP_H_
#define PRIORITY_QUEUE_HEAP_H_

#include "priority_queue.h"
#include "queue_excpt.h"
#include "vector.h"

// Heap namespace
namespace heap {
    template <typename typeT, typename Compare = utils::less<typeT>>
    class PriorityQueue : public PriorityQueueBase<typeT> {
        private:
            Vector<typeT> m_heap;
            Compare m_comp; // Custom comparator

            /**
             * @brief Reajusta o heap após a remoção de um elemento
             * @param index Índice do elemento que foi removido
             **/
            void HeapifyDown(unsigned int index);

            /**
             * @brief Reajusta o heap após a inserção de um elemento
             * @param index Índice do elemento que foi inserido
             **/
            void HeapifyUp(unsigned int index);

        public:
            /**
             * @brief Constructor for PriorityQueue
             * @param comp The custom comparator to use (default is the standard comparator)
             */
            PriorityQueue(const Compare& comp = Compare());
            ~PriorityQueue();

            /**
            * @brief Insere um novo elemento na fila
            * @param element Novo elemento
            **/
            void Enqueue(typeT element) override;

            /**
            * @brief Pega o elemento de menor prioridade, sem removê-lo
            * @return O elemento de menor prioridade
            **/
            typeT Peek() override;

            /**
            * @brief Deleta o elemento de menor prioridade
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

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::PriorityQueue(const Compare& comp) : m_comp(comp) { }

    template<typename typeT, typename Compare>
    PriorityQueue<typeT, Compare>::~PriorityQueue() { }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::HeapifyDown(unsigned int index) {
        unsigned int left = 2 * index + 1;
        unsigned int right = 2 * index + 2;
        unsigned int largest = index;

        if (left < this->m_heap.Size() and this->m_comp(this->m_heap[left], this->m_heap[largest]))
            largest = left;

        if (right < this->m_heap.Size() and this->m_comp(this->m_heap[right], this->m_heap[largest]))
            largest = right;

        if (largest != index) {
            this->m_heap.Swap(index, largest);
            this->HeapifyDown(largest);
        }
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::HeapifyUp(unsigned int index) {
        unsigned int parent = (index - 1) / 2;

        while (index > 0 and this->m_comp(this->m_heap[index], this->m_heap[parent])) {
            this->m_heap.Swap(index, parent);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Enqueue(typeT element) {
        this->m_heap.PushBack(element);
        this->HeapifyUp(this->m_heap.Size() - 1);
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Peek() {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        return this->m_heap[0];
    }

    template<typename typeT, typename Compare>
    typeT PriorityQueue<typeT, Compare>::Dequeue() {
        if (this->m_heap.IsEmpty())
            throw queexcpt::QueueIsEmpty();

        typeT max = this->m_heap[0];
        this->m_heap.Swap(0, this->m_heap.Size() - 1);
        this->m_heap.PopBack();
        this->HeapifyDown(0);

        return max;
    }

    template<typename typeT, typename Compare>
    bool PriorityQueue<typeT, Compare>::IsEmpty() {
        return this->m_heap.IsEmpty();
    }

    template<typename typeT, typename Compare>
    unsigned int PriorityQueue<typeT, Compare>::Size() {
        return this->m_heap.Size();
    }

    template<typename typeT, typename Compare>
    void PriorityQueue<typeT, Compare>::Clear() {
        this->m_heap.Clear();
    }
}

#endif // PRIORITY_QUEUE_HEAP_H_
