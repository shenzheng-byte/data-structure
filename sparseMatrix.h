#ifndef SPARSE
#define SPARSE
#include<iostream>
#include<stdexcept>
#include"arrayList.h"
using namespace std;

template<class T>
struct matrixTerm
{
    int row;
    int col;
    T value;
};

template<class T>
class sparseMatrix
{
private:
    int rows;
    int cols;
    arrayList<matrixTerm<T>> term;
public:
    sparseMatrix(){ rows=0; cols=0; }
    sparseMatrix(const sparseMatrix<T>& s):rows(s.rows),cols(s.cols),term(s.term){}
    T get(const int theRow,const int theColumn);
    void set(const int theRow,const int theColumn,const T Value);
    void transpose();
    sparseMatrix<T> add(const sparseMatrix<T>& b);
    sparseMatrix<T> multiply(const sparseMatrix<T>& b);
};

template<class T>
T sparseMatrix<T>::get(const int theRow,const int theColumn)
{
    if(theRow<1||theRow>rows||theColumn<1||theColumn>cols)
    throw out_of_range();
    typename arrayList<matrixTerm<T>>::iterator it=term.begin();
    typename arrayList<matrixTerm<T>>::iterator itEnd=term.end();
    while(it!=itEnd)
    {
        if((*it).row==theRow&&(*it).col==theColumn){
            return (*it).value;
        }
        it++;
    }
    if(it==itEnd) return T();
}

template<class T>
void sparseMatrix<T>::set(const int theRow,const int theColumn,const T Value)
{
    if(theRow<1||theRow>rows||theColumn<1||theColumn>cols)
    throw out_of_range();
    typename arrayList<matrixTerm<T>>::iterator it=term.begin();
    typename arrayList<matrixTerm<T>>::iterator itEnd=term.end();
    int index=0,flag=0;
    while(it!=itEnd)
    {
        if((*it).row==theRow&&(*it).col==theColumn){
            (*it).value=Value;
            break;
        } 
        else if((*it).row>theRow||((*it).row==theRow&&(*it).col>theColumn)){
            matrixTerm<T> w;
            w.row=theRow;
            w.col=theColumn;
            w.value=Value;
            term.insert(w,index);
            flag=1;
            break;
        }
        index++;
        it++;
    }
    if(!flag){
        matrixTerm<T> w;
        w.row=theRow;
        w.col=theColumn;
        w.value=Value;
        term.insert(w,index);
    }
}

template<class T>
sparseMatrix<T> sparseMatrix<T>::add(const sparseMatrix<T>& b)
{
    if(rows!=b.rows||cols!=b.cols){
        throw exception();
    }
    sparseMatrix<T> c;
    c.rows=rows;
    c.cols=cols;
    c.term.clear();
    int cSize=0;

    typename arrayList<matrixTerm<T>>::iterator it=term.begin();
    typename arrayList<matrixTerm<T>>::iterator ib=b.term.begin();
    typename arrayList<matrixTerm<T>>::iterator itEnd=term.end();
    typename arrayList<matrixTerm<T>>::iterator ibEnd=b.term.end();

    while(it!=itEnd&&ib!=ibEnd){
        int tindex=((*it).row-1)*cols+(*it).col;
        int bindex=((*ib).row-1)*cols+(*ib).col;

        if(tindex<bindex){
            c.term.insert(*it,cSize++);
            it++;
        }
        else if(tindex>bindex){
            c.term.insert(*ib,cSize++);
            ib++;
        }
        else{
            if((*it).value+(*ib).value!=0){
                matrixTerm<T> w;
                w.col=(*it).col;
                w.row=(*it).row;
                w.value=(*it).value+(*ib).value;
                c.term.insert(w,cSize++);
            }
            it++;
            ib++;
        }
    }
    for(; it!=itEnd;it++){
        c.term.insert(*it,cSize++);
    }
    for(; ib!=ibEnd;ib++){
        c.term.insert(*ib,cSize++);
    }
    return c;
}

template<class T>
void sparseMatrix<T>::transpose()
{   
    arrayList<matrixTerm<T>> b(term.get_arrrayLength());
    b.resize(term.get_listSize());
    int* colSize=new int [cols+1];
    int* rowNext=new int [cols+1];

    for(int i=0;i<=cols;i++){
        colSize[i]=0;
    }
    for(typename arrayList<matrixTerm<T>>::iterator i=term.begin();i!=term.end();i++){
        colSize[(*i).col]++;
    }
    rowNext[1]=0;
    for(int i=2;i<=cols;i++){
        rowNext[i]=rowNext[i-1]+colSize[i-1];
    }
    matrixTerm<T> m;
    for(typename arrayList<matrixTerm<T>>::iterator i=term.begin();i!=term.end();i++){
        int j=rowNext[(*i).col];
        rowNext[(*i).col]++;
        m.col=(*i).row;
        m.row=(*i).col;
        m.value=(*i).value;
        b.set(j,m);
    }
    int temp=cols;
    cols=rows;
    rows=temp;
    term=b;
    delete[] colSize;
    delete[] rowNext;
}

template<class T>
sparseMatrix<T> sparseMatrix<T>::multiply(const sparseMatrix<T>& b)
{
    if(cols!=b.rows){
        throw invalid_argument("The sparseMatrix b is invalid!");
    }
    sparseMatrix<T> c;
    c.cols=b.cols;
    c.rows=rows;
    int cSize=0;
    int br=b.rows,bc=b.cols;
    int* rowSize=new int[br+1];
    int* rowNext=new int[br+1];
    int* Answer=new int[bc+1];
    for(int i=1;i<=br;i++)
        rowSize=0;
    typename arrayList<matrixTerm<T>>::iterator itb=b.term.begin();
    typename arrayList<matrixTerm<T>>::iterator itbEnd=b.term.end();
    for(;itb!=itbEnd;itb++){
        rowSize[(*itb).row]++;
    }
    rowNext[1]=0;
    for(int i=2;i<=b.rows;i++){
        rowNext[i]=rowNext[i-1]+rowSize[i-1];
    }

    int p=0;
    for(int i=1;i<=rows&&p<term.get_listSize();i++){
        for(int j=1;j<=bc;j++)
            Answer[j]=0;
        while(p<term.get_listSize()&&term[p].row==i){
            int t=term[p].col;
            if(rowSize[t]!=0){
                for(int z=rowNext[t];z<rowNext[t]+rowSize[t];z++)
                    Answer[b.term[z].col]+=term[p].value*b.term[z].value;
            }
            p++;
        }
        for(int k=1;k<=b.cols;k++){
            if(Answer[k]!=0)
                c.term.insert(cSize++,Answer[k]);
        }
    }
    delete[] rowNext;
    delete[] rowSize;
    delete[] Answer;
    return c;
}

#endif