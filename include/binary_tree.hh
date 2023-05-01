#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <fstream>
#include <iostream>

#include "queue.hh"
#include "utils.hh"
#include "node_doubly_linked.hh"

template <typename typeT>
class BinaryTree {
    private:
        dlkd::Node<typeT> *_root;
        int _nodes;

        /**
        @brief Verifica se um nó i é ancestral do nó j recursivamente
        @param node Ponteiro para o próximo nó da chamada recursiva
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool isAncestorRecursive(dlkd::Node<typeT> *node, typeT i, typeT j);

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        @param level Nível do nó atual
        @param node Nó atual
        @param side, deve receber True se o nó está o lado esquerdo ou False, caso o nó esteja do lado direito
        */
        void dumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft);

        /**
        @brief Inserir um novo elemento na árvore
        @param key Chave do novo nó
        @param node Ponteiro para o próximo nó (função recursiva)
        */
        void insert(dlkd::Node<typeT> *&node, typeT key);

        /**
        @brief Deleta toda a árvore
        @param node Nó atual que será deletado a cada chamada recursiva da função
        */
        void deleteTree(dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void inorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void postorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void preorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

    public:
        BinaryTree();

        ~BinaryTree();

        /**
         @brief Busca um nó com uma determinada chave e retorna um ponteiro para ele
         @param key Chave que está sendo procurada
         @param node Ponteiro para o próximo nó
         @return Ponteiro para o nó que contém a chave, nullptr caso não exista um nó na árvore com essa chave
         */
        dlkd::Node<typeT> *search(dlkd::Node<typeT> *node, typeT key);

        /**
        @brief Overload para inserir um novo elemento sem o apontador para o nó
        @param key Chave do novo nó
        */
        void insert(typeT key);

        /**
        @brief Deleta um determinado nó
        @param key Chave do nó que será deletado
        */
        void deleteNode(typeT key);

        /**
        @brief Deleta toda a árvore
        */
        void deleteTree();

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void inorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void preorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void postorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento por nível na árvore e vai printando os elementos
        */
        void levelOrderTreeWalk();

        /**
        @brief Realiza o caminhamento por nível na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void levelOrderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Verifica se um nó i é ancestral do nó j recursivamente
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool isAncestorRecursive(typeT i, typeT j);

        /**
        @brief Verifica se um nó i é ancestral do nó j (usa apenas o caminhamento por nível)
        @param i Chave do nó
        @param j Chave do nó
        @return True se i é ancestral de j, False caso contrário
        */
        bool isAncestorLevelOrder(typeT i, typeT j);

        /**
         @brief Verifica se um nó i é ancestral de um nó j
         @param i Chave do nó
         @param j Chave do nó
         @return True se i é ancestral de j, False caso contrário
        */
        bool isAncestor(typeT i, typeT j);

        /**
        @brief Retorna a posição (índice) de um elemento na fila (função necessária para o método
        isAncestor)
        @param array Array de busca
        @param key Chave que será buscada
        @return Inteiro que corresponde ao índice do elemento no array, -1 caso o elemento não esteja no array
        */
        int keyPosition(typeT (&array)[], int key);

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        */
        void dumpTree(std::ofstream &output);
};

template<typename typeT>
BinaryTree<typeT>::BinaryTree() {
    this->_root = nullptr;
    this->_nodes = 0;
}

template<typename typeT>
BinaryTree<typeT>::~BinaryTree() {
    this->deleteTree();
}

template<typename typeT>
dlkd::Node<typeT>* BinaryTree<typeT>::search(dlkd::Node<typeT> *node, typeT key) {
    if (node == nullptr or key == node->_key)
        return node;

    if (key < node->_key)
        return this->search(node->_left, key);

    else
        return this->search(node->_right, key);
}

template<typename typeT>
void BinaryTree<typeT>::insert(typeT key) {
    if (this->_root == nullptr) {
        this->_root = new dlkd::Node<typeT>(key);
        this->_nodes++;
    }
    else {
        if (key < this->_root->_key) {
            this->insert(this->_root->_left, key);
        }
        else {
            this->insert(this->_root->_right, key);
        }
    }
}

