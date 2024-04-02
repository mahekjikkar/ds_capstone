#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class stadium
{
    protected:

    int N;          // no. of entry gates
    int M;          // no. of people
    int p;          // time taken by single attendee to enter any gate

    public:

    stadium()
    {
        cout<<"Enter total no. of gates in your stadium: ";
        cin>>N;

        cout<<"enter total no. of attendees entering the stadium:";
        cin>>M;

        cout<<"time taken by a single attendee to enter any gate:";
        cin>>p;

    }

    friend void assign_gates(stadium s1);
};

class Node
{
    protected:

    int no;
    int wait_time; 

    public:

    Node(int i , int j){
        no = i;
        wait_time = j;
    }

};

void assign_gates(stadium s1) {

    // creation of gates
    vector<queue<Node>>gate ;      // declaring a vector of queues where each queue where each queue holds objects of node class
    

    // assigning randomly different gates to M/2 people


}