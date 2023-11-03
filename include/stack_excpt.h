/*
 * Filename: stack_excpt.h
 * Created on: May 13, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef STACK_EXCPT_H_
#define STACK_EXCPT_H_

#include <exception>
#include <string>

// stack exception namespace
namespace stkexcpt
{
    class StackOverflow : public std::exception
    {
        public:
            const char* what() const throw();
    };

    class StackIsEmpty : public std::exception
    {
        public:
            const char* what() const throw();
    };
} // namespace stkexcpt

#endif // STACK_EXCPT_H_
