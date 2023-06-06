/*
* Filename: queue_excpt.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef QUEUE_EXCPT_H_
#define QUEUE_EXCPT_H_

#include <exception>

namespace queexcpt {
    class QueueOverflow : public std::exception {
            public:
            const char *what() const throw();
    };

    class QueueIsEmpty : public std::exception {
          public:
            const char *what() const throw();
    };
} // namespace queexcpt

#endif // QUEUE_EXCPT_H_
