/*
* Filename: map_excpt.h
* Created on: June 28, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef MAP_EXCPT_H_
#define MAP_EXCPT_H_

#include <exception>
#include <string>

namespace mapexcpt {
    class MapIsEmpty : public std::exception {
        public:
            const char *what() const throw();
    };
}

#endif // MAP_EXCPT_H_
