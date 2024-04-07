#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib> // For using rand()
#include <ctime> // For seeding the random number generator (will efficiently randomise)
#include <queue>
using namespace std;

class Stadium {
private:
    int N; // Number of entry gates
    int M; // Total number of people
    int p; // Time for a single attendee to enter any gate (in minutes)
    vector<deque<int>> entryGates;

public:
    Stadium()
    {
        cout<< "Enter the total number of gates in the stadium"<<endl;
        cin >> N;
        cout<<endl;
        if(N<=0)
{
    cout << "Error, the total number of gates cannot be negative or zero" << endl;
    return;
}

        cout<< "Enter the total number of attendees in the stadium"<<endl;
        cin >> M;
        cout<<endl;
        if(M<0)
        {
            cout << "Error, the total number of attendees cannot be negative"<< endl;
            return;
        }

        cout << "Time taken by single attendee to enter any gate"<<endl;
        cin >> p;
        cout<<endl;
        if(p<0)
        {   
            cout << "Error, time taken to enter gate by attendee cannot be negative " << endl;
            return;
        }
        cout<<endl;

        int vip_count;
        cout<< "Enter the number of VIPs arriving at stadium"<< endl;
        cin >> vip_count;
        if(vip_count < 0)
        {
            cout << "Error, number of VIPs cannot be negative" << endl;
            return;
        }
            queue<int> vip_queue;
            vip(vip_count,vip_queue);
            M = M-vip_count;
            cout << endl;

        //Initializing the vector
        entryGates.resize(N);
        
        // Initial random assignment of M/2 people to gates
        for (int i = 1; i <= M/2; ++i) {
            int gateIndex = rand() % N; // Randomly select a gate index
            entryGates[gateIndex].push_back(i); // Assign the person to the selected gate
        }

        // Printing the waiting time of each queue before switching (optimization)
        cout << "Displaying Number of people at each gate before optimization" << endl<<endl;
        displayStatus();

        optimizeInitialRandomPeople();

         //Printing the waiting time of each queue after switching (optimization)
        cout << "Displaying Number of people at each gate after optimization" << endl <<endl;
        displayStatus();

        cout<<endl;
        cout<<"Now the initial randomisation of M/2 people and their optimisation has been completed."<<endl<<"Now the gates will be opened and simultaneously the rest M/2 people will be enqueued inside the queues"<<endl<<endl;
        if(vip_count>0){
        cout << "Since, gates are open the dequeuing of VIPs have also been started simultaenously"<<endl<<endl;}
        
        addingNewPeople(vip_queue);
    }

//This function will balance the first M/2 randomised people into ordered queues by popping people from larger queue and pushing them into shorter queue according to the average calculated
void optimizeInitialRandomPeople() {
    int idealPeoplePerGate = M / (2 * N);    // Calculating average of first M/2 randomized people for balancing

    // Balancing the queues
    for (int i = 0; i < N; ++i) {
        while (entryGates[i].size() > idealPeoplePerGate) {
            int person = entryGates[i].back(); 
            entryGates[i].pop_back(); // Popping the back person from the current gate
            for (int j = 0; j < N; ++j) {
                // Finding the destination gate (by iterating through each gate excluding the current gate)
                if (j != i && entryGates[j].size() < idealPeoplePerGate) {
                    entryGates[j].push_back(person);  // Pushing the back person to a destined smaller gate
                    break;
                }
            }
        }
    }
    
    // Counting the total number of people after balancing
    int people = 0;
    for(int i = 0; i < N; i++) {
        people += entryGates[i].size();
    }
    
    // Filling remaining spaces to reach M/2 people only when the total number in optimised queues are not equal to M/2
    while (people < M / 2) {
        for (int i = 0; i < N && people < M / 2; i++) {
            entryGates[i].push_back(people + 1);                //Pushing the people that were left after optimization
            ++people;
        }
    }
}


// After balancing M/2 people now adding another M/2 people gate-wise 
void addingNewPeople(queue<int>& vip_queue){
    int vip_time = 0;
    int minQueue = 0;
    for (int i = 0; i < N; ++i)
    {
        if (entryGates[i].size() < entryGates[minQueue].size())
        {
            minQueue = i;
        }
    }

    int people = M/2+1;
    int i = minQueue;
    vector<int> timeToEmpty(N, 0); // creating a vector to store the time taken for each gate to become empty
    while(people!=(M+1)){
        entryGates[i].push_back(people);
        ++i;
        ++people;
        if(i==N){
            i=0;       // again wrapping around to first queue if it reaches the last queue
        }
        //dequeuing people from each gate after every p time
        for (int j = 0; j < N; ++j) {
            if(vip_queue.size()!=0)
            {
                vip_queue.pop();
                vip_time+=p;
            }
            
            if (!entryGates[j].empty()) {
                entryGates[j].pop_front(); // Dequeuing the first person from each gate
                timeToEmpty[j] += p; // Incrementing the time taken for this gate to become empty
            }
        }
    }
    
    // Print the time taken by each gate to become empty
    cout << "Total time taken by each gate to become empty:" << endl<<endl;
    for (int i = 0; i < N; ++i) {
        cout << "Gate " << i + 1 << ": " << timeToEmpty[i] << " minutes" << endl;
    }
    cout << "VIP Gate: "<< vip_time <<" minutes"<<endl <<endl;
    cout<<endl;
    //The program ends after this since all people have entered the stadium
    cout << "All people have entered the stadium." << endl;
}

     void vip(int vip_count,queue<int>& vip_queue)
{
     for(int i=1;i<= vip_count;i++)
    {
        vip_queue.push(i);
    }
}

void displayStatus(){

    for(int i=0;i<N;i++){
        cout<<"Total no. of people in gate "<<i+1<<":  "<<entryGates[i].size()<<endl;
    }
    cout<<endl;

    }
};

