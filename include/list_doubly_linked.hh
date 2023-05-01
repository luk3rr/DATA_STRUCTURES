#ifndef LIST_DOUBLY_LINKED_H_
#define LIST_DOUBLY_LINKED_H_

#include <iostream>

#include "list_excpt.hh"
#include "node_doubly_linked.hh"

// Doubly linked namespace
namespace dlkd {
    template<typename typeT>
    class List {
        private:
            Node<typeT> *_head;
            Node<typeT> *_tail;
            int _size_of;

            /**
            @brief Remove um nó da lista
            @param node Ponteiro para o nó
            */
            void remove(Node<typeT> *node);

            /**
            @brief Busca pelo nó que contém a chave
            @param key Chave que será procurada
            @param Próximo nó de busca
            @return Ponteiro para o nó que contém a chave
            */
            Node<typeT>* search(Node<typeT> *&node, typeT &key);

        public:
            List();

            ~List();

            /**
            @brief Esvazia toda a lista
            */
            void clean();

            /**
            @brief Retorna a quantidade de chaves armazenadas na lista
            */
            int size();

            /**
            @brief Retorna um booleano para indicar se a lista está ou não vazia
            */
            bool isEmpty();

            /**
            @brief Inseri uma nova chave na lista
            @param key Valor que será armazenado
            */
            void push_back(typeT key);

            /**
            @brief Remove uma chave da lista
            @param key Valor que será removido
            */
            void remove(typeT key);

            /**
            @brief Busca pelo nó que contém a chave
            @param key Chave que será procurada
            @return Ponteiro para o nó que contém a chave
            */
            Node<typeT>* search(typeT &key);

            /**
            @brief Retorna o primeiro elemento da lista
            @return Chave do primeiro elemento da lista
            */
            typeT front();

            /**
            @brief Retorna o último elemento da lista
            @return Chave do último elemento da lista
            */
            typeT back();

            /**
            @brief Percorre a lista e imprime todas as chaves
            */
            void print();
    };

    template<typename typeT>
    List<typeT>::List() {
        this->_head = nullptr;
        this->_tail = nullptr;
        this->_size_of = 0;
    }

    template<typename typeT>
    List<typeT>::~List() {
        this->clean();
    }

    template<typename typeT>
    void List<typeT>::clean() {
        while (!this->isEmpty()) {
            this->remove(this->_head);
        }
    }

    template<typename typeT>
    int List<typeT>::size() {
        return this->_size_of;
    }

    template<typename typeT>
    bool List<typeT>::isEmpty() {
        if (this->_size_of == 0)
            return true;

        else
            return false;
    }

    template<typename typeT>
    void List<typeT>::push_back(typeT key) {
        if (this->_head == nullptr) {
            this->_head = this->_tail = new Node<typeT>(key);
        }
        else {
            this->_tail->_right = new Node<typeT>(this->_tail, key);
            this->_tail = this->_tail->_right;
        }
        this->_size_of++;
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::search(typeT &key) {
        if (this->_size_of == 0)
            return nullptr;

        if (this->_head->_key == key)
            return this->_head;

        else
            return search(this->_head->_right, key);
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::search(Node<typeT> *&node, typeT &key) {
        if (node == nullptr)
            return nullptr;

        if (node->_key == key)
            return node;

        else
            return search(node->_right, key);
    }

    template<typename typeT>
    void List<typeT>::remove(typeT key) {
        Node<typeT> *node = this->search(key);
        this->remove(node);
    }

    template<typename typeT>
    void List<typeT>::remove(Node<typeT> *node) {
        if (node == nullptr)
            return;

        if (node == this->_head and node == this->_tail) {
            this->_head = nullptr;
            this->_tail = nullptr;
        }
        else if (node == this->_head) {
            this->_head = node->_right;
            this->_head->_left = nullptr;
        }
        else if (node == this->_tail) {
            this->_tail = this->_tail->_left;
            this->_tail->_right = nullptr;
        }
        else {
            node->_left->_right = node->_right;
            node->_right->_left = node->_left;
        }

        delete node;
        this->_size_of--;
    }

    template<typename typeT>
    typeT List<typeT>::front() {
        if (this->isEmpty())
            throw lstexcpt::ListIsEmpty();

        return
            this->_head->_key;
    }

    template<typename typeT>
    typeT List<typeT>::back() {
        if (this->isEmpty())
            throw lstexcpt::ListIsEmpty();

        return
            this->_tail->_key;
    }

    template<typename typeT>
    void List<typeT>::print() {
        if (this->isEmpty())
            throw lstexcpt::ListIsEmpty();

        Node<typeT> *nodeAux = this->_head;
        while (nodeAux != nullptr) {
            std::cout << " " << nodeAux->_key;
            nodeAux = nodeAux->_right;
        }
    }
}

#endif // LIST_DOUBLY_LINKED_H_
