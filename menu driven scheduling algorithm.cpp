#include <iostream>
#include <algorithm>
using namespace std;

void swap(int *a, int *b);
void calculateCompletionTime(int num, int mat[][3]);
void calculateTurnaroundTime(int num, int mat[][3]);
void displayResults(int num, int mat[][3], float avgTurnaroundTime, float avgWaitingTime);
void fcfs(int num, int mat[][3]);
void sjf_non_preemptive(int num, int mat[][3]);
void sjf_preemptive(int num, int mat[][3]);
void round_robin(int num, int mat[][3], int quantum);
void srtf(int num, int mat[][3]);

void calculate(int num, int mat[][3], float &avgTurnaroundTime, float &avgWaitingTime) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    
    int completionTime = 0;

    for (int i = 0; i < num; i++) {
        if (i == 0 || mat[i][1] > completionTime) {
            completionTime = mat[i][1];
        }
        completionTime += mat[i][2];
        mat[i][3] = completionTime;
        mat[i][4] = mat[i][3] - mat[i][1];
        mat[i][5] = mat[i][4] - mat[i][2];

        totalTurnaroundTime += mat[i][4];
        totalWaitingTime += mat[i][5];
    }

    avgTurnaroundTime = (totalTurnaroundTime) / num;
    avgWaitingTime =(totalWaitingTime) / num;
}

int main() {
    int num, choice, quantum;
    
    cout << "Enter the number of processes: ";
    cin >> num;

    int mat[num][3]; 

    cout << "Enter the Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < num; i++) {
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> mat[i][1];
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> mat[i][2];
        mat[i][0] = i + 1; 
    }
    
    cout << "===== CPU Scheduling Menu =====\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF) - Non-Preemptive\n";
    cout << "3. Shortest Job First (SJF) - Preemptive\n";
    cout << "4. Round Robin (RR)\n";
    cout << "5. Shortest Remaining Time First (SRTF)\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    float avgTurnaroundTime, avgWaitingTime;

    if (choice == 1) {
        fcfs(num, mat);
    } else if (choice == 2) {
        sjf_non_preemptive(num, mat);
    } else if (choice == 3) {
        sjf_preemptive(num, mat);
    } else if (choice == 4) {
        cout << "Enter the time quantum for Round Robin: ";
        cin >> quantum;
        round_robin(num, mat, quantum);
    } else if (choice == 5) {
        srtf(num, mat);
    } else if (choice == 6) {
        cout << "Exiting the program.\n";
        return 0;
    } else {
        cout << "Invalid choice. Please enter a valid option.\n";
        return 0;
    }

    calculate(num, mat, avgTurnaroundTime, avgWaitingTime);
    displayResults(num, mat, avgTurnaroundTime, avgWaitingTime);

    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void calculateCompletionTime(int num, int mat[][3]) {
    int completionTime = mat[0][1] + mat[0][2];
    mat[0][3] = completionTime;

    for (int i = 1; i < num; i++) {
        if (mat[i][1] > completionTime) {
            completionTime = mat[i][1];
        }
        completionTime += mat[i][2];
        mat[i][3] = completionTime;
    }
}

void calculateTurnaroundTime(int num, int mat[][3]) {
    for (int i = 0; i < num; i++) {
        mat[i][4] = mat[i][3] - mat[i][1];
    }
}

void displayResults(int num, int mat[][3], float avgTurnaroundTime, float avgWaitingTime) {
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < num; i++) {
        cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t" << mat[i][2] << "\t\t" << mat[i][3]
             << "\t\t" << mat[i][4] << "\t\t" << mat[i][5] << "\n";
    }
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
}

void fcfs(int num, int mat[][3]) {
    cout << "\n(FCFS) Scheduling\n";
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
    calculateCompletionTime(num, mat);
}

void sjf_non_preemptive(int num, int mat[][3]) {
    cout << "\n(SJF) - Non-Preemptive Scheduling\n";
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][2] > mat[j + 1][2]) {
                for (int k = 0; k < 3; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
    calculateCompletionTime(num, mat);
}

void sjf_preemptive(int num, int mat[][3]) {
    cout << "\n(SJF) - Preemptive Scheduling \n";
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
    calculateCompletionTime(num, mat);
}

void round_robin(int num, int mat[][3], int quantum) {
    cout << "\n(RR) Scheduling\n";
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 3; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
    calculateCompletionTime(num, mat);
}
void srtf(int num, int mat[][3]) {
    cout << "\n(SRTF) Scheduling\n";
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][2] > mat[j + 1][2]) {
                for (int k = 0; k < 3; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
    calculateCompletionTime(num, mat);
}

