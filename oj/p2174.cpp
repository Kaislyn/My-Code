#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int> > adj(n+1);
    for(int i=1;i<=m;i++){
        int a,b; // 起始边，终点边
        cin>>a>>b;
        adj[a].push_back(b);
    }
    for(auto &vec:adj){
        sort(vec.begin(),vec.end());
    }
    vector<int> ans;
    while(q--){
        int a,b;
        cin>>a>>b;
        if(b<=adj[a].size()){
            ans.push_back(adj[a][b-1]);
        }else{
            ans.push_back(-1);
        }
    }
    for(auto i:ans){
        cout<<i<<endl;
    }
    return 0;
}