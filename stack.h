#ifndef STACK
#define STACK
#include<iostream>
#include<sstream>
#include<stdexcept>
using namespace std;

//栈的数组描述
template<class T>
class arrayStack
{
private:
    int top; //栈顶
    int arrayLength; //栈容量
    T* stack;
public:
    arrayStack(int capacity=10);
    ~arrayStack(){ delete[] stack; }
    int size(){ return top+1; }
    bool is_empty(){ return top==-1; }
    T& get_top();
    void push(const T& value);
    void pop();
};

template<class T>
arrayStack<T>::arrayStack(int capacity=10)
{
    if(capacity<1){
        ostringstream s;
        s<<"Initial capacity = "<<capacity<<" Must be > 0";
        throw invalid_argument(s.str());
    }
    arrayLength=capacity;
    stack=new T[arrayLength];
    top=-1;
}

template <class T>
inline T& arrayStack<T>::get_top()
{
    if(top==-1){
        throw out_of_range("栈为空");
    }
    return stack[top];
}

template <class T>
void arrayStack<T>::push(const T &value)
{
    if(arrayLength==top+1){
        T* temp=new T[arrayLength*2];
        for(int i=0;i<=top;i++){
            temp[i]=stack[i];
        }
        delete[] stack;
        stack=temp;
        arrayLength*=2;
    }
    stack[++top]=value;
}

template<class T>
void arrayStack<T>::pop()
{
    if(top==-1){
        throw out_of_range("栈为空");
    }
    stack[top--].~T();
}

//栈的链表描述

template<class T>
struct chainNode
{
    T element;
    chainNode<T>* next;
};

template<class T>
class linkedStack
{
private:
    int size; //元素个数
    chainNode<T>* top; //栈顶指针(firstNode)
public:
    linkedStack(int capacity=10){ top=NULL; size=0;}
    ~linkedStack();
    bool is_empty(){ return size==0; }
    int get_size(){ return size; }
    T& get_top();
    void push(const T& value);
    void pop();
};

template<class T>
linkedStack<T>::~linkedStack()
{
    while(top!=NULL){
        chainNode<T> next=top->next;
        delete top;
        top=next;
    }
}

template<class T>
T& linkedStack<T>::get_top()
{
    if(size==0)
    throw out_of_range("栈为空");
    return top->element;
}

template<class T>
void linkedStack<T>::push(const T& value)
{
    chainNode<T>* newnode=new chainNode<T>;
    newnode->element=value;
    if(size==0){
        top=newnode;
        top->next=NULL;
    }
    else{
        newnode->next=top;
        top=newnode;
    }
    size++;
}

template<class T>
void linkedStack<T>::pop()
{
    if(size==0){
        throw out_of_range("栈为空");
    }
    chainNode<T>* deleteNode;
    deleteNode=top;
    top=top->next;
    delete deleteNode;
    size--;
}


#endif STACK