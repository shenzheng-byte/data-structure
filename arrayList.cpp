#include"arrayList.h"
int main(){
    arrayList<int> a(20);
    for(int i=0;i<20;i++){
        a.push_back(i);
    }
    for(int i=0;i<20;i++){
        cout<<a[i]<<endl;
    }
    return 0;
}