#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define MAX 1000
int N;                 // So thanh pho
int **GRAPH;           // Khoang cach giua cac thanh pho
vector<int> *SOLUTION; // Route ketqua la mot array voi moi phan tu la mot vector
int P;                 // So xe cho hang
int C;                 // Trong tai max cua moi xe
int *COST;             // Gia tri cua moi khach hang

void readFile()
{
    ifstream f;
    f.open("test.txt");
    f >> N; // Doc so thanh pho
    f >> P; // Doc so xe cho hang
    f >> C; // Doc trong tai max cua moi xe

    // Khoi tao bo nho
    GRAPH = new int *[N];
    COST = new int[N];
    for (int i = 0; i < N; i++)
    {
        GRAPH[i] = new int[N];
    }

    // Doc khoang cach giua moi thanh pho
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f >> GRAPH[i][j];
        }
    }

    // Doc gia tri cua moi khach hang
    for (int i = 0; i < N; i++)
    {
        f >> COST[i];
    }
    f.close();
}

// Tinh khoang cach di tu solution nay
int fitness(vector<int> *SOL)
{
    int result = 0; // Khoang cach tinh ra
    for (int i = 0; i < P; i++)
    {
        for (int j = 1; j < SOL[i].size(); j++)
        {
            result += GRAPH[SOL[i][j - 1]][SOL[i][j]];
        }
        int k = SOL[i].size() - 1;
        result += GRAPH[SOL[i][k]][0];
    }
    return result;
}

// Kiem tra solution co hop le hay khong bang cach kiem tra no co qua tai khong
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

// Khoi tao solution dau tien
void firstSol()
{
    int check;
    SOLUTION = new vector<int>[P];
    do
    {
        for (int i = 0; i < P; i++)
        {
            SOLUTION[i].push_back(0);
        }
        check = 0;
        for (int i = 1; i < N; i++)
        {
            int route = rand() % (P - 0);
            SOLUTION[route].push_back(i);
        }
        if (checkCondition(SOLUTION) == false)
        {
            check = 1;
            for (int i = 0; i < P; i++)
            {
                SOLUTION[i].clear();
            }
        }
    } while (check == 1);
}

// In solution
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

void testMain(vector<int> *SOLUTION)
{
    vector<int> *bestSOL;
    bestSOL = new vector<int>[P];
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < SOLUTION[i].size(); j++)
        {
            bestSOL[i].push_back(SOLUTION[i][j]);
        }
    }
    // printSolution(bestSOL);

    int bestVALUE = fitness(bestSOL);

    vector<int> *best_candidateSOL;
    best_candidateSOL = new vector<int>[P];
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < SOLUTION[i].size(); j++)
        {
            best_candidateSOL[i].push_back(SOLUTION[i][j]);
        }
    }

    int tabu_list[N];
    memset(tabu_list, N, 0);
    int t = N / 2;
    bool stop = false;
    int stopping_turn = 500;
    int best_keeping = 0;
}

