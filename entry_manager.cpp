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
        }

        // Printing the waiting time of each queue before switching (optimization)
        cout << "Displaying Number of people at each gate before optimization" << endl<<endl;
        displayStatus();

        optimizeInitialRandomPeople();

         //Printing the waiting time of each queue after switching (optimization)
        cout << "Displaying Number of people at each gate after optimization" << endl;
        displayStatus();

 }

//This function will balance the first M/2 randomised people into ordered queues by popping people from larger queue and pushing them into shorter queue according to the average calculated
void optimizeInitialRandomPeople() {
        float idealPeoplePerGate = (float)M / (2 * N); // Calculating average of first M/2 randomised people for balancing

        for (int i = 0; i < N; ++i) {
            while (entryGates[i].size() > idealPeoplePerGate) {
                int person = entryGates[i].back();
                entryGates[i].pop();
                int j = (i + 1) % N; // Start checking from the next gate
                while (j != i) {
                    if (entryGates[j].size() < idealPeoplePerGate) {
                        entryGates[j].push(person);
                        break;
                    }
                    j = (j + 1) % N;
                }
                if (j == i) {
                    entryGates[i].push(person); // If no shorter queue found, push the person back to the original queue
                    break;
                }
            }
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
    while(people!=(M+1)){
        entryGates[i].push(1);
        ++i;
        ++people;
        if(i==N){
            i=0;       // again wrapping around to first queue if it reaches the last queue
        }
        }
    }

void displayStatus(){

    for(int i=0;i<N;i++){
        cout<<"total no. of people in gate "<<i+1<<" are "<<entryGates[i].size()<<endl;
    }

    }
};

