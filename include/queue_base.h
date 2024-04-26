/*
 * Filename: queue_base.h
 * Created on: June 27, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef QUEUE_BASE_H_
#define QUEUE_BASE_H_

#include <cstddef>

/**
 * @brief Base class for Queue
 *
 * This class serves as a base class for a queue and defines a set of
 * common operations for enqueuing, peeking, dequeuing, checking if it's empty,
 * and determining its size. Derived classes implement specific priority queue
 * behaviors
 *
 * @tparam typeT The type of elements that the queue can store
 */
template<typename typeT>
class QueueBase
{
    public:
        virtual void Enqueue(typeT key) = 0;

        virtual typeT Peek() = 0;

        virtual typeT Dequeue() = 0;

        virtual bool IsEmpty() = 0;

        virtual std::size_t Size() = 0;

        virtual void Clear() = 0;
};

#endif // QUEUE_BASE_H_
