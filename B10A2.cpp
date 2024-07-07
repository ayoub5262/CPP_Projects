#include <iostream>
#include <algorithm>
#include <list>
#include <cassert>

int zooManager(int c[], int f[], int n)
{
    /**********************************************************/
    /**** Langaufgabe 10.2: ****/
    std::sort(c, c + n, std::less<int>());
    std::sort(f, f + n, std::greater<int>());
    int cost = 0;
    for (int i = 0; i < n; i++)
        cost += c[i] * f[i];
    return cost * 1000;
    /**********************************************************/
}

int main()
{
    int n;
    std::cin >> n;
    assert(n > 0);

    int *c = new int[n];
    int *f = new int[n];

    for (int i = 0; i < n; i++)
    {
        std::cin >> c[i];
    }

    for (int i = 0; i < n; i++)
    {
        std::cin >> f[i];
    }

    int cost = zooManager(c, f, n);

    std::cout << "Minimale Kosten: " << cost << " Euro" << std::endl;

    delete[] c;
    delete[] f;
    return 0;
}
