/*
* Filename: binary_tree.h
* Created on: May 12, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <fstream>
#include <iostream>

#include "queue.h"
#include "utils.h"
#include "node_doubly_linked.h"

template <typename typeT>
class BinaryTree {
    private:
        dlkd::Node<typeT> *m_root;
        int m_nodes;

        /**
        @brief Verifica se um nó i é ancestral do nó j recursivamente
        @param node Ponteiro para o próximo nó da chamada recursiva
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool IsAncestorRecursive(dlkd::Node<typeT> *node, typeT i, typeT j);

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        @param level Nível do nó atual
        @param node Nó atual
        @param side, deve receber True se o nó está o lado esquerdo ou False, caso o nó esteja do lado direito
        */
        void DumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft);

        /**
        @brief Inserir um novo elemento na árvore
        @param key Chave do novo nó
        @param node Ponteiro para o próximo nó (função recursiva)
        */
        void Insert(dlkd::Node<typeT> *&node, typeT key);

        /**
        @brief Deleta toda a árvore
        @param node Nó atual que será deletado a cada chamada recursiva da função
        */
        void DeleteTree(dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void InorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void PostorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void PreorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

    public:
        BinaryTree();

        ~BinaryTree();

        /**
         @brief Busca um nó com uma determinada chave e retorna um ponteiro para ele
         @param key Chave que está sendo procurada
         @param node Ponteiro para o próximo nó
         @return Ponteiro para o nó que contém a chave, nullptr caso não exista um nó na árvore com essa chave
         */
        dlkd::Node<typeT> *Search(dlkd::Node<typeT> *node, typeT key);

        /**
        @brief Overload para inserir um novo elemento sem o apontador para o nó
        @param key Chave do novo nó
        */
        void Insert(typeT key);

        /**
        @brief Deleta um determinado nó
        @param key Chave do nó que será deletado
        */
        void DeleteNode(typeT key);

        /**
        @brief Deleta toda a árvore
        */
        void DeleteTree();

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void InorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void PreorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void PostorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento por nível na árvore e vai printando os elementos
        */
        void LevelorderTreeWalk();

        /**
        @brief Realiza o caminhamento por nível na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void LevelorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Verifica se um nó i é ancestral do nó j recursivamente
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool IsAncestorRecursive(typeT i, typeT j);

        /**
        @brief Verifica se um nó i é ancestral do nó j (usa apenas o caminhamento por nível)
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool IsAncestorLevelOrder(typeT i, typeT j);

        /**
        @brief Verifica se um nó i é ancestral de um nó j
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool IsAncestor(typeT i, typeT j);

        /**
        @brief Retorna a posição (índice) de um elemento na fila (função necessária para o método
        IsAncestor)
        @param array Array de busca
        @param key Chave que será buscada
        @return Inteiro que corresponde ao índice do elemento no array, -1 caso o elemento não esteja no array
        */
        int KeyPosition(typeT (&array)[], int key);

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        */
        void DumpTree(std::ofstream &output);
};

template<typename typeT>
BinaryTree<typeT>::BinaryTree() {
    this->m_root = nullptr;
    this->m_nodes = 0;
}

template<typename typeT>
BinaryTree<typeT>::~BinaryTree() {
    this->DeleteTree();
}

template<typename typeT>
dlkd::Node<typeT>* BinaryTree<typeT>::Search(dlkd::Node<typeT> *node, typeT key) {
    if (node == nullptr or key == node->m_key)
        return node;

    if (key < node->m_key)
        return this->Search(node->m_left, key);

    else
        return this->Search(node->m_right, key);
}

template<typename typeT>
void BinaryTree<typeT>::Insert(typeT key) {
    if (this->m_root == nullptr) {
        this->m_root = new dlkd::Node<typeT>(key);
        this->m_nodes++;
    }
    else {
        if (key < this->m_root->m_key) {
            this->Insert(this->m_root->m_left, key);
        }
        else {
            this->Insert(this->m_root->m_right, key);
        }
    }
}

