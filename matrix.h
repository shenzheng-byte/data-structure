#ifndef MATRIX
#define MATRIX
#include<iostream>
#include<stdexcept>
using namespace std;

template<class T>
class matrix
{
private:
    int rows;
    int columns;
    T *element;
public:
    matrix(int theRows=0,int theColumns=0);
    matrix(const matrix<T>& m);
    ~matrix() {delete[] element;}
    int get_rows() const {return rows;}
    int get_columns() const {return columns;}

    T& operator()(int i,int j) const;
    matrix<T>& operator= (const matrix<T>& m);
    matrix<T> operator+ (const matrix<T>& m);
    matrix<T> operator- (const matrix<T>& m);
    matrix<T> operator* (const matrix<T>& m);

};

template<class T>
matrix<T>::matrix(int theRows=0,int theColumns=0)
{
    if(theRows<=0||theColumns<=0){
        throw out_of_range("Rows and Columns must be >0");
    }
    this->rows=theRows;
    this->columns=theColumns;
    element=new T[theRows*theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
    rows=m.rows;
    columns=m.columns;
    element=new T [rows*columns];
    for(int i=0;i<rows*columns;i++){
        element[i]=m.element[i];
    }
}

template<class T>
T& matrix<T>::operator()(int i,int j) const
{
    if(i<1||i>rows||j<1||j>columns){
        throw out_of_range();
    }
    return element[(i-1)*columns+j-1];
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    if(this!=&m){
        delete[] element;
        rows=m.rows;
        columns=m.columns;
        element=new T [rows*columns];
        for(int i=0;i<rows*columns;i++){
            element[i]=m.element[i];
        }
    }
    return *this;
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m)
{
    if(rows!=m.rows||columns!=m.columns){
        throw invalid_argument();
    }
    matrix<T> w(rows,columns);
    for(int i=0;i<rows*columns;i++){
        w[i]=element[i]+m.element[i];
    }
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m)
{
    if(rows!=m.rows||columns!=m.columns){
        throw invalid_argument();
    }
    matrix<T> w(rows,columns);
    for(int i=0;i<rows*columns;i++){
        w[i]=element[i]-m.element[i];
    }
    return w;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m)
{
    if(columns!=m.rows){
        throw exception();
    }
    matrix<T> w(rows,m.columns);
    int ct=0,cm=0,cw=0;

    for(int i=1;i<=rows;i++){
        for(int j=1;j<=m.columns;j++){
            T sum=element[ct]*m.element[cm];
            for(int k=2;k<=columns;k++){
                ct++;
                cm+=m.columns;
                sum+=element[ct]*m.element[cm];
            }
            w.element[cw++]=sum;
            ct-=columns-1; 
            cm=j;
        }
        ct+=columns;
        cm=0;
    }
    return w;
}


#endif