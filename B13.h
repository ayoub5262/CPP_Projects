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
    int **weights;
    
public:
    Graph(int n)
    {
        this->n = n;
        this->m = 0;
        weights = new int*[n];

        for (int i = 0; i < n; i++)
        {
            weights[i] = new int[n];
            for (int j = 0; j < n; j++) {
                weights[i][j] = INT_MAX;
            }

            weights[i][i] = 0;
        }
    }

    ~Graph()
    {
        for (int i = 0; i < n; i++)
        {
            delete weights[i];
        }
        delete[] weights;
    }

    int getN() const {
        return n;
    }


    int getWeight(int src, int dst) const
    {
        return weights[src][dst];
    }

    void addEdge(int src, int dst, int weight)
    {
        m++;
        weights[src][dst] = weight;
        weights[dst][src] = weight;
    }
    
    void addDirEdge(int src, int dst, int weight)
    {
        m++;
        weights[src][dst] = weight;
    }

    void print() const
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << i << ": ";

            for (int j = 0; j < n; j++)
            {
                int weight = getWeight(i, j);
                if (weight > 0) {
                    std::cout << j << " (" << weight << ") ";
                }
            }

            std::cout << std::endl;
        }
    }
};