template <typename typeT>
void BinaryTree<typeT>::Insert(dlkd::Node<typeT> *&node, typeT key) {
    if (node == nullptr) {
        node = new dlkd::Node<typeT>(key);
        this->m_nodes++;
    }
    else {
        if (key < node->m_key) {
            this->Insert(node->m_left, key);
        }
        else {
            this->Insert(node->m_right, key);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::DeleteTree() {
    this->DeleteTree(this->m_root);
    this->m_root = nullptr;
}

template<typename typeT>
void BinaryTree<typeT>::DeleteTree(dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->DeleteTree(node->m_left);
        this->DeleteTree(node->m_right);
        delete node;
    }
}

template<typename typeT>
void BinaryTree<typeT>::InorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->m_root != nullptr) {
        this->InorderTreeWalk(walk, this->m_root->m_left);
        walk.push(this->m_root->m_key);
        this->InorderTreeWalk(walk, this->m_root->m_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::InorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->InorderTreeWalk(walk, node->m_left);
        walk.push(node->m_key);
        this->InorderTreeWalk(walk, node->m_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::PreorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->m_root != nullptr) {
        walk.push(this->m_root->m_key);
        this->PreorderTreeWalk(walk, this->m_root->m_left);
        this->PreorderTreeWalk(walk, this->m_root->m_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::PreorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        walk.push(node->m_key);
        this->PreorderTreeWalk(walk, node->m_left);
        this->PreorderTreeWalk(walk, node->m_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::PostorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->m_root != nullptr) {
        this->PostorderTreeWalk(walk, this->m_root->m_left);
        this->PostorderTreeWalk(walk, this->m_root->m_right);
        walk.push(this->m_root->m_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::PostorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->PostorderTreeWalk(walk, node->m_left);
        this->PostorderTreeWalk(walk, node->m_right);
        walk.push(node->m_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::LevelorderTreeWalk() {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.push(this->m_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            std::cout << node->m_key << " ";
            queue.push(node->m_left);
            queue.push(node->m_right);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::LevelorderTreeWalk(CircularQueue<typeT> &walk) {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.push(this->m_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            walk.push(node->m_key);
            queue.push(node->m_left);
            queue.push(node->m_right);
        }
    }
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorRecursive(typeT i, typeT j) {
    if (this->m_root == nullptr)
        return false;

    if (i == this->m_root->m_key)
        return true;

    if (j == this->m_root->m_key)
        return false;

    if (i == j)
        return false;

    if (utils::Min(i, j) < this->m_root->m_key and utils::Max(i, j) > this->_root->key)
        return false;

    else
        if (i < this->m_root->m_key and j < this->_root->key)
            return this->IsAncestorRecursive(this->m_root->m_left, i, j);
        else
            return this->IsAncestorRecursive(this->m_root->m_right, i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorRecursive(dlkd::Node<typeT> *node, typeT i, typeT j) {
    if (node == nullptr)
        return false;

    if (i == node->m_key)
        return true;

    if (j == node->m_key)
        return false;

    if (i == j)
        return false;

    if (utils::Min(i, j) < node->m_key and utils::Max(i, j) > node->key)
        return false;

    else
        if (i < node->m_key and j < node->key)
            return this->IsAncestorRecursive(node->m_left, i, j);
        else
            return this->IsAncestorRecursive(node->m_right, i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestorLevelOrder(typeT i, typeT j) {
    // A lógica por trás de usar somente level order é que ele organiza os valores no array
    // preservando a hierarquia da árvore de cima para baixo e do nó mais à esquerda para o nó mais
    // à direita. Por esse motivo, as mesmas verificações realizadas no IsAncestorRecursive podem
    // ser feitas no array (no caso, fila) que armazena o caminhamento por nível

    int root_aux;
    int tmp;
    CircularQueue<typeT> levelOrder;
    this->LevelorderTreeWalk(levelOrder);

    for (int k = 0; k < this->m_nodes; k++) {
        if (k == 0) {
            try {
                root_aux = levelOrder.pop();
            }
            catch (queexcpt::QueueIsEmpty &e) {
                std::cout << e.what() << std::endl;
                break;
            }
            if (i == root_aux) {
                return true;
            }
            continue;
        }
        if (i == j) {
            return false;
        }
        if (i == root_aux) {
            return true;
        }
        if (j == root_aux) {
            return false;
        }
        if (utils::Min(i, j) < root_aux and utils::Max(i, j) > root_aux) {
            return false;
        }
        else if (i < root_aux and j < root_aux) {
            try {
                do {
                    tmp = levelOrder.pop();
                } while (tmp > root_aux);
                root_aux = tmp;

            }
            catch (queexcpt::QueueIsEmpty &e) {
                return false;
            }
        }
        else {
            try {
                do {
                    tmp = levelOrder.pop();
                } while (tmp < root_aux);
                root_aux = tmp;

            }
            catch (queexcpt::QueueIsEmpty &e) {
                return false;
            }
        }
    }
    return false;
}

template<typename typeT>
int BinaryTree<typeT>::KeyPosition(typeT (&array)[], int key) {
    for (int i = 0; i < this->m_nodes; i++) {
        if (array[i] == key)
            return i;
    }
    return -1;
}

template<typename typeT>
bool BinaryTree<typeT>::IsAncestor(typeT i, typeT j) {
    // Caso básico: i == j, então i não é ancestral de j
    if (i == j)
        return false;

    CircularQueue<typeT> inorder, preorder, postorder;
    this->InorderTreeWalk(inorder);
    this->PreorderTreeWalk(preorder);
    this->PostorderTreeWalk(postorder);

    typeT inorderArray[this->m_nodes];
    typeT preorderArray[this->m_nodes];
    typeT postorderArray[this->m_nodes];

    for (int i = 0; i < this->m_nodes; i++) {
        inorderArray[i] = inorder.pop();
        preorderArray[i] = preorder.pop();
        postorderArray[i] = postorder.pop();
    }

    int inorderPositionI = this->KeyPosition(inorderArray, i);
    int inorderPositionJ = this->KeyPosition(inorderArray, j);

    int inorderPositionRoot = this->KeyPosition(inorderArray, preorderArray[0]);

    // i < root < j  OU  j < root < i, implica em galhos diferentes o que é suficiente para dizer
    // que i não é ancestral de j
    // No inorder é possível descobrir isso comparando as posições relativas em relação a raiz
    if (utils::Min(inorderPositionI, inorderPositionJ) < inorderPositionRoot
        and utils::Max(inorderPositionI, inorderPositionJ) > inorderPositionRoot) {

        return false;
    }

    // i == raiz, então para todo j, i sempre será ancestral de j
    // da mesma maneira, se j == raiz, então para todo i, i nunca será ancestral de j
    if (inorderPositionI == inorderPositionRoot)
        return true;

    else if (inorderPositionJ == inorderPositionRoot)
        return false;

    int preorderPositionI = this->KeyPosition(preorderArray, i);
    int preorderPositionJ = this->KeyPosition(preorderArray, j);

    int postorderPositionI = this->KeyPosition(postorderArray, i);
    int postorderPositionJ = this->KeyPosition(postorderArray, j);

    // Verifica se i ou j não foi encontrado no array
    if (utils::Min(inorderPositionI, inorderPositionJ,
                   preorderPositionI, preorderPositionJ,
                   postorderPositionI, postorderPositionJ) == -1) {

        return false;
    }

    return (postorderPositionI > postorderPositionJ
            and preorderPositionI < preorderPositionJ);
}

template<typename typeT>
void BinaryTree<typeT>::DumpTree(std::ofstream &output) {
    int level = 0;

    if (this->m_root != nullptr) {
        output << this->m_root->m_key;
        output << "(";
        output << level;
        output << ")" << std::endl;
        this->DumpTree(this->m_root->m_left, level + 1, "", output, true);
        this->DumpTree(this->m_root->m_right, level + 1, "", output, false);
    }
}

template<typename typeT>
void BinaryTree<typeT>::DumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft) {
    if (node != nullptr) {
        if (sideIsLeft) {
            output << vBar << "├───" << node->m_key << "(" << level << ")" << std::endl;
        }
        else {
            output << vBar << "└───" << node->m_key << "(" << level << ")" << std::endl;
        }
        this->DumpTree(node->m_left, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, true);
        this->DumpTree(node->m_right, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, false);
    }
}

#endif // BINARY_TREE_H_
