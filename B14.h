#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <limits>
#include <queue>
#include <bits/stdc++.h>

class Graph
{
private:
    int n, m;
    int **capacities;
    int **flow;

public:
    Graph(int n)
    {
        /**********************************************************/
        /**** Langaufgabe 14.1: ****/

        // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

        /**********************************************************/
    }

    ~Graph()
    {
        for (int i = 0; i < n; i++)
        {
            delete capacities[i];
            delete flow[i];
        }
        delete[] capacities;
        delete[] flow;
    }

    int getN() const
    {
        return n;
    }

    int getCapacity(int src, int dst) const
    {
        /**********************************************************/
        /**** Langaufgabe 14.1: ****/

        // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

        /**********************************************************/
    }

    int getFlow(int src, int dst) const
    {
        /**********************************************************/
        /**** Langaufgabe 14.1: ****/

        // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

        /**********************************************************/
    }

    void addFlow(int src, int dst, int f)
    {
        /**********************************************************/
        /**** Langaufgabe 14.1: ****/

        // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

        /**********************************************************/
    }

    void addEdge(int src, int dst, int capacity)
    {
        m++;
        /**********************************************************/
        /**** Langaufgabe 14.1: ****/

        // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

        /**********************************************************/
    }

    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << i << ": ";

            for (int j = 0; j < n; j++)
            {
                int capacity = getCapacity(i, j);
                if (capacity > 0)
                {
                    std::cout << j << " (" << capacity << ") ";
                }
            }

            std::cout << std::endl;
        }
    }
};