/*
 * Filename: queue_slkd.h
 * Created on: May 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef QUEUE_SLKD_H_
#define QUEUE_SLKD_H_

#include <cstddef>
#include <stdexcept>

#include "node.h"
#include "queue_base.h"

// Singly linked namespace
namespace slkd
{
    /**
     * @brief Implementation of a queue using a singly-linked list
     *
     * This class implements a queue data structure on top of a singly-linked list. It
     * offers efficient enqueue, dequeue, and peek operations
     *
     * Implementation with worst-case time complexities:
     * - Enqueue: O(1)
     * - Dequeue: O(1)
     * - Peek: O(1)
     *
     * @tparam typeT The type of elements stored in the queue
     */
    template<typename typeT>
    class Queue : QueueBase<typeT>
    {
        private:
            Node<typeT>* m_first;
            Node<typeT>* m_last;
            std::size_t  m_size;

            /**
             * @brief Deletes the first node from the queue
             * @throw std::underflow_error If queue is empty
             */
            void DeleteFirst();

        public:
            Queue();

            ~Queue();

            /**
             * @brief Insert a new element into the queue
             * @param element New element
             **/
            void Enqueue(typeT element) override;

            /**
             * @brief Get the element at the front of the queue
             * @return The element at the front of the queue
             * @throw std::overflow_error If queue is empty
             **/
            typeT Peek() override;

            /**
             * @brief Remove and return the element at the front of the queue
             * @return The element at the front of the queue
             * @throw std::underflow_error If queue is empty
             **/
            typeT Dequeue() override;

            /**
             * @brief Check if the queue is empty
             * @return True if it is empty, False otherwis
             **/
            bool IsEmpty() override;

            /**
             * @brief Get the current size of the queue
             * @return The current size of the queue
             **/
            std::size_t Size() override;

            /**
             * @brief Delete all nodes in the queue
             **/
            void Clear() override;
    };

    template<typename typeT>
    Queue<typeT>::Queue()
    {
        this->m_size  = 0;
        this->m_first = this->m_last = nullptr;
    }

    template<typename typeT>
    Queue<typeT>::~Queue()
    {
        this->Clear();
    }

    template<typename typeT>
    void Queue<typeT>::Enqueue(typeT element)
    {
        if (this->IsEmpty())
        {
            this->m_first = this->m_last = new Node<typeT>(element);
        }
        else
        {
            Node<typeT>* aux = new Node<typeT>(element);
            this->m_last->SetNextNode(aux);
            this->m_last = aux;
        }
        this->m_size++;
    }

    template<typename typeT>
    typeT Queue<typeT>::Peek()
    {
        if (this->IsEmpty())
            throw std::overflow_error("Queue is empty!");

        return this->m_first->GetValue();
    }

    template<typename typeT>
    typeT Queue<typeT>::Dequeue()
    {
        if (this->IsEmpty())
            throw std::underflow_error("Queue is empty!");

        typeT element = this->m_first->GetValue();
        this->DeleteFirst();
        return element;
    }

    template<typename typeT>
    bool Queue<typeT>::IsEmpty()
    {
        return (this->m_size == 0);
    }

    template<typename typeT>
    std::size_t Queue<typeT>::Size()
    {
        return this->m_size;
    }

    template<typename typeT>
    void Queue<typeT>::Clear()
    {
        while (not this->IsEmpty())
        {
            this->DeleteFirst();
        }
    }

    template<typename typeT>
    void Queue<typeT>::DeleteFirst()
    {
        if (this->IsEmpty())
            throw std::underflow_error("Queue is empty!");

        Node<typeT>* toDelete = this->m_first;
        this->m_first         = this->m_first->GetNextNode();
        delete toDelete;
        this->m_size--;
    }

} // namespace slkd

#endif // QUEUE_SLKD_H_
