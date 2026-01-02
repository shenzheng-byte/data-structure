#include"stack.h"
#include<iostream>
#include<string>
using namespace std;

void printMatchedPairs(string expr)
{
    //¿®∫≈∆•≈‰
    arrayStack<int> s;
    int length=(int)expr.length();
    for(int i=0;i<length;i++){
        if(expr[i]=='(') s.push(i);
        else if(expr[i]==')'){
            if(s.is_empty()){
                cout<<"Œ¥∆•≈‰”“¿®∫≈Œª÷√: "<<i<<endl;
            }
            else{
                int pos=s.get_top();
                s.pop();
                cout<<"∆•≈‰µƒ¿®∫≈Œª÷√: "<<pos<<" , "<<i<<endl;
            }
        }
    }
    while(!s.is_empty()){
        cout<<"’ª÷– £”‡Œ¥∆•≈‰◊Û¿®∫≈Œª÷√: "<<s.get_top()<<endl;
        s.pop();
    }
}

int main()
{
    string expr="(a+b)*(c-d)/(e+f))+(g*h)-(i+j*(k-l)";
    printMatchedPairs(expr);
    return 0;
}