/*
 * Filename: circular_queue.h
 * Created on: May 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef CIRCULAR_QUEUE_H_
#define CIRCULAR_QUEUE_H_

#include "queue_base.h"
#include "queue_excpt.h"
#include <cstddef>

#define CIRCULAR_QUEUE_MAX_SIZE 1000

/**
 * @brief Implementation of a Circular Queue data structure
 *
 * This class represents a circular queue, also known as a ring buffer, which is a
 * type of data structure that follows the First-In-First-Out (FIFO) principle
 * It can store elements of type 'typeT'
 *
 * @tparam typeT The type of elements stored in the circular queue
 */
template<typename typeT>
class CircularQueue : QueueBase<typeT>
{
    private:
        std::size_t m_size, m_front, m_back;
        typeT       m_queue[CIRCULAR_QUEUE_MAX_SIZE];

    public:
        CircularQueue();

        ~CircularQueue();

        /**
         * @brief Insert a new element into the queue
         * @param element New element
         **/
        void Enqueue(typeT element) override;

        /**
         * @brief Get the element at the front of the queue
         * @return The element at the front of the queue
         **/
        typeT Peek() override;

        /**
         * @brief Remove and return the element at the front of the queue
         * @return The element at the front of the queue
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
CircularQueue<typeT>::CircularQueue()
{
    this->m_size = this->m_front = this->m_back = 0;
}

template<typename typeT>
CircularQueue<typeT>::~CircularQueue()
{ }

template<typename typeT>
void CircularQueue<typeT>::Enqueue(typeT item)
{
    if (this->m_size == CIRCULAR_QUEUE_MAX_SIZE)
        throw queexcpt::QueueOverflow();

    this->m_queue[this->m_back] = item;

    this->m_back = (this->m_back + 1) % CIRCULAR_QUEUE_MAX_SIZE;
    this->m_size++;
}

template<typename typeT>
typeT CircularQueue<typeT>::Peek()
{
    if (this->IsEmpty())
        throw queexcpt::QueueIsEmpty();

    return this->m_queue[this->m_front];
}

template<typename typeT>
typeT CircularQueue<typeT>::Dequeue()
{
    if (this->IsEmpty())
        throw queexcpt::QueueIsEmpty();

    typeT element = this->m_queue[this->m_front];
    this->m_front = (this->m_front + 1) % CIRCULAR_QUEUE_MAX_SIZE;
    this->m_size--;
    return element;
}

template<typename typeT>
bool CircularQueue<typeT>::IsEmpty()
{
    return (this->m_size == 0);
}

template<typename typeT>
std::size_t CircularQueue<typeT>::Size()
{
    return this->m_size;
}

template<typename typeT>
void CircularQueue<typeT>::Clear()
{
    this->m_size = this->m_front = this->m_back = 0;
}

#endif // CIRCULAR_QUEUE_H_
