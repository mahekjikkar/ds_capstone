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

        cout<< "Enter the total number of attendees in the stadium"<<endl;
        cin >> M;

        cout << "Time taken by single attendee to enter any gate"<<endl;
        cin >> p;

        //Initializing the vector
        entryGates.resize(N);
        
        // Initial random assignment of M/2 people to gates
        for (int i = 1; i <= M/2; ++i) {
            int gateIndex = rand() % N; // Randomly select a gate index
            entryGates[gateIndex].push(i); // Assign the person to the selected gate

        // Printing the waiting time of each queue before switching (optimization)
        cout << "Displaying waiting time of gates before optimization" << endl;
        for (int i=0; i<N; ++i) {
            cout<<"Waiting time for gate " << i+1 << " = " << entryGates[i].size()*p << endl;            
        }

        optimizeInitialRandomPeople();

        //Printing the waiting time of each queue after switching (optimization)
        cout << "Displaying waiting time of gates after optimization" << endl;
        for (int i=0; i<N; ++i) {
            cout<<"Waiting time for gate " << i+1 << " = " << entryGates[i].size()*p << endl;            
        }

    }

