#include<iostream>
#include<queue>
#include<string>

using namespace std;

struct Task{
    string name;
    int time;
};

int main(){
    int task_num,QPU_time;
    cin>>task_num>>QPU_time;

    queue<Task> q;
    
    while(task_num--){
        Task task;
        cin>>task.name>>task.time;
        q.push(task);
    }
    
    int timelen=0;
    while(!q.empty()){
        if(q.front().time <= QPU_time){
            timelen+=q.front().time;
            cout<<q.front().name<<" "<<q.front().time<<endl;
            q.pop();
        }else{
            timelen+=QPU_time;
            q.front().time-=QPU_time;
            Task temp_task=q.front();
            q.pop();
            q.push(temp_task);
        }
    }
    return 0;
}