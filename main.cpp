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

// Making first solution
vector<int> *firstSol()
{
}

// Main algorithm
void tabuSearch()
{
}

int main()
{
    readFile();
    SOLUTION = new vector<int>[N];
    tabuSearch();
}