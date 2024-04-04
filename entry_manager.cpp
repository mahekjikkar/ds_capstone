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
        cout<< "enter the total number of gates in the stadium";
        cin >> N;

        cout<< " enter the total number of attendes in the stadium";
        cin >> M;

        cout << "time taken by singke attendee to enter any gate";
        cin >> p;
    }
