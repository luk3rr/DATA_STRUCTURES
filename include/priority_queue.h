/*
* Filename: priority_queue.h
* Created on: June 27, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Priority Queue base class
*/

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "utils.h"

template<typename typeT, typename Compare = utils::less<typeT>>
class PriorityQueueBase
{
    public:
        virtual void Enqueue(typeT key) = 0;

        virtual typeT Peek() = 0;

        virtual typeT Dequeue() = 0;

        virtual bool IsEmpty() = 0;

        virtual unsigned int Size() = 0;
};

#endif // PRIORITY_QUEUE_H_
