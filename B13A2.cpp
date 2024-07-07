#include "B13.h"

using namespace std;

void floyd_warshall(Graph *graph, int n)
{
    /**********************************************************/
    /**** Kurzaufgabe 13.2: ****/
    // Überprüfen, ob der Graph leer ist oder ungültig ist. Wenn ja, beende die Funktion.
    if(n == 0 || graph == nullptr) return;
    // 2D-Vektor zur Speicherung der kürzesten Distanzen zwischen allen Knotenpaaren.
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    // Initialisierung der Distanzmatrix.
    for(int i = 0; i < n; i++){
        dist[i][i] = 0; // Distanz zu sich selbst ist immer 0.
        for(int j = 0; j < n; j++){
            if(i != j && graph->getWeight(i, j) != INT_MAX)
                dist[i][j] = graph->getWeight(i, j); // Initiale Distanzen von direkter Kante zwischen i und j.
        }
    }
    // Hauptschleifen des Floyd-Warshall-Algorithmus.
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                // Überprüfen, ob der Knoten k als Zwischenknoten eine kürzere Route bietet.
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    // Überprüfung auf negative Zyklen.
    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            cout << "Negativen Zyklus entdeckt!" << endl;
            return;
        }
    }
    // Ausgabe der kürzesten Distanzen zwischen allen Knotenpaaren.
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] < INT_MAX) {
                cout << " (" << j << ", " << dist[i][j] << ")";
            }
        }
        cout << endl;
    }
    /**********************************************************/
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    Graph graph = Graph(n);

    for (int i = 0; i < m; i++){
        int s, t, d;
        std::cin >> s >> t >> d;
        graph.addDirEdge(s, t, d);
    }

    floyd_warshall(&graph, n);

    return 0;
}