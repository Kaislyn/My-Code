#include<iostream>
#include<set>

using namespace std;

int main(){
    int q;
    cin>>q;
    int sign,num;
    multiset<int> ms;
    while(q--){
        cin>>sign>>num;
        switch(sign){
            case 1:
                ms.insert(num);
                break;
            case 2:{
                auto it=ms.find(num);
                if(it!=ms.end()){
                    ms.erase(it);   
                }
                break;
            }
            case 3:{
                auto up=ms.upper_bound(num);
                if(up!=ms.end()){
                    cout<<*up<<endl;
                }else{
                    cout<<-1<<endl;
                }
            }
        }
    }
    return 0;
}