template <typename typeT>
void BinaryTree<typeT>::insert(dlkd::Node<typeT> *&node, typeT key) {
    if (node == nullptr) {
        node = new dlkd::Node<typeT>(key);
        this->_nodes++;
    }
    else {
        if (key < node->_key) {
            this->insert(node->_left, key);
        }
        else {
            this->insert(node->_right, key);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::deleteTree() {
    this->deleteTree(this->_root);
    this->_root = nullptr;
}

template<typename typeT>
void BinaryTree<typeT>::deleteTree(dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->deleteTree(node->_left);
        this->deleteTree(node->_right);
        delete node;
    }
}

template<typename typeT>
void BinaryTree<typeT>::inorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        this->inorderTreeWalk(walk, this->_root->_left);
        walk.push(this->_root->_key);
        this->inorderTreeWalk(walk, this->_root->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::inorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->inorderTreeWalk(walk, node->_left);
        walk.push(node->_key);
        this->inorderTreeWalk(walk, node->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::preorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        walk.push(this->_root->_key);
        this->preorderTreeWalk(walk, this->_root->_left);
        this->preorderTreeWalk(walk, this->_root->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::preorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        walk.push(node->_key);
        this->preorderTreeWalk(walk, node->_left);
        this->preorderTreeWalk(walk, node->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::postorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        this->postorderTreeWalk(walk, this->_root->_left);
        this->postorderTreeWalk(walk, this->_root->_right);
        walk.push(this->_root->_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::postorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->postorderTreeWalk(walk, node->_left);
        this->postorderTreeWalk(walk, node->_right);
        walk.push(node->_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::levelOrderTreeWalk() {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.push(this->_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            std::cout << node->_key << " ";
            queue.push(node->_left);
            queue.push(node->_right);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::levelOrderTreeWalk(CircularQueue<typeT> &walk) {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.push(this->_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            walk.push(node->_key);
            queue.push(node->_left);
            queue.push(node->_right);
        }
    }
}

template<typename typeT>
bool BinaryTree<typeT>::isAncestorRecursive(typeT i, typeT j) {
    if (this->_root == nullptr)
        return false;

    if (i == this->_root->_key)
        return true;

    if (j == this->_root->_key)
        return false;

    if (i == j)
        return false;

    if (utils::min(i, j) < this->_root->_key and std::max(i, j) > this->_root->key)
        return false;

    else
        if (i < this->_root->_key and j < this->_root->key)
            return this->isAncestorRecursive(this->_root->_left, i, j);
        else
            return this->isAncestorRecursive(this->_root->_right, i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::isAncestorRecursive(dlkd::Node<typeT> *node, typeT i, typeT j) {
    if (node == nullptr)
        return false;

    if (i == node->_key)
        return true;

    if (j == node->_key)
        return false;

    if (i == j)
        return false;

    if (utils::min(i, j) < node->_key and std::max(i, j) > node->key)
        return false;

    else
        if (i < node->_key and j < node->key)
            return this->isAncestorRecursive(node->_left, i, j);
        else
            return this->isAncestorRecursive(node->_right, i, j);
}

template<typename typeT>
bool BinaryTree<typeT>::isAncestorLevelOrder(typeT i, typeT j) {
    // A lógica por trás de usar somente level order é que ele organiza os valores no array
    // preservando a hierarquia da árvore de cima para baixo e do nó mais à esquerda para o nó mais
    // à direita. Por esse motivo, as mesmas verificações realizadas no isAncestorRecursive podem
    // ser feitas no array (no caso, fila) que armazena o caminhamento por nível

    int root_aux;
    int tmp;
    CircularQueue<typeT> levelOrder;
    this->levelOrderTreeWalk(levelOrder);

    for (int k = 0; k < this->_nodes; k++) {
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
        if (utils::min(i, j) < root_aux and std::max(i, j) > root_aux) {
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
int BinaryTree<typeT>::keyPosition(typeT (&array)[], int key) {
    for (int i = 0; i < this->_nodes; i++) {
        if (array[i] == key)
            return i;
    }
    return -1;
}

template<typename typeT>
bool BinaryTree<typeT>::isAncestor(typeT i, typeT j) {
    // Caso básico: i == j, então i não é ancestral de j
    if (i == j)
        return false;

    CircularQueue<typeT> inorder, preorder, postorder;
    this->inorderTreeWalk(inorder);
    this->preorderTreeWalk(preorder);
    this->postorderTreeWalk(postorder);

    typeT inorderArray[this->_nodes];
    typeT preorderArray[this->_nodes];
    typeT postorderArray[this->_nodes];

    for (int i = 0; i < this->_nodes; i++) {
        inorderArray[i] = inorder.pop();
        preorderArray[i] = preorder.pop();
        postorderArray[i] = postorder.pop();
    }

    int inorderPositionI = this->keyPosition(inorderArray, i);
    int inorderPositionJ = this->keyPosition(inorderArray, j);

    int inorderPositionRoot = this->keyPosition(inorderArray, preorderArray[0]);

    // i < root < j  OU  j < root < i, implica em galhos diferentes o que é suficiente para dizer
    // que i não é ancestral de j
    // No inorder é possível descobrir isso comparando as posições relativas em relação a raiz
    if (utils::min(inorderPositionI, inorderPositionJ) < inorderPositionRoot
        and utils::max(inorderPositionI, inorderPositionJ) > inorderPositionRoot) {

        return false;
    }

    // i == raiz, então para todo j, i sempre será ancestral de j
    // da mesma maneira, se j == raiz, então para todo i, i nunca será ancestral de j
    if (inorderPositionI == inorderPositionRoot)
        return true;

    else if (inorderPositionJ == inorderPositionRoot)
        return false;

    int preorderPositionI = this->keyPosition(preorderArray, i);
    int preorderPositionJ = this->keyPosition(preorderArray, j);

    int postorderPositionI = this->keyPosition(postorderArray, i);
    int postorderPositionJ = this->keyPosition(postorderArray, j);

    // Verifica se i ou j não foi encontrado no array
    if (utils::min(inorderPositionI, inorderPositionJ,
                   preorderPositionI, preorderPositionJ,
                   postorderPositionI, postorderPositionJ) == -1) {

        return false;
    }

    return (postorderPositionI > postorderPositionJ
            and preorderPositionI < preorderPositionJ);
}

template<typename typeT>
void BinaryTree<typeT>::dumpTree(std::ofstream &output) {
    int level = 0;

    if (this->_root != nullptr) {
        output << this->_root->_key;
        output << "(";
        output << level;
        output << ")" << std::endl;
        this->dumpTree(this->_root->_left, level + 1, "", output, true);
        this->dumpTree(this->_root->_right, level + 1, "", output, false);
    }
}

template<typename typeT>
void BinaryTree<typeT>::dumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft) {
    if (node != nullptr) {
        if (sideIsLeft) {
            output << vBar << "├───" << node->_key << "(" << level << ")" << std::endl;
        }
        else {
            output << vBar << "└───" << node->_key << "(" << level << ")" << std::endl;
        }
        this->dumpTree(node->_left, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, true);
        this->dumpTree(node->_right, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, false);
    }
}

#endif // BINARY_TREE_H_
