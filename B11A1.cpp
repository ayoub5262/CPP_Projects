#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int disjoint(int *A, int n)
{
    /**********************************************************/
    /**** Kurzaufgabe 11.1A: ****/
    vector<int> B(n,0);
    B[0] = A[0];
    B[1] = max(A[1], A[0]);

    for(int i = 2; i < n; i++)
        B[i] = max(B[i-1], B[i-2] + A[i]);
    
    return B[n-1];

    /**********************************************************/
}

std::list<int> disjoint3(int *A, int n)
{
    /**********************************************************/
    /**** Kurzaufgabe 11.1B: ****/
    vector<int> B(n,0);
    list<int> C = {};
    B[0] = A[0];
    B[1] = max(A[1], A[0]);
    C.push_back(max(A[1], A[0]));

    for(int i = 2; i < n; i++){
        B[i] = max(B[i-1], B[i-2] + A[i]);
        if(B[i] != B[i-1]) C.push_back(A[i]);
    }
    return C;
    /**********************************************************/
}


int main()
{
    int n, m;
    std::cin >> n;

    int A[n];

    for (int i = 0; i < n; i++)
        std::cin >> A[i];

    std::cout << "Strikt disjunkt: " << disjoint(A, n) <<std::endl;

    
    std::list<int> solution = disjoint3(A, n);
    int sum = 0;
    for (int item : solution) { sum += item; }
    std::cout << "Strikt 3-disjunkt: " << solution.size() << " " << sum << " |";
    
    for (int item : solution)
    {
        std::cout << " " << item;
    }
    std::cout << std::endl;

    return 0;
}
