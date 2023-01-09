#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define MAX 1000
int N;                 // So thanh pho
int **GRAPH;           // Distance between each city
vector<int> *SOLUTION; // Routes solution is an array with each index is a vector
int P;                 // Number of cars to delivery
int C;                 // Capitality on each car
int *COST;             // Cost from each customers

void readFile()
{
    ifstream f;
    f.open("test.txt");
    f >> N; // Read nums of city
    f >> P; // Read nums of delivery cars
    f >> C; // Read capitality of each car

    // Allocate memory
    GRAPH = new int *[N];
    COST = new int[N];
    for (int i = 0; i < N; i++)
    {
        GRAPH[i] = new int[N];
    }

    // Read distance from each cities
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f >> GRAPH[i][j];
        }
    }

    // Read cost from each cities
    for (int i = 0; i < N; i++)
    {
        f >> COST[i];
    }
    f.close();
}

// Caculate the length from this solution
int fitness(vector<int> *SOL)
{
    int result = 0; // Length of the path
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < SOL[i].size(); j++)
        {
            result += GRAPH[i][j];
        }
        result += GRAPH[SOL[i].size() - 1][0];
    }
    return result;
}

// Checking if the solution is valid or not
bool checkCondition(vector<int> *sol)
{
    int value[P] = {0};
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < sol[i].size(); j++)
        {
            value[i] += COST[sol[i][j]];
        }
    }
    for (int i = 0; i < P; i++)
    {
        if (value[i] > C)
            return false;
    }
    return true;
}

// Making first solution
void firstSol()
{
    SOLUTION = new vector<int>[P];
    for (int i = 0; i < P; i++)
    {
        SOLUTION[i].push_back(0);
    }
    do
    {
        for (int i = 1; i < N; i++)
        {
            int route = rand() % (P - 0);
            SOLUTION[route].push_back(i);
        }
        if (checkCondition == false)
        {
            for (int i = 0; i < P; i++)
            {
                SOLUTION[i].clear();
            }
            for (int i = 0; i < P; i++)
            {
                SOLUTION[i].push_back(0);
            }
        }
    } while (checkCondition == false);
}

void printSolution(vector<int> *sol)
{
    int cap[P] = {0};
    for (int i = 0; i < P; i++)
    {
        cout << "Route " << i << ": ";
        for (int j = 0; j < sol[i].size(); j++)
        {
            cap[i] += COST[sol[i][j]];
            cout << sol[i][j] << " ";
        }
        cout << endl;
        cout << "Storage of route " << i << ": ";
        cout << cap[i] << "/" << C;
        cout << endl;
    }
}

// Main algorithm
void tabuSearch()
{
}

int main()
{
    srand(time(NULL));
    readFile();
    SOLUTION = new vector<int>[N];
    tabuSearch();
    firstSol();
    cout << "First initialize solution: " << endl;
    printSolution(SOLUTION);
    cout << endl
         << "SOLUTION: " << fitness(SOLUTION); // dang khong chay duoc ham nay
}