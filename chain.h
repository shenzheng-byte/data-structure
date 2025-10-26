#ifndef CHAIN
#define CHAIN
#include<iostream>
#include<stdexcept>
#include<sstream>
using namespace std;

template<class T>
struct chainNode
{
    T element;
    chainNode<T>* next;
};

template<class T>
class chain
{
private:
    chainNode<T>* firstNode;
    int listSize;
public:
    chain(const chain<T>& theChain);
    chain();
    ~chain();
    int get_listSize(){ return listSize; }
    bool is_empty(){ return listSize==0; }
    void checkIndex(int index);

    void insert(const T& theElement,int index);
    void push_back(const T& theElement);
    void erase(int index);
    void clear();
    T& get(int index);
    int _find(const T& theElement);
    void reverse();
    void output();

    class iterator{
        protected:
            chainNode<T>* node;
        public:
            iterator(chainNode<T>* theNode=NULL){node=theNode;}
            T& operator*() const { return node->element;}
            T* operator->() const { return &node->element;}

            iterator& operator++(){ node=node->next; return *this;}
            iterator operator++(int){
                iterator old=*this;
                node=node->next;
                return old;
            }

            bool operator!=(const iterator right) const {return node!=right->node;}
            bool operator==(const iterator right) const {return node==right->node;}
    };
    
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(NULL); }
};

template<class T>
chain<T>::chain()
{
    firstNode=NULL;
    listSize=0;
}

template<class T>
chain<T>::~chain()
{
    while(firstNode!=NULL){
        chainNode<T>* t=firstNode->next;
        delete firstNode;
        firstNode=t;
    }
    listSize=0;
}

template<class T>
chain<T>::chain(const chain<T>& theChain)
{
    if(theChain.listSize=0){
        firstNode=NULL;
        listSize==0;
        return ;
    }
    firstNode=new chainNode<T>;
    chainNode<T>* sourceNode=theChain.firstNode;
    chainNode<T>* p=firstNode;
    while(sourceNode!=NULL)
    {
        p->element=sourceNode->element;
        p->next=new chainNode<T>;
        p=p->next;
        sourceNode=sourceNode->next;
    }
    p->next=NULL;
    listSize=theChain.listSize;
}

template<class T>
void chain<T>::checkIndex(int index)
{
    if(index<0||index>=listSize){
        ostringstream s;
        s<<"The index out of range";
        throw out_of_range(s.str());
    }
}

template<class T>
void chain<T>::insert(const T& theElement,int index)
{
    if(index<0||index>listSize){
        ostringstream s;
        s<<"The index out of range";
        throw out_of_range(s.str());
    }
    chainNode<T>* newnode=new chainNode<T>;
    newnode->element=theElement;
    if(index==0){
        newnode->next=firstNode;
        firstNode=newnode;
    }
    else{
        chainNode<T>* p=firstNode;
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        newnode->next=p->next;
        p->next=newnode;
    }
    listSize++;
}

template<class T>
void chain<T>::push_back(const T& theElement)
{
    chainNode<T>* newnode=new chainNode<T>;
    newnode->element=theElement;
    newnode->next=NULL;
    if(listSize==0) firstNode=newnode;
    else{
        chainNode<T>* p=firstNode;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=newnode;
    }
    listSize++;
}

template<class T>
void chain<T>::erase(int index)
{
    checkIndex(index);
    chainNode<T>* deleteNode;
    if(index==0){
        deleteNode=firstNode;
        firstNode=firstNode->next;
    }
    else{
        chainNode<T>* p=firstNode;
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        deleteNode=p->next;
        p->next=p->next->next;
    }
    delete deleteNode;
    listSize--;
}

template<class T>
void chain<T>::clear()
{
    while(firstNode!=NULL)
    {
        chainNode<T>* node=firstNode;
        firstNode=node->next;
        delete node;
    }
    listSize=0;
}

template<class T>
T& chain<T>::get(int index)
{
    checkIndex(index);
    chainNode<T>* p=firstNode;
    for(int i=0;i<index;i++){
        p=p->next;
    }
    return p->element;
}

template<class T>
int chain<T>::_find(const T& theElement)
{
    chainNode<T>* p=firstNode;
    int index=0;
    while(p->element!=theElement&&p!=NULL)
    {
        p=p->next;
        index++;
    }
    if(p!=NULL) return index;
    else return -1;
}

template<class T>
void chain<T>::reverse()
{
   if(listSize>1)
   {
    chainNode<T>* pre=NULL;
    chainNode<T>* cur=firstNode;
    chainNode<T>* nex=cur->next;
    while(nex!=NULL)
    {
        cur->next=pre;
        pre=cur;
        cur=nex;
        nex=nex->next;
    }
    cur->next=pre;
    firstNode=cur;
   }
}

template<class T>
void chain<T>::output()
{
    chainNode<T>* p=firstNode;
    while(p!=NULL){
        cout<<p->element<<endl;
        p=p->next;
    }
}

#endif