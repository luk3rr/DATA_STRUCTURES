/*
* Filename: node_doubly_linked.h
* Created on: May 12, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

// Doubly linked namespace
namespace dlkd {
    template <typename typeT>
    struct Node {
        typeT m_key;
        Node<typeT> *m_left;
        Node<typeT> *m_right;

        Node(typeT &k) : m_key(k), m_left(nullptr), m_right(nullptr) { }
        Node(Node *left, typeT &k) : m_key(k), m_left(left), m_right(nullptr) { }
        Node(typeT &k, Node *right) : m_key(k), m_left(nullptr), m_right(right) { }
        Node(typeT &k, Node *left, Node *right) : m_key(k), m_left(left), m_right(right) { }
    };
}
