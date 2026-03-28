#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main(){
    int q,sign,num;
    cin>>q;
    set<int> s;
    while(q--){
        sign=0;
        cin>>sign>>num;
        switch(sign){
            case 1:
                s.insert(num);
                break;
            case 2:
                s.erase(num);
                break;
            case 3:
                auto it = s.lower_bound(num);
                if (it!=s.end()){
                    cout<<*it<<endl;
                }else{
                    cout<<-1<<endl;
                }
        }
    }
    return 0;
}