// Main algorithm
void tabuSearch(vector<int> *SOLUTION)
{
    int thunghiem = 1;
    vector<int> *bestSOL;
    bestSOL = new vector<int>[P]; // BEST OF ALL
    // Copy lai nghiem khoi tao vao bestSOL
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < SOLUTION[i].size(); j++)
        {
            bestSOL[i].push_back(SOLUTION[i][j]);
        }
    }
    // printSolution(bestSOL);

    // BEST VALUE (Gia tri tot nhat cua bestSOL)
    int best_val = fitness(bestSOL);

    // vector<int> *candidateSOL;
    // candidateSOL = new vector<int>[P]; // best in finding (chua can den)
    // for (int i = 0; i < P; i++)
    // {
    //     for (int j = 0; j < SOLUTION[i].size(); j++)
    //     {
    //         candidateSOL[i].push_back(SOLUTION[i][j]);
    //     }
    // }

    // Best tu vong lap truoc
    vector<int> *best_candidateSOL;
    best_candidateSOL = new vector<int>[P];
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < SOLUTION[i].size(); j++)
        {
            best_candidateSOL[i].push_back(SOLUTION[i][j]);
        }
    }
    // printSolution(best_candidateSOL);

    int tabu_list[N];
    memset(tabu_list, N, 0);
    int t = N / 2;
    bool stop = false;
    int stopping_turn = 500;
    int best_keeping = 0;

    while (!stop)
    {
        int r1, p1, r2, p2; // route va pos truoc va sau chuyen
        int cmp = INT_MAX;
        // Solution tam thoi dang tim kiem (khi moi di chuyen thanh pho)
        vector<int> *tmpSOL;
        tmpSOL = new vector<int>[P];
        for (int i = 0; i < P; i++)
        {
            for (int j = 0; j < best_candidateSOL[i].size(); j++)
            {
                tmpSOL[i].push_back(best_candidateSOL[i][j]);
            }
        }
        // printSolution(tmpSOL);
        // Duyet tung xe mot
        for (int route = 0; route < P; route++)
        {
            // Duyet tung vi tri trong xe day
            for (int pos = 1; pos < tmpSOL[route].size(); pos++)
            {
                // x la thanh pho duoc chon
                int x = tmpSOL[route][pos];
                // Xoa khoi xe hien tai
                tmpSOL[route].erase(tmpSOL[route].begin() + pos);
                for (int i = 0; i < P; i++)
                {
                    for (int j = 1; j <= tmpSOL[i].size(); j++)
                    {
                        // Bang vi tri ban dau thi skip
                        if (i == route && j == pos)
                            continue;
                        else
                        {
                            // Insert vao xe i vi tri j
                            tmpSOL[i].insert(tmpSOL[i].begin() + j, x);
                            // printSolution(tmpSOL);
                            // cout << endl;
                            // Xe bi qua tai, truong hop khong hop le -> skip
                            if (checkCondition(tmpSOL) == false)
                            {
                                // cout << "False" << endl;
                                tmpSOL[i].erase(tmpSOL[i].begin() + j);
                                continue;
                            }
                            // Kiem tra ket qua co dang tot nhat khong
                            if (fitness(tmpSOL) < cmp)
                            {
                                // cout << "True" << endl;
                                cmp = fitness(tmpSOL);
                                // danh dau diem can chuyen va sau khi chuyen
                                r1 = route;
                                p1 = pos;
                                r2 = i;
                                p2 = j;
                                // cout << r1 << " " << p1 << " " << r2 << " " << p2 << endl;
                            }
                            tmpSOL[i].erase(tmpSOL[i].begin() + j);
                        }
                    }
                }
                tmpSOL[route].insert(tmpSOL[route].begin() + pos, x);
                // printSolution(tmpSOL);
            }
        }

        if (thunghiem == 1)
            printSolution(bestSOL);

        delete[] tmpSOL;

        // Thay doi best_candidateSOL
        int x = best_candidateSOL[r1][p1];
        best_candidateSOL[r1].erase(best_candidateSOL[r1].begin() + p1);
        best_candidateSOL[r2].insert(best_candidateSOL[r2].begin() + p2, x);

        if (thunghiem == 1)
            printSolution(best_candidateSOL);

        thunghiem++;

        // Kiem tra voi cac tot nhat hien tai
        if (fitness(best_candidateSOL) < best_val)
        {
            // Clear bestSOL
            for (int i = 0; i < P; i++)
            {
                bestSOL[i].clear();
            }
            // Change bestSOL
            for (int i = 0; i < P; i++)
            {
                for (int j = 0; j < best_candidateSOL[i].size(); j++)
                {
                    bestSOL[i].push_back(best_candidateSOL[i][j]);
                }
            }
            // Change bestVal
            best_val = fitness(bestSOL);
            best_keeping = -1;
        }

        // cap nhap tabu
        if (tabu_list[x] == 0)
        {
            for (int i = 0; i < N; i++)
                if (tabu_list[i] > 0)
                    tabu_list[i]--;
            tabu_list[x] += t;
        }
        else
        {
            for (int i = 0; i < N; i++)
                tabu_list[i] = 0;
            tabu_list[x] += t;
        }

        // ktra stop condition
        best_keeping++;
        if (best_keeping == stopping_turn)
        {
            stop = true;
            cout << best_val << endl;
            for (int i = 0; i < P; i++)
            {
                for (int j = 0; j < bestSOL[i].size(); j++)
                    cout << bestSOL[i][j] << " ";
                cout << endl;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    readFile();
    SOLUTION = new vector<int>[N];
    firstSol();
    cout << "First initialize solution: " << endl;
    printSolution(SOLUTION);
    cout << endl
         << "SOLUTION: " << fitness(SOLUTION);
    cout << endl;
    tabuSearch(SOLUTION);
    // testMain(SOLUTION);
}
