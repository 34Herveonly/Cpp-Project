#include <iostream>
#include <queue>

using namespace std;

struct Process {
    int id;
    int burstTime;
};

void roundRobinScheduling(Process processes[], int n, int quantum) {
    queue<Process> processQueue;
    int currentTime = 0;

    while (true) {
        bool allProcessesCompleted = true;
        for (int i = 0; i < n; ++i) {
            if (processes[i].burstTime > 0) {
                allProcessesCompleted = false;

                int executionTime = min(quantum, processes[i].burstTime);
                processes[i].burstTime -= executionTime;
                currentTime += executionTime;

                cout << "Process " << processes[i].id << " executes from time "
                     << currentTime - executionTime << " to " << currentTime << endl;

                if (processes[i].burstTime == 0) {
                    cout << "Process " << processes[i].id << " completed." << endl;
                } else {
                    processQueue.push(processes[i]);
                }
            }
        }

        if (allProcessesCompleted) {
            break;
        }

        while (!processQueue.empty() && processQueue.front().burstTime <= 0) {
            processQueue.pop();
        }

        if (!processQueue.empty()) {
            Process currentProcess = processQueue.front();
            processQueue.pop();
            processQueue.push(currentProcess);
        }
    }
}

int main() {
    int n, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; ++i) {
        processes[i].id = i;
        cout << "Enter burst time for process " << i << ": ";
        cin >> processes[i].burstTime;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    roundRobinScheduling(processes, n, quantum);

    return 0;
}
