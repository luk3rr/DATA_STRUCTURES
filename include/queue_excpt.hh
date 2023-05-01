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
