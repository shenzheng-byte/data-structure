#ifndef ARRAY
#define ARRAY
#include<iostream>
#include<sstream>
#include<stdexcept>
using namespace std;

template<class T>
class arrayList
{
private:
    int arrayLength;
    int listSize;
    T* element;
public:
    arrayList(int capacity=10);
    arrayList(const arrayList<T>& thelist);
    ~arrayList(){ delete[] element; }
    int get_arrrayLength(){ return arrayLength; }
    int get_listSize(){ return listSize; }
    bool is_empty(){ return listSize==0; }
    void extend();
    void checkIndex(int index);

    void push_back(const T& theElement);
    void insert(int index,const T& theElement);
    void pop_back();
    void erase(int index);
    int _find(const T& theElement);
    void set(int index,const T& value){checkIndex(index); element[index]=value;}
    void resize(int newSize){ if(newSize>arrayLength) extend(); listSize=newSize;}

    T& operator[](int x){ checkIndex(x); return element[x];}
    //friend ostream& operator<<(ostream& out,const T& value);

    class iterator{
        protected:
            T* position;
        public:
            iterator(T* thePosition=nullptr){ position=thePosition; }
            //解引用操作符
            T& operator*() const { return *position; }
            T* operator->() const { return &*position; } 
            
            iterator& operator++(){ ++position; return *this; }
            iterator operator++(int){
                iterator old=*this;
                ++position;
                return old;
            }
            iterator operator--(){ --position; return *this; }
            iterator operator--(int){
                iterator old=*this;
                --position;
                return old;
            }
            bool operator!=(const iterator right) const {return position!=right.position;}
            bool operator==(const iterator right) const {return position==right.position;}
    };

    iterator begin() { return iterator(element); }
    iterator end() { return iterator(element+listSize); }
};

template<class T>
arrayList<T>::arrayList(int capacity) //构造函数进行初始化
{
    if(capacity<1){
        ostringstream s;
        s<<"Initial capacity = "<<capacity<<" Must be > 0";
        throw invalid_argument(s.str());
    }
    element=new T[capacity];
    arrayLength=capacity;
    listSize=0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& thelist) //复制构造函数
{
    element=new T[thelist.arrayLength];
    arrayLength=thelist.arrayLength;
    listSize=thelist.listSize;
    for(int i=0;i<listSize;i++){
        element[i]=thelist.element[i];
    }
}

template<class T>
void arrayList<T>::extend()
{
    T* temp=new T[arrayLength*2];
    for(int i=0;i<listSize;i++){
        temp[i]=element[i];
    }
    delete[] element;
    element=temp;
    arrayLength*=2;
}

template<class T>
void arrayList<T>::checkIndex(int index)
{
    if(index<0||index>=listSize){
        ostringstream s;
        s<<"index = "<<index<<" size = "<<listSize;
        throw invalid_argument(s.str());
    }
}

template<class T>
void arrayList<T>::push_back(const T& theElement)
{
    if(listSize==arrayLength)
        extend();
    element[listSize++]=theElement;
}

template<class T>
void arrayList<T>::insert(int index,const T& theElement)
{
    if(index<0||index>listSize){
        ostringstream s;
        s<<"index = "<<index<<" size = "<<listSize;
        throw invalid_argument(s.str());
    }
    if(listSize==arrayLength) extend();
    for(int i=listSize;i>index;i--){
        element[i]=element[i-1];
    }
    element[index]=theElement;
    listSize++;
}

template<class T>
void arrayList<T>::pop_back()
{
    if(is_empty()){
        ostringstream s;
        s<<"数组元素为空";
        throw out_of_range(s.str());
    }
    element[--listSize].~T();
}

template<class T>
void arrayList<T>::erase(int index)
{
    checkIndex(index);
    for(int i=index;i<listSize-1;i++){
        element[i]=element[i+1];
    }
    element[--listSize].~T();
}

template<class T>
int arrayList<T>::_find(const T& theElement)
{
    for(int i=0;i<listSize;i++){
        if(element[i]==theElement) return i;
    }
    return -1;
}
/*template<class T>
ostream& operator<<(ostream& out,const T& value)
{
    out<<value;
    return out;
}*/

#endif