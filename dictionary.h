#ifndef DICTIONARY
#define DICTIONARY
#include<iostream>
#include<stdexcept>
using namespace std;
template<class K,class E>
class sortedArrayList
{
private:
    pair<K,E>* data;
    int listSize;
    int arrayLength;
public:
    sortedArrayList(int capacity=10);
    ~sortedArrayList(){ delete data; }
    bool is_empty(){ return listSize==0;}
    int get_listSize(){ return listSize;}
    int get_arrayLength(){ return arrayLength;}
    void extend();

    pair<K,E>* find(const K& theKey);
    void insert(const pair<K,E>& thePair);
    void erase(const K& theKey);
};

template<class K,class E>
sortedArrayList<K,E>::sortedArrayList(int capacity)
{
    if(capacity<0){
        throw invalid_argument("容量不能为0");
    }
    data=new pair<K,E>[capacity];
    arrayLength=capacity;
    listSize=0;
}

template<class K,class E>
void sortedArrayList<K,E>::extend()
{
    pair<K,E>* temp=new pair<K,E>[arrayLength*2];
    for(int i=0;i<arrayLength;i++){
        temp[i]=data[i];
    }
    arrayLength*=2;
    delete[] data;
    data=temp;
}

template<class K,class E>
pair<K,E>* sortedArrayList<K,E>::find(const K& theKey)
{
    int left=0,right=listSize-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(data[mid].first==theKey)
            return &data[mid];
        else if(data[mid].first<theKey)
            left=mid+1;
        else if(data[mid]>theKey)
            right=mid-1;
    }
    return NULL;
}

template<class K,class E>
void sortedArrayList<K,E>::insert(const pair<K,E>& thePair)
{
    if(find(thePair.first)!=NULL){
        pair<K,E>* it=find(thePair.first);
        it->second=thePair.second;
        return ;
    }
    else{
        if(listSize==arrayLength) 
            extend();
        int i;
        for(i=listSize;i>0;i--){
            if(data[i].first>thePair.first)
                data[i]=data[i-1];
            else break;
        }
        data[i]=thePair;
        listSize++;
    }
}

template<class K,class E>
void sortedArrayList<K,E>::erase(const K& theKey)
{
    int index=-1;
    int left=0,right=listSize-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(data[mid].first==theKey)
            index=mid;
        else if(data[mid].first<theKey)
            left=mid+1;
        else if(data[mid]>theKey)
            right=mid-1;
    }
    if(index==-1) throw out_of_range("未找到键");
    else{
        for(int i=index;i<listSize-1;i++){
            data[i]=data[i+1];
        }
        data[listSize-1].~pair<K,E>;
        listSize--;
    }
}


#endif