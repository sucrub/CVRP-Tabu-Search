// TRONG NAY CO RAT NHIEU CHO T KHONG HIEU SAO PHAI DUNG DAU BANG, KHO HIEU CUC M XEM GIAI THICH GIUP T

#include <bits/stdc++.h>
using namespace std;

const int N = 3; // so xe cho hang
vector<int> a[N];

void printSolution()
{
    cout << endl;
    cout << "Route 1: ";
    for (int i = 0; i < a[1].size(); i++)
    {
        cout << a[1][i] << " ";
    }
    cout << endl;
    cout << "Route 2: ";
    for (int i = 0; i < a[2].size(); i++)
    {
        cout << a[2][i] << " ";
    }
    cout << endl;
    cout << "Route 3: ";
    for (int i = 0; i < a[3].size(); i++)
    {
        cout << a[3][i] << " ";
    }
    cout << endl;
}

void relocate(int x) // di chuyen xe x toi moi vi tri co the
{
    // x: so xe se di chuyen
    int route, pos;              // xe day dang o route nao, vi tri nao
    for (int i = 0; i <= N; i++) // DAU BANG MOI XET DUOC ROUTE CUOI
    {
        vector<int>::iterator it;
        it = find(a[i].begin(), a[i].end(), x);
        if (it != a[i].end()) // co thay vi tri x tren route nay
        {
            route = i;
            pos = it - a[i].begin();
            break;
        }
    }
    a[route].erase(a[route].begin() + pos);
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= a[i].size(); j++) // DAU BANG MOI XET DUOC XE CUOI
        {
            if (i == 0 && j == 0)
                continue; // doan nay y, neu ma khong co doan nay thi no se in cai solution mat di gia tri x
            // t khong hieu tai sao lam, m thu xem
            if (i == route && j == pos)
                cout << endl
                     << "skip" << endl;
            else
            {
                a[i].insert(a[i].begin() + j, x);
                printSolution();
                a[i].erase(a[i].begin() + j);
            }
        }
    }
    a[route].insert(a[route].begin() + pos, x);
}

void swap(int x, int y) // swap khach hang x va y cho nhau
{
    int routex, posx, routey, posy;
    for (int i = 0; i <= N; i++)
    {
        vector<int>::iterator it1, it2;
        it1 = find(a[i].begin(), a[i].end(), x);
        it2 = find(a[i].begin(), a[i].end(), y);
        if (it1 != a[i].end())
        {
            routex = i;
            posx = it1 - a[i].begin();
        }
        if (it2 != a[i].end())
        {
            routey = i;
            posy = it2 - a[i].begin();
        }
    }
    a[routex].erase(a[routex].begin() + posx);
    a[routex].insert(a[routex].begin() + posx, y);
    a[routey].erase(a[routey].begin() + posy);
    a[routey].insert(a[routey].begin() + posy, x);
    printSolution();
    a[routex].erase(a[routex].begin() + posx);
    a[routex].insert(a[routex].begin() + posx, x);
    a[routey].erase(a[routey].begin() + posy);
    a[routey].insert(a[routey].begin() + posy, y);
}

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        a[1].push_back(i);
    }
    for (int i = 6; i <= 10; i++)
    {
        a[2].push_back(i);
    }
    for (int i = 11; i <= 14; i++)
    {
        a[3].push_back(i);
    }
    printSolution();
    cout << endl
         << "RELOCATE NEIGHBOR: " << endl;
    relocate(1);
    cout << endl
         << "FIRST SOLUTION: " << endl;
    printSolution();
    cout << endl
         << "SWAP NEIGHBOR: " << endl;
    swap(4, 11);
    cout << endl
         << "FIRST SOLUTION: " << endl;
    printSolution();
}