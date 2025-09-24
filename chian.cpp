#include"chain.h"
int main(){
    chain<int> a;
    for(int i=0;i<5;i++){
        a.push_back(i+1);
    }
    a.output();
    a.reverse();
    a.output();
    return 0;
}