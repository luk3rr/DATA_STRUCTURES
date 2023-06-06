/*
* Filename: list_doubly_linked.h
* Created on: May 13, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef LIST_DOUBLY_LINKED_H_
#define LIST_DOUBLY_LINKED_H_

#include <iostream>

#include "list_excpt.h"
#include "node_doubly_linked.h"

// Doubly linked namespace
namespace dlkd {
    template<typename typeT>
    class List {
        private:
            Node<typeT> *m_head;
            Node<typeT> *m_tail;
            int m_size;

            /**
            @brief Remove um nó da lista
            @param node Ponteiro para o nó
            */
            void Remove(Node<typeT> *node);

            /**
            @brief Busca pelo nó que contém a chave
            @param key Chave que será procurada
            @param Próximo nó de busca
            @return Ponteiro para o nó que contém a chave
            */
            Node<typeT>* Search(Node<typeT> *&node, typeT &key);

        public:
            List();

            ~List();

            /**
            @brief Pega a quantidade de chaves armazenadas na lista
            @return A quantidade de chaves
            */
            int Size();

            /**
            @brief Verifica se a lista está vazia
            @return True se a lista estiver vazia, False caso contrário
            */
            bool IsEmpty();

            /**
            @brief Inseri uma nova chave na lista
            @param key Valor que será armazenado
            */
            void PushBack(typeT key);

            /**
            @brief Remove uma chave da lista
            @param key Valor que será removido
            */
            void Remove(typeT key);

            /**
            @brief Esvazia toda a lista
            */
            void Clear();

            /**
            @brief Busca pelo nó que contém a chave
            @param key Chave que será procurada
            @return Ponteiro para o nó que contém a chave
            */
            Node<typeT>* Search(typeT &key);

            /**
            @brief Retorna o primeiro elemento da lista
            @return Chave do primeiro elemento da lista
            */
            typeT Front();

            /**
            @brief Retorna o último elemento da lista
            @return Chave do último elemento da lista
            */
            typeT Back();

            /**
            @brief Percorre a lista e imprime todas as chaves
            */
            void Print();
    };

    template<typename typeT>
    List<typeT>::List() {
        this->m_head = nullptr;
        this->m_tail = nullptr;
        this->m_size = 0;
    }

    template<typename typeT>
    List<typeT>::~List() {
        this->Clear();
    }

    template<typename typeT>
    int List<typeT>::Size() {
        return this->m_size;
    }

    template<typename typeT>
    bool List<typeT>::IsEmpty() {
        if (this->m_size == 0)
            return true;

        else
            return false;
    }

    template<typename typeT>
    void List<typeT>::PushBack(typeT key) {
        if (this->m_head == nullptr) {
            this->m_head = this->m_tail = new Node<typeT>(key);
        }
        else {
            this->m_tail->m_right = new Node<typeT>(this->m_tail, key);
            this->m_tail = this->m_tail->m_right;
        }
        this->m_size++;
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::Search(typeT &key) {
        if (this->m_size == 0)
            return nullptr;

        if (this->m_head->m_key == key)
            return this->m_head;

        else
            return this->Search(this->m_head->m_right, key);
    }

    template<typename typeT>
    Node<typeT>* List<typeT>::Search(Node<typeT> *&node, typeT &key) {
        if (node == nullptr)
            return nullptr;

        if (node->m_key == key)
            return node;

        else
            return this->Search(node->m_right, key);
    }

    template<typename typeT>
    void List<typeT>::Remove(typeT key) {
        Node<typeT> *node = this->Search(key);
        this->Remove(node);
    }

    template<typename typeT>
    void List<typeT>::Remove(Node<typeT> *node) {
        if (node == nullptr)
            return;

        if (node == this->m_head and node == this->m_tail) {
            this->m_head = nullptr;
            this->m_tail = nullptr;
        }
        else if (node == this->m_head) {
            this->m_head = node->m_right;
            this->m_head->m_left = nullptr;
        }
        else if (node == this->m_tail) {
            this->m_tail = this->m_tail->m_left;
            this->m_tail->m_right = nullptr;
        }
        else {
            node->m_left->m_right = node->m_right;
            node->m_right->m_left = node->m_left;
        }

        delete node;
        this->m_size--;
    }

    template<typename typeT>
    void List<typeT>::Clear() {
        while (!this->IsEmpty()) {
            this->Remove(this->m_head);
        }
    }

    template<typename typeT>
    typeT List<typeT>::Front() {
        if (this->IsEmpty())
            throw lstexcpt::ListIsEmpty();

        return
            this->m_head->m_key;
    }

    template<typename typeT>
    typeT List<typeT>::Back() {
        if (this->IsEmpty())
            throw lstexcpt::ListIsEmpty();

        return
            this->m_tail->m_key;
    }

    template<typename typeT>
    void List<typeT>::Print() {
        if (this->IsEmpty())
            throw lstexcpt::ListIsEmpty();

        Node<typeT> *nodeAux = this->m_head;
        while (nodeAux != nullptr) {
            std::cout << " " << nodeAux->m_key;
            nodeAux = nodeAux->m_right;
        }
    }
}

#endif // LIST_DOUBLY_LINKED_H_
