#ifndef GRAPH
#define GRAPH

#include<iostream>
using namespace std;

//邻接矩阵描述
class adjMatrixGraph
{
private:
    int n; //顶点数
    int e; //边数
    int** adjMatrix; //邻接矩阵
public:
    adjMatrixGraph(int N);
    ~adjMatrixGraph();
    void insertEdge(int i,int j,int weight);
    void removeEdge(int i,int j);
    bool isEdge(int i,int j) const;
    int getNumOfVertices() const { return n; }
    void set(int i,int j,int weight){ adjMatrix[i][j]=weight; }
    int get(int i,int j) const { return adjMatrix[i][j]; }
};

adjMatrixGraph::adjMatrixGraph(int N)
{
    n=N;
    e=0;
    adjMatrix=new int*[n];
    for(int i=0;i<n;i++){
        adjMatrix[i]=new int[n];
        for(int j=0;j<n;j++)
            adjMatrix[i][j]=0; //初始化为0，表示没有边
    }
}

adjMatrixGraph::~adjMatrixGraph()
{
    for(int i=0;i<n;i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}

void adjMatrixGraph::insertEdge(int i,int j,int weight)
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return;
    }
    if(adjMatrix[i][j]==0){
        adjMatrix[i][j]=weight; //表示有边
        e++;
    }
}

void adjMatrixGraph::removeEdge(int i,int j)
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return;
    }
    if(adjMatrix[i][j]!=0){
        adjMatrix[i][j]=0; //表示没有边
        e--;
    }
}

bool adjMatrixGraph::isEdge(int i,int j) const
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return false;
    }
    return adjMatrix[i][j]!=0;
}

//邻接链表描述
struct adjListNode
{
    int vertex;
    int weight;
    adjListNode* next;
    adjListNode(int v,int w,adjListNode* n=NULL):vertex(v),weight(w),next(n){}
};

class adjLinkedGraph
{
private:
    int n; //顶点数
    int e; //边数
    adjListNode** adjList; //邻接表
public:
    adjLinkedGraph(int N);
    ~adjLinkedGraph();
    void insertEdge(int i,int j,int weight);
    void removeEdge(int i,int j);
    bool isEdge(int i,int j) const;
    int getNumOfVertices() const { return n; }
};

adjLinkedGraph::adjLinkedGraph(int N)
{
    n=N;
    e=0;
    adjList=new adjListNode*[n];
    for(int i=0;i<n;i++)
        adjList[i]=NULL; //初始化为空链表
}

adjLinkedGraph::~adjLinkedGraph()
{
    for(int i=0;i<n;i++){
        adjListNode* p=adjList[i];
        while(p!=NULL){
            adjListNode* temp=p;
            p=p->next;
            delete temp;
        }
    }
    delete[] adjList;
}

void adjLinkedGraph::insertEdge(int i,int j,int weight)
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return;
    }
    adjListNode* p=adjList[i];
    if(p==NULL){
        adjList[i]=new adjListNode(j,weight,NULL);
        e++;
        return;
    }
    while(p->next!=NULL){
        if(p->vertex==j){
            p->weight=weight; //更新权重
            return;
        }
        p=p->next;
    }
    p->next=new adjListNode(j,weight,NULL);
    e++;
}

void adjLinkedGraph::removeEdge(int i,int j)
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return;
    }
    adjListNode* p=adjList[i];
    adjListNode* prev=NULL;
    while(p!=NULL){
        if(p->vertex==j){
            if(prev==NULL)
                adjList[i]=p->next;
            else
                prev->next=p->next;
            delete p;
            e--;
            return;
        }
        prev=p;
        p=p->next;
    }
}

bool adjLinkedGraph::isEdge(int i,int j) const
{
    if(i<0||i>=n||j<0||j>=n){
        cerr<<"Error: invalid vertex index."<<endl;
        return false;
    }
    adjListNode* p=adjList[i];
    while(p!=NULL){
        if(p->vertex==j)
            return true;
        p=p->next;
    }
    return false;
}



















#endif