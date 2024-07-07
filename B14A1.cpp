#include "B14.h"

bool bfs(Graph *graph, int s, int t, int n, std::list<int> *path)
{
    /**********************************************************/
    /**** Langaufgabe 14.1: ****/

    // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

    /**********************************************************/

    return false;
}

int edmond_karp(Graph *graph, int s, int t, int n)
{
    int flow = 0;

    /**********************************************************/
    /**** Langaufgabe 14.1: ****/

    // Ersetzen Sie diese Kommentarzeile durch Ihren Code!

    /**********************************************************/

    return flow;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    Graph graph = Graph(n);

    for (int i = 0; i < m; i++)
    {
        int s, t, c;
        std::cin >> s >> t >> c;
        graph.addEdge(s, t, c);
    }

    std::string command;
    while (true)
    {
        std::cout << "Enter command (f to caluclate flow, q to quit): ";
        std::cin >> command;

        if (command == "f")
        {
            int s, t;
            std::cin >> s >> t;

            std::cout << "max flow: " << edmond_karp(&graph, s, t, n) << std::endl;
        }
        else if (command == "q")
        {
            break;
        }
        else
        {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}