#include <bits/stdc++.h>
using namespace std;

int N;
int **graph;
int *cap;
int numberOfCar;
int capEachCar;

bool checkCondition()
{
    int sumCapCanStorage = numberOfCar * capEachCar;
    int sumCapCustomer = 0;
    for (int i = 0; i < N; i++)
    {
        sumCapCustomer += cap[i];
    }
    if (sumCapCustomer > sumCapCanStorage)
        return false;
    else
        return true;
}

int main()
{
    srand(time(NULL));
    do
    {
        N = rand() % (15 - 6 + 1) + 6;
        numberOfCar = rand() % (6 - 3 + 1) + 3;
        capEachCar = rand() % (40 - 20 + 1) + 20;
        graph = new int *[N];
        for (int i = 0; i < N; i++)
        {
            graph[i] = new int[N];
        }
        cap = new int[N];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {

                if (i == j)
                {
                    graph[i][j] = 0;
                    graph[j][i] = 0;
                }
                if (i > j)
                    continue;
                if (i < j)
                {
                    graph[i][j] = rand() % (20 - 1 + 1) + 1;
                    graph[j][i] = graph[i][j];
                }
            }
        }
        for (int i = 1; i < N; i++)
        {
            cap[i] = rand() % (10 - 3 + 1) + 3;
        }
    } while (checkCondition == false);

    ofstream f;
    f.open("test.txt");
    f << N << endl;
    f << numberOfCar << endl;
    f << capEachCar << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f << graph[i][j] << " ";
        }
        f << endl;
    }
    cap[0] = 0;
    for (int i = 0; i < N; i++)
    {
        f << cap[i] << endl;
    }
}