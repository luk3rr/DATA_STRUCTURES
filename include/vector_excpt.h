/*
* Filename: vector_excpt.h
* Created on: June  5, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef VECTOR_EXCPT_H_
#define VECTOR_EXCPT_H_

#include <exception>
#include <string>

// vector exception namespace
namespace vecexcpt {
    class InvalidIndex : public std::exception {
        public:
            const char *what() const throw();
    };

} // namespace vecexcpt

#endif // VECTOR_EXCPT_H_
