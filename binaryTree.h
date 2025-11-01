#include<iostream>
#include<stdexcept>
#include<cmath>
#include"queue.h"
using namespace std;

//数组描述
template<class T>
class arrayBinaryTree{
private:
    int listSize;
    int arrayLength;
    T* binaryTree;
public:
    arrayBinaryTree(int capacity=10);
    ~arrayBinaryTree(){ delete[] binaryTree;}
    void extend();
    int size(){ return listSize;}
    bool is_empty(){ return listSize==0;}
    int _find(const T& v);
    void push_back(const T& v);
    /*void erase(const T& v);
    void insert(const T& v,int index);
    void output();*/
};

template<class T>
arrayBinaryTree<T>::arrayBinaryTree(int capacity)
{
    if(capacity<1){
        throw invalid_argument("This capacity is invalid");
    }
    arrayLength=capacity;
    listSize=0;
    binaryTree=new T[capacity];
}

template<class T>
void arrayBinaryTree<T>::extend()
{
    T* newTree=new T[arrayLength*2];
    for(int i=1;i<=listSize;i++){
        newTree[i]=binaryTree[i];
    }
    delete[] binaryTree;
    binaryTree=newTree;
    arrayLength*=2;
}

template<class T>
int arrayBinaryTree<T>::_find(const T& v)
{
    for(int i=1;i<=listSize;i++){
        if(binaryTree[i]==v) return i;
    }
    return -1;
}

template<class T>
void arrayBinaryTree<T>::push_back(const T& v)
{
    if(listSize==arrayLength-1)
        extend();
    binaryTree[++listSize]=v;
}

//链表描述
template<class T>
struct binaryTreeNode{
    T element;
    binaryTreeNode<T>* leftChild;
    binaryTreeNode<T>* rightChild;
};

template<class T>
class linkedBinaryTree{
private:
    int treeSize;
    binaryTreeNode<T>* root;
public:
    linkedBinaryTree();
    ~linkedBinaryTree();
    bool is_empty(){ return treeSize==0; }
    int size(){ return treeSize; }
    int height();
    void preOrder(binaryTreeNode<T>* t);
    void inOrder(binaryTreeNode<T>* t);
    void postOrder(binaryTreeNode<T>* t);
    void levelOrder(binaryTreeNode<T>* t);
    void visit(binaryTreeNode<T>* t);
    void add(const T& value);
    void dispose(binaryTreeNode<T>* node);
};

template<class T>
linkedBinaryTree<T>::linkedBinaryTree()
{
    treeSize=0;
    root=NULL;
}

template<class T>
linkedBinaryTree<T>::~linkedBinaryTree()
{
    dispose(root);
}

template<class T>
void linkedBinaryTree<T>::dispose(binaryTreeNode<T>* node)
{
    if(node!=NULL){
        dispose(node->leftChild);
        dispose(node->rightChild);
        delete node;
    }
}

template<class T>
void linkedBinaryTree<T>::add(const T& value)
{
    binaryTreeNode<T>* newnode=new binaryTreeNode<T>;
    newnode->element=value;
    newnode->leftChild=NULL;
    newnode->rightChild=NULL;
    if(root==NULL){
        root=newnode;
        treeSize++;
        return ;
    }
    arrayQueue<binaryTreeNode<T>*> q;
    q.push(root);
    while(!q.is_empty()){
        binaryTreeNode<T>* current=q.get_front();
        q.pop();
        if(current->leftChild!=NULL)
            q.push(current->leftChild);
        else{
            current->leftChild=newnode;
            treeSize++;
            return ;
        }
        if(current->rightChild!=NULL)
            q.push(current->rightChild);
        else{
            current->rightChild=newnode;
            treeSize++;
            return ;
        }
    }
}

template<class T>
int linkedBinaryTree<T>::height()
{
    return (int)(log2(treeSize))+1;
}

template<class T>
void linkedBinaryTree<T>::visit(binaryTreeNode<T>* t)
{
    cout<<t->element<<" ";
}

template<class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* t)
{
    if(t!=NULL){
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t)
{
    if(t!=NULL){
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template<class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* t)
{
    if(t!=NULL){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

template<class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T>* t)
{
    arrayQueue<binaryTreeNode<T>*> q;
    while(t!=NULL){
        visit(t);
        if(t->leftChild!=NULL)
            q.push(t->leftChild);
        if(t->rightChild!=NULL)
            q.push(t->rightChild);
        if(!q.is_empty()){
            t=q.get_front();
            q.pop();
        }
        else t=NULL;
    }
}