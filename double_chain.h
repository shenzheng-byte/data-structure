#ifndef DOUBLE
#define DOUBLE
#include<iostream>
#include<stdexcept>
#include<sstream>
using namespace std;

template<class T>
class chainNode
{
    T element;
    chainNode<T>* previous;
    chainNode<T>* next;
};

template<class T>
class double_chain
{
private:
    chainNode<T>* firstNode;
    chainNode<T>* lastNode;
    int listSize;
public:
    double_chain();
    ~double_chain();
    int get_listSize(){ return listSize; }
    bool is_empty(){ return listSize==0; }
    void checkIndex(int index);


};

template<class T>
double_chain<T>::double_chain()
{
    firstNode=NULL;
    lastNode=NULL;
    listSize=0;
}

template<class T>
double_chain<T>::~double_chain()
{
    while (firstNode!=NULL)
    {
        chainNode<T>* t=firstNode->next;
        delete firstNode;
        firstNode=t;
    }
}

template<class T>
void double_chain<T>::checkIndex(int index)
{
    
}


#endif 