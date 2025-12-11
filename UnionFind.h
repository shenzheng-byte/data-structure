#ifndef UNIONFIND
#define UNIONFIND
#include<iostream>
using namespace std;

//数组实现
class UnionFindArray
{
private:
    int* equivClass;   //存储并查集
    int n;  //元素个数
public:
    UnionFindArray(int size);
    void unite(int calssA,int classB);
    int find(int element);
    ~UnionFindArray(){ delete[] equivClass;}
};

UnionFindArray::UnionFindArray(int size)
{
    n=size;
    equivClass=new int [n+1];
    for(int i=1;i<=n;i++){
        equivClass[i]=i;
    }
}

void UnionFindArray::unite(int classA,int classB)
{
    for(int k=1;k<=n;k++){
        if(equivClass[k]==classB)
        equivClass[k]=classA;
    }
}

int UnionFindArray::find(int element)
{
    return equivClass[element];
}

//链表实现
struct equiveNode
{
    int equiveClass;
    int size;
    int next;
};

class UnionFindChain
{
private:
    equiveNode* node;
    int n;
public:
    UnionFindChain(int size);
    void unite(int classA,int classB);
    int find(int element);
    ~UnionFindChain(){ delete[] node; }
};

UnionFindChain::UnionFindChain(int size)
{
    n=size;
    node=new equiveNode[n+1];
    for(int i=1;i<=n;i++){
        node[i].equiveClass=i;
        node[i].next=0;
        node[i].size=1;
    }
}

void UnionFindChain::unite(int classA,int classB)
{
    if(node[classA].size>node[classB].size)
        swap(classA,classB);
    int k;
    for(k=classA;node[k].next!=0;k=node[k].next){
        node[k].equiveClass=classB;
    }
    node[k].equiveClass=classB;//链表最后一个节点

    node[classB].size+=node[classA].size;
    node[k].next=node[classB].next;
    node[classB].next=classA;
}

int UnionFindChain::find(int element)
{
    return node[element].equiveClass;
}

//树形实现
//优化：路径压缩+按秩合并
class unionFind
{
private:
    int* parent;  //根节点数组
    int* rank;   //树的高度
    int size;
public:
    unionFind(int n);
    ~unionFind(){ delete[] parent; delete[] rank; }
    int find(int x);
    bool unite(int x,int y);
};

unionFind::unionFind(int n)
{
    size=n;
    parent=new int[n+1];
    rank=new int[n+1]{0};
    for(int i=1;i<=n;i++)
        parent[i]=i;
}

int unionFind::find(int x)
{
    if(parent[x]!=x)
        parent[x]=find(parent[x]);
    return parent[x];
}

bool unionFind::unite(int x,int y)
{
    int rootX=find(x);
    int rootY=find(y);
    if(rootX==rootY) return false;
    if(rank[rootX]<rank[rootY])
        parent[rootX]=rootY;
    else{
        parent[rootY]=rootX;
        if(rank[rootX]==rank[rootY])
            rank[rootX]++;
    }
    return true;
}

#endif