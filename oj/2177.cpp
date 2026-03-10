#include<iostream>
#include<map>
#include<string>

using namespace std;

int main(){
    int q;
    cin>>q;
    string str;
    int sign,num;
    map<string,int> m;
    while(q--){
        cin>>sign;
        switch(sign){
            case 1:{
                cin>>str>>num;
                m[str]+=num;
                break;
            }
            case 2: {
                cin>>str>>num;
                if(m[str]<num){
                    cout<<-1<<endl;
                    continue;
                }else{
                    m[str]-=num;
                    cout<<m[str]<<endl;
                }
                break;
            }
            case 3: {
                cin>>str;
                if(m.find(str)!=m.end()){
                    cout<<m[str]<<endl;
                }else{
                    cout<<0<<endl;
                }
            }
        }
    }
    return 0;
}