#include<iostream>
#include<exception>
using namespace std;

template<class T>
class maxHeap
{
private:
    int heapSize;
    int arrayLength;
    T* heap;
public:
    maxHeap(int capacity=10);
    ~maxHeap(){ delete[] heap;}
    int size(){ return heapSize;}
    void initialize(T* theHeap,int size);
    bool is_empty(){ return heapSize==0;}
    void extend();
    T& top();
    T& pop();
    void push(const T& value);
};

template<class T>
maxHeap<T>::maxHeap(int capacity)
{
    if(capacity<0)
        throw invalid_argument("capacity must >0");
    heapSize=0;
    arrayLength=capacity;
    heap=new T[arrayLength];
}

template<class T>
void maxHeap<T>::initialize(T* theHeap,int size)
{
    delete[] heap;
    heap=theHeap;
    heapSize=size;
    arrayLength=size+10;
    for(int root=heapSize/2;root>=1;root--){
        T rootElement=heap[root];
        int child=2*root;
        while(child<=heapSize){
            if(child<heapSize&&heap[child]<heap[child+1])
                child++;
            if(rootElement>=heap[child])
                break;
            heap[child/2]=heap[child];
            child*=2;
        }
        heap[child/2]=rootElement;
    }
}

template<class T>
T& maxHeap<T>::top()
{
    if(is_empty())
        throw out_of_range("The heap is empty");
    return heap[1];
}

template<class T>
void maxHeap<T>::extend()
{
    T* newHeap=new T[arrayLength*2];
    for(int i=1;i<=heapSize;i++){
        newHeap[i]=heap[i];
    }
    delete[] heap;
    heap=newHeap;
    arrayLength*=2;
}

template<class T>
void maxHeap<T>::push(const T& value)
{
    if(heapSize==arrayLength-1){
        extend();
    }
    int current=++heapSize;
    while(current!=1&&value>heap[current/2]){
        heap[current]=heap[current/2];
        current/=2;
    }
    heap[current]=value;
}

template<class T>
T& maxHeap<T>::pop()
{
    if(heapSize==0)
        throw out_of_range("The heap is empty");
    heap[1].~T();
    T lastElement=heap[heapSize--];
    int current=1,child=2;
    while(child<=heapSize){
        if(child<heapSize&&heap[child]<heap[child+1])
            child++;
        if(heap[child]<=lastElement)
            break;
        heap[current]=heap[child];
        current=child;
        child*=2;
    }
    heap[current]=lastElement;
}