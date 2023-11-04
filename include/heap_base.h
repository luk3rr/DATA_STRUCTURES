/*
 * Filename: heap_base.h
 * Created on: November  3, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef HEAP_BASE_H_
#define HEAP_BASE_H_

#include <cstddef>

/**
 * @brief Base class for Heap
 *
 * This class serves as a base class for a heap and defines a set of
 * common operations for pushing, peeking, popping, checking if it's empty,
 * and determining its size. Derived classes implement specific heap behaviors.
 *
 * @tparam typeT The type of elements that the heap can store
 */
template<typename typeT>
class HeapBase
{
    public:
        virtual void HeapifyDown(std::size_t index) = 0;

        virtual void HeapifyUp(std::size_t index) = 0;

        virtual void Push(typeT key) = 0;

        virtual typeT Peek() = 0;

        virtual typeT Pop() = 0;

        virtual bool IsEmpty() = 0;

        virtual std::size_t Size() = 0;

        virtual void Clear() = 0;
};

#endif // HEAP_BASE_H_
