#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include<iostream>
using namespace std;

template<class K,class E>
struct binaryTreeNode
{
    pair<K,E> element;
    binaryTreeNode<K,E>* leftChild;
    binaryTreeNode<K,E>* rightChild;
    binaryTreeNode(const pair<K,E>& theElement)
    {
        element=theElement;
        leftChild=NULL;
        rightChild=NULL;
    }
};

template<class K,class E>
class binarySearchTree
{
private:
    binaryTreeNode<K,E>* root;
    int size;
public:
    binarySearchTree(){ root=NULL; size=0; }
    ~binarySearchTree();
    bool is_empty(){ return size==0; }
    int get_size(){ return size; }
    void insert(const pair<K,E>& thePair);
    pair<K,E>* find(const K& theKey) const;
    void erase(const K& theKey);
};

template<class K,class E>
void binarySearchTree<K,E>::insert(const pair<K,E>& thePair)
{
    binaryTreeNode<K,E> *p=root;
    binaryTreeNode<K,E> *pp=NULL;
    while(p!=NULL){
        pp=p;
        if(thePair.first<p->element.first)
            p=p->leftChild;
        else if(thePair.first>p->element.first)
            p=p->rightChild;
        else{
            p->element.second=thePair.second;
            return;
        }
    }
    binaryTreeNode<K,E>* newnode=new binaryTreeNode<K,E>(thePair);
    if(root!=NULL){
        if(thePair.first<pp->element.first)
            pp->leftChild=newnode;
        else
            pp->rightChild=newnode;
    }
    else
        root=newnode;
    size++;
}

template<class K,class E>
pair<K,E>* binarySearchTree<K,E>::find(const K& theKey) const
{
    binaryTreeNode<K,E>* p=root;
    while(p!=NULL){
        if(theKey<p->element.first)
            p=p->leftChild;
        else if(theKey>p->element.first)
            p=p->rightChild;
        else
            return &p->element;
    }
    return NULL;
}

template<class K,class E>
void binarySearchTree<K,E>::erase(const K& theKey)
{
    binaryTreeNode<K,E>* p=root;
    binaryTreeNode<K,E>* pp=NULL;
    while(p!=NULL){
        if(theKey<p->element.first){
            pp=p;
            p=p->leftChild;
        }
        else if(theKey>p->element.first){
            pp=p;
            p=p->rightChild;
        }
        else
            break;
    }
    if(p==NULL)
        return ;
    //当p有两个子节点时
    if(p->leftChild!=NULL&&p->rightChild!=NULL){
        binaryTreeNode<K,E>* s=p->leftChild;
        binaryTreeNode<K,E>* ps=p;
        while(s->rightChild!=NULL){
            ps=s;
            s=s->rightChild;
        }
        p->element=s->element;
        p=s;
        pp=ps;
    }
    //当p有0个或1个子节点时
    binaryTreeNode<K,E>* c;
    if(p->leftChild!=NULL)
        c=p->leftChild;
    else
        c=p->rightChild;
    if(p==root)
        root=c;
    else{
        if(p==pp->leftChild)
            pp->leftChild=c;
        else
            pp->rightChild=c;
    }
    delete p;
    size--;
}








#endif