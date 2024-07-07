#include "B14.h"

struct Ice
{
    int x, y;
    int n, m;
};

/**********************************************************/
/**** Langaufgabe 14.2: ****/

// Ersetzen Sie diese Kommentarzeile durch Ihren Code!

/**********************************************************/

int main()
{
    int n;
    double D;
    std::cin >> n >> D;

    Ice icefloats[n];

    for (int i = 0; i < n; i++)
    {
        int x, y, ni, mi;
        std::cin >> x >> y >> ni >> mi;

        icefloats[i] = {x, y, ni, mi};
    }

    /**********************************************************/
    /**** Langaufgabe 14.2: ****/

    // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

    /**********************************************************/

    return 0;
}