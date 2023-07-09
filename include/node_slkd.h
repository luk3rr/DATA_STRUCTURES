/*
* Filename: node_slkd.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef NODE_SLKD_H_
#define NODE_SLKD_H_

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    struct Node {
        typeT m_key;
        Node<typeT> *m_next;

        Node(typeT &k) : m_key(k), m_next(nullptr) { }
        Node(typeT &k, Node *next) : m_key(k), m_next(next) { }
    };
}

#endif // NODE_SLKD_H_
