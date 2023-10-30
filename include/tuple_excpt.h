/*
* Filename: tuple_excpt.h
* Created on: October 29, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef TUPLE_EXCPT_H_
#define TUPLE_EXCPT_H_

#include <exception>
#include <string>

// tuple exception namespace
namespace tplexcpt {
    class InvalidIndex : public std::exception
    {
        public:
            const char *what() const throw();
    };

} // namespace tplexcpt

#endif // TUPLE_EXCPT_H_
