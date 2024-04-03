#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main(){

    int N = 5;
    int M = 1000;
    int p = 2 ;

    vector<queue<int> > gate;
    for(int i=1;i<=N;i++){
        gate.push_back(queue<int>());
        gate.back().push(0);
    }

    int waiting_time = 0;

    for(int i=0 ; i<M/2 ; i++){
        int index = rand() % N; // randomly assign gates to people
        gate[index].push(waiting_time=+p);
    }

     for(int i=1;i<=N;i++){
        cout<<"total no. of people in gate "<<i<<" are "<<gate[i].size()<<endl;
     }
     
    for(int i=1;i<=N;i++){
        cout<<"waiting time for gate "<<i<<" is "<<gate[i].size()*p<<endl;
    }


}