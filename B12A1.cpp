#include "B12.h"

int main()
{
    int n, m;
    std::cin >> n >> m;

    Graph graph = Graph(n);

    for (int i = 0; i < m; i++)
    {
        int s, t;
        std::cin >> s >> t;
        graph.addEdge(s, t);
    }

    graph.print();

    return 0;
}