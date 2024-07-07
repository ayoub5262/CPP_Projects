#include <iostream>
#include <algorithm>
#include <list>
#include <cassert>

int Kreuzfahrtschiffes(int x, int g[], int n)
{
    int fahrten = 0;

    /**********************************************************/
    /**** Langaufgabe 10.3: ****/
    std::sort(g, g + n, std::greater<int>());
    int i = 0, j = n - 1;
    while(i <= j){
        if(g[i] + g[j] <= x)
            j--;
        i++;
        fahrten++;
    }
    /**********************************************************/

    return fahrten;
}

int main()
{
    int n, x;
    std::cin >> n >> x;
    assert(n > 0);

    int *g = new int[n];

    for (int i = 0; i < n; i++)
    {
        std::cin >> g[i];
    }

    int fahrten = Kreuzfahrtschiffes(x, g, n);

    std::cout << "Mindestanzahl Fahrten: " << fahrten << std::endl;

    delete[] g;
    return 0;
}
