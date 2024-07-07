#include "B12.h"

/**********************************************************/
/**** Langaufgabe 12.2: ****/
enum Mark {
    UNMARKED,
    TEMPORARY,
    PERMANENT
};
/**********************************************************/

bool dfs(std::list<int> *solution, Node *currentNode, Mark *marked)
{
    /**********************************************************/
    /**** Langaufgabe 12.2: ****/
    int id = currentNode->getId();
    if (marked[id] == TEMPORARY)
        // Zyklus entdeckt
        return false;

    if (marked[id] == PERMANENT)
        // Knoten bereits verarbeitet
        return true;

    // Knoten als TEMPORARY markieren
    marked[id] = TEMPORARY;

    // Rekursiv alle erreichbaren Knoten verarbeiten
    for (const auto& edge : currentNode->getEdges()) {
        if (!dfs(solution, edge.getDst(), marked))
            return false;
    }
    // Knoten als PERMANENT markieren und zur Lösung hinzufügen
    marked[id] = PERMANENT;
    solution->push_front(id);

    return true;
    /**********************************************************/
}

std::list<int> topoSort(Graph *g, int n)
{
    std::list<int> solution;
    /**********************************************************/
    /**** Langaufgabe 12.2: ****/
    Mark* marked = new Mark [n];
    for(int i = 0; i < n; i++)
        marked[i] = UNMARKED;

    for (int i = 0; i < n; ++i) {
        if (marked[i] == UNMARKED) {
            if (!dfs(&solution, g->getNode(i), marked))
                // Zyklus entdeckt, leere Liste zurückgeben
                return {};
        }
    }
    /**********************************************************/
    return solution;
}

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

    std::list<int> solution = topoSort(&graph, n);
    if (solution.empty())
    {
        std::cout << "Zyklus entdeckt!" << std::endl;
    }
    else
    {
        std::cout << "Topologische Sortierung:";
        for (int id : solution)
        {
            std::cout << " " << id;
        }
        std::cout << std::endl;
    }

    return 0;
}