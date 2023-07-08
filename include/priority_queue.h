/*
* Filename: priority_queue.h
* Created on: June 27, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "node_singly_linked.h"

template<typename typeT>
class PriorityQueue {
    public:
        virtual void Insert(typeT key) = 0;

        virtual typeT Get() = 0;

        virtual typeT Delete() = 0;

        virtual bool IsEmpty() = 0;

        virtual unsigned int Size() = 0;
};

#endif // PRIORITY_QUEUE_H_
