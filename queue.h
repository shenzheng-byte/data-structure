#ifndef QUEUE
#define QUEUE
#include<iostream>
#include<cmath>
#include<stdexcept>
#include<sstream>
using namespace std;

template<class T>
class arrayQueue
{
private:
    int front;
    int back;
    int arrayLength;
    T* queue;
public:
    arrayQueue(int capacity=10);
    ~arrayQueue(){ delete[] queue;}
    bool is_empty(){return back==-1;}
    int size(){ return (back-front+arrayLength)%arrayLength+1;}
    T& get_front();
    T& get_back();
    void push(const T& value);
    void pop();
    void extend();
};

template<class T>
arrayQueue<T>::arrayQueue(int capacity)
{
    if(capacity<1){
        ostringstream s;
        s<<"Initial capacity = "<<capacity<<" Must be > 0";
        throw invalid_argument(s.str());
    }
    front=back=-1;
    arrayLength=capacity;
    queue=new T[arrayLength];
}

template<class T>
T& arrayQueue<T>::get_front()
{
    if(back==-1){
        throw out_of_range("队列为空");
    }
    return queue[front%arrayLength];
}

template<class T>
T& arrayQueue<T>::get_back()
{
    if(back==-1){
        throw out_of_range("队列为空");
    }
    return queue[back%arrayLength];
}

template<class T>
void arrayQueue<T>::extend()
{
    T* newqueue=new T[arrayLength*2];
    if(back<front){
        for(int i=front;i<arrayLength;i++){
            newqueue[i]=queue[i];
        }
        for(int i=0;i<=back;i++){
            newqueue[arrayLength+i]=queue[i];
        }
        back+=arrayLength;
    }
    else{
        for(int i=front;i<=back;i++){
            newqueue[i]=queue[i];
        }
    }
    arrayLength*=2;
    delete queue;
    queue=newqueue;
}

template<class T>
void arrayQueue<T>::push(const T& value)
{
    if((back+1)%arrayLength==front)
        extend();
    if(back==-1){
        front++;
    }
    back=(back+1)%arrayLength;
    queue[back]=value;
}

template<class T>
void arrayQueue<T>::pop()
{
    if(back==-1){
        throw out_of_range("队列为空");
    }
    queue[front].~T();
    front=(front+1)%arrayLength;
}

//队列的链表描述
template<class T>
struct chainNode
{
    T element;
    chainNode<T>* next;
};

template<class T>
class linkedQueue
{
private:
    chainNode<T>* front,back;
    int size; 
public:
    linkedQueue(int capacity=10){ front=NULL; back=NULL; size=0; }
    ~linkedQueue();
    bool is_empty(){ return size==0;}
    int get_size(){ return size;}
    T& get_front();
    T& get_back();
    void push(const T& value);
    void pop();
};

template<class T>
linkedQueue<T>::~linkedQueue()
{
    while (front!=NULL)
    {
        chainNode<T>* next=front->next;
        delete front;
        front=next;
    }
}

template<class T>
T& linkedQueue<T>::get_front()
{
    if(front==NULL){
        throw out_of_range("队列为空");
    }
    return front->element;
}

template<class T>
T& linkedQueue<T>::get_back()
{
    if(back==NULL){
        throw out_of_range("队列为空");
    }
    return back->element;
}

template<class T>
void linkedQueue<T>::push(const T& value)
{
    chainNode<T>* newnode=new chainNode<T>;
    newnode->next=NULL;
    if(front==NULL){
        front=newnode;
        back=newnode;
    }
    else{
        back->next=newnode;
        back=newnode;
    }
    size++;
}

template<class T>
void linkedQueue<T>::pop()
{
    if(back==NULL){
        throw out_of_range("队列为空");
    }
    chainNode<T>* deleteNode=front;
    front=front->next;
    delete deleteNode;
    size--;
}

#endif  