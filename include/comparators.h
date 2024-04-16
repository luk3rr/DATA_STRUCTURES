/*
 * Filename: comparators.h
 * Created on: April 16, 2024
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#ifndef COMPARATORS_H_
#define COMPARATORS_H_

namespace comparators
{
    /**
     * @brief A function object to compare two values using less-than operator
     */
    template<typename typeT>
    auto less = [](const typeT& a, const typeT& b) -> bool { return a < b; };

    /**
     * @brief A function object to compare two values using greater-than operator
     */
    template<typename typeT>
    auto greater = [](const typeT& a, const typeT& b) { return a > b; };

    /**
     * @brief A function object to compare two values for equality
     */
    template<typename typeT>
    auto equal = [](const typeT& a, const typeT& b) { return a == b; };

} // namespace comparators

#endif // COMPARATORS_H_
