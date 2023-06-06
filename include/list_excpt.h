/*
* Filename: list_excpt.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef LIST_EXCPT_H_
#define LIST_EXCPT_H_

#include <exception>
#include <string>

// list except namespace
namespace lstexcpt {
    class ListIsEmpty : public std::exception {
          public:
            const char *what() const throw();
    };
} // namespace lstexcpt

#endif // LIST_EXCPT_H_
