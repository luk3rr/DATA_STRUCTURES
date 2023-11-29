/*
* Filename: tree_base.h
* Created on: November 18, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef TREE_BASE_H_
#define TREE_BASE_H_

#include "queue_slkd.h"

template<typename typeT>
class TreeBase
{
public:
        virtual void Insert(typeT key) = 0;
        virtual void Search(typeT key) = 0;
        virtual void DeleteTree() = 0;
        virtual void DeleteNode(typeT key) = 0;
        virtual void InorderTreeWalk(slkd::Queue<typeT> &walk) = 0;
        virtual void PreorderTreeWalk(slkd::Queue<typeT> &walk) = 0;
        virtual void PostorderTreeWalk(slkd::Queue<typeT> &walk) = 0;
        virtual void LevelorderTreeWalk(slkd::Queue<typeT> &walk) = 0;
        virtual bool IsAncestor(typeT i, typeT j) = 0;
        virtual void DumpTree(std::string filename);
};

#endif // TREE_BASE_H_
