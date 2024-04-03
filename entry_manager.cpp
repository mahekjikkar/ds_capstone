#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(){

    int N = 5;
    int M = 1000;
    int p = 2 ;

    vector<queue<int> > gate;
    for(int i=0;i<N;i++){
        gate.push_back(queue<int>());
    }

    int waiting_time = 0;

    for(int i=0 ; i<M/2 ; i++){
        int index = rand() % N; // randomly assign gates to people
        gate[index].push(waiting_time+=p);
    }

     for(int i=0;i<N;i++){
        cout<<"total no. of people in gate "<<i+1<<" are "<<gate[i].size()<<endl;
     }
     
    for(int i=0;i<N;i++){
        cout<<"waiting time for gate "<<i+1<<" is "<<gate[i].size()*p<<endl;
    }

    int minQueue = 0;
    for (int i = 0; i < N; ++i)
    {
        if (gate[i].size() < gate[minQueue].size())
        {
            minQueue = i;
        }
    }
    cout<<"gate no. "<< minQueue+1<<" has less waiting time of "<<gate[minQueue].size()*p<<" mins."<<endl; 

    int ans;
    cout<<"Are you already in queue? (enter 1 for yes and 0 for no)"<<endl;
    cin>>ans;
    if(ans==0){
        bool stadiumFull = true;
        for (int i = 0; i < N; ++i) {
            if (gate[i].size() < M) {
                stadiumFull = false;
                break;
                  }
        }
        int minQueue = 0;
        if (!stadiumFull)
        {
            
            for (int i = 0; i < N; ++i)
            {
                if (gate[i].size() < gate[minQueue].size())
                {
                    minQueue = i;
                }
            }

            gate[minQueue].push(p); // Assuming new attendee's waiting time is p
            cout << "You have been added to queue " << minQueue + 1 << endl;
        }
        else
        {
            cout << "Stadium is full. Cannot add more attendees." << endl;
            exit(1);
        }
    }

    return 0;
}
