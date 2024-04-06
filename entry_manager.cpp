#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib> // For using rand()
#include <ctime> // For seeding the random number generator (will efficiently randomise)

using namespace std;

class Stadium {
private:
    int N; // Number of entry gates
    int M; // Total number of people
    int p; // Time for a single attendee to enter any gate (in minutes)
    vector<queue<int>> entryGates;

public:
    Stadium()
    {
        cout<< "Enter the total number of gates in the stadium"<<endl;
        cin >> N;
        if(N<=0)
{
    cout << "Error, the total number of gates cannot be negative or zero" << endl;
    return;
}

        cout<< "Enter the total number of attendees in the stadium"<<endl;
        cin >> M;
        if(M<0)
        {
            cout << "Error, the total number of attendees cannot be negative"<< endl;
            return;
        }

        cout << "Time taken by single attendee to enter any gate"<<endl;
        cin >> p;
        if(p<0)
        {   
            cout << "Error, time taken to enter gate by attendee cannot be negative " << endl;
            return;
        }

        //Initializing the vector
        entryGates.resize(N);
        
        // Initial random assignment of M/2 people to gates
        for (int i = 1; i <= M/2; ++i) {
            int gateIndex = rand() % N; // Randomly select a gate index
            entryGates[gateIndex].push(i); // Assign the person to the selected gate
        }

        // Printing the waiting time of each queue before switching (optimization)
        cout << "Displaying Number of people at each gate before optimization" << endl<<endl;
        displayStatus();

        optimizeInitialRandomPeople();

         //Printing the waiting time of each queue after switching (optimization)
        cout << "Displaying Number of people at each gate after optimization" << endl;
        displayStatus();
        addingNewPeople();
 }

//This function will balance the first M/2 randomised people into ordered queues by popping people from larger queue and pushing them into shorter queue according to the average calculated
void optimizeInitialRandomPeople() {
    int idealPeoplePerGate = M / (2 * N);    // Calculating average of first M/2 randomized people for balancing

    // Balancing the queues
    for (int i = 0; i < N; ++i) {
        while (entryGates[i].size() > idealPeoplePerGate) {
            int person = entryGates[i].back(); 
            entryGates[i].pop(); // Popping the back person from the current gate
            for (int j = 0; j < N; ++j) {
                // Finding the destination gate (by iterating through each gate excluding the current gate)
                if (j != i && entryGates[j].size() < idealPeoplePerGate) {
                    entryGates[j].push(person);  // Pushing the back person to a destined smaller gate
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
    ;
    while (people < M / 2) {
        for (int i = 0; i < N && people < M / 2; i++) {
            entryGates[i].push(people + 1);                //Pushing the people that were left after optimization
            ++people;
        }
    }


// After balancing M/2 people now adding another M/2 people gate-wise 
void addingNewPeople(){

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
        entryGates[i].push(1);
        ++i;
        ++people;
        if(i==N){
            i=0;       // again wrapping around to first queue if it reaches the last queue
        }
        //dequeuing people from each gate after every p time
        for (int j = 0; j < N; ++j) {
            if (!entryGates[j].empty()) {
                entryGates[j].pop(); // Dequeuing the first person from each gate
                timeToEmpty[j] += p; // Incrementing the time taken for this gate to become empty
            }
        }
    }
    
    // Print the time taken by each gate to become empty
    cout << "Total time taken by each gate to become empty:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Gate " << i + 1 << ": " << timeToEmpty[i] << " minutes" << endl;
    }

    //The program ends after this since all people have entered the stadium
    cout << "All people have entered the stadium." << endl;
}

void displayStatus(){

    for(int i=0;i<N;i++){
        cout<<"total no. of people in gate "<<i+1<<" are "<<entryGates[i].size()<<endl;
    }

    }
};

