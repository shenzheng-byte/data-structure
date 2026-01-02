#include"stack.h"
#include<iostream>
using namespace std;

//递归实现汉诺塔
void towersOfHanoi(int n,int x,int y,int z)
{
    if(n>0){
        towersOfHanoi(n-1,x,z,y);
        cout<<"Move top disk from tower "<<x<<" to top of tower "<<y<<endl;
        towersOfHanoi(n-1,z,y,x);
    }
}

//使用栈实现
arrayStack<int> tower[4];
void moveAndShow(int n,int x,int y,int z)
{
    if(n>0){
        moveAndShow(n-1,x,z,y);
        int d=tower[x].get_top();
        tower[x].pop();
        tower[y].push(d);
        cout<<"Move top disk from tower "<<x<<" to top of tower "<<y<<endl;
        moveAndShow(n-1,z,y,x);
    }
}

int main()
{ 
    int n;
    cout<<"请输入汉诺塔的层数: ";
    cin>>n;
    towersOfHanoi(n,1,2,3);
    cout<<"使用栈实现汉诺塔过程如下: "<<endl;
    for(int i=n;i>=1;i--){
        tower[1].push(i);
    }
    moveAndShow(n,1,2,3);
    for(int i=1;i<=n;i++){
        cout<<tower[2].get_top()<<" ";
        tower[2].pop();
    }
    return 0;
}




