#include<iostream>
#include<stdexcept>
#include"dictionary.h"
using namespace std;

//线性探查
template<class K,class E>
class hashTable
{
private:
    pair<K,E>** table;
    int listSize; 
    int divisor;    //除数，也可以看作容量
    int hash(const K& key)
    {
        return key%divisor;
    }
public:
    hashTable(int capacity);
    ~hashTable();
    void inseart(const pair<K,E>& thePair);
    void erase(const K& key);
    int search(const K& key);         //返回可以插入的位置
    pair<K,E>* find(const K& key);    //返回键值对
};

template<class K,class E>
hashTable<K,E>::hashTable(int capacity)
{
    divisor=capacity;
    listSize=0;
    table=new pair<K,E>[capacity];
    for(int i=0;i<capacity;i++){
        table[i]=NULL;
    }
}

template<class K,class E>
hashTable<K,E>::~hashTable()
{
    for(int i=0;i<divisor;i++){
        delete[] table[i];
    }
    delete[] table;
}

template<class K,class E>
void hashTable<K,E>::inseart(const pair<K,E>& thePair)
{
    int b=search(thePair.first);
    if(table[b]==NULL){
        table[b]=new pair<K,E>(thePair);
        listSize++;
    }
    else{
        if(table[b]->first==thePair.first){
            table[b]->second=thePair.second;
        }
        else throw length_error("hash is full");
    }
}

template<class K,class E>
void hashTable<K,E>::erase(const K& key)
{
    int b=search(key);
    if(table[b]==NULL||table[b]->first!=key)
        throw invalid_argument("Not find the key");
    if(table[b]->first==key){
        int current=(b+1)%divisor;
        while(table[current]!=NULL){
            if(hash(table[current]->first)==current) break;
            else{
                table[b]->first=table[current]->first;
                table[b]->second=table[current]->second;
                b=current;
                current=(current+1)%divisor;
            }
        }
        delete table[b];
        table[b]=NULL;
        listSize--;
    }
}

template<class K,class E>
int hashTable<K,E>::search(const K& key)
{
    int index=hash(key);
    int i=index;
    do
    {
        if(table[index]!=NULL&&table[index]->first!=key)
            index=(index+1)%divisor;
        else break;
    } while (index!=i);
    return index;
}

template<class K,class E>
pair<K,E>* hashTable<K,E>::find(const K& key)
{
    int b=search(key);
    if(table[b]==NULL||table[b]->first!=key) return NULL;
    return table[b];
}

//链式散列
template<class K,class E>
class hashChains
{
private:
    sortedChain<K,E>* table;
    int divisor;
    int hash(const K& key)
    {
        return key%divisor;
    }
public:
    hashChains(int capacity);
    ~hashChains(){ delete[] table;}
    pair<K,E>* find(const K& key);
    void insert(const pair<K,E>& thePair);
    void erase(const K& key);
};

template<class K,class E>
hashChains<K,E>::hashChains(int capacity)
{
    divisor=capacity;
    table=new sortedChain<K,E>[capacity];
}

template<class K,class E>
pair<K,E>* hashChains<K,E>::find(const K& key)
{
    int index=hash(key);
    pair<K,E>* thepair=table[index].find(key);
    if(thepair==NULL)
        throw invalid_argument("Not find the key");
    return thepair;
}

template<class K,class E>
void hashChains<K,E>::insert(const pair<K,E>& thePair)
{
    int index=hash(thePair.first);
    table[index].insert(thePair);
}

template<class K,class E>
void hashChains<K,E>::erase(const K& key)
{
    int index=hash(key);
    table[index].erase(key);
}
