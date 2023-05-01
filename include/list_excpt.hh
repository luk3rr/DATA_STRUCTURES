#ifndef LISTEXCPT_H_
#define LISTEXCPT_H_

#include <exception>
#include <string>

// list except namespace
namespace lstexcpt {
    class ListIsEmpty : public std::exception {
          public:
            const char *what() const throw();
    };
    } // namespace lstexcpt

#endif // LISTEXCPT_H_
