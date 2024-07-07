#include <iostream>
#include <algorithm>
#include <list>
#include <cassert>
#include <vector>
using namespace std;

void SquareCounting(int **M, int n, int m)
{
    /**********************************************************/
    /**** Kurzaufgabe 11.2: ****/
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int total_count = 0;
    int max_size = min(n, m);
    vector<int> size_count(max_size + 1, 0);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(M[i][j] == 1) {
                if (i == 0 || j == 0)  dp[i][j] = 1;  
                else  dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                total_count += dp[i][j];
                for(int size = 1; size <= dp[i][j]; ++size)
                    size_count[size]++;
            }
        }
    }

    cout << "Anzahl Untermatrizen: " << total_count << endl;
    for (int size = 1; size <= max_size; ++size)
        cout << "Anzahl " << size << "-Untermatrizen: " << size_count[size] << endl;
    
    for(int j = 0; j < m; j++)
        cout << "__" << (j < m-1 ? "" : "___\n");
    for(int i = 0; i < n; i++){
        cout << "| ";
        for(int j = 0; j < m; j++)
            cout << dp[i][j] << (j < m-1 ? " " : " |\n");
    }
    for(int j = 0; j < m; j++)
        cout << "‾‾" << (j < m-1 ? "" : "‾‾‾\n");
    /**********************************************************/
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    int **M = new int *[n];

    for (int i = 0; i < n; i++)
    {
        M[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            std::cin >> M[i][j];
        }
    }

    SquareCounting(M, n, m);

    for (int i = 0; i < n; i++)
    {
        delete[] M[i];
    }
    delete[] M;
    return 0;
}
