#include "B13.h"

using namespace std;

typedef std::pair<int, int> Pair;

void dijkstra(Graph *graph, int s, int n)
{
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    /**********************************************************/
    /**** Kurzaufgabe 13.1: ****/
    // Überprüfen, ob der Graph leer ist oder ungültig ist. Wenn ja, beenden Sie die Funktion.
    if(n == 0 || graph == nullptr) return;
    // Startknoten mit einer Distanz von 0 in die Prioritätswarteschlange einfügen
    pq.push(make_pair(0, s));
    // Vektor zur Speicherung der minimalen Distanzen von Startknoten zu allen anderen Knoten.
    // Initialisiere alle Distanzen mit INT_MAX (unendlich), außer die Startknoten-Distanz.
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;
    // Hauptschleife: Verarbeitung der Knoten in der Prioritätswarteschlange
    while(!pq.empty()){
        // Extrahieren Sie den Knoten mit der kleinsten Distanz
        int u = pq.top().second;
        pq.pop();   
        // Untersuche alle Nachbarn des aktuellen Knotens
        for(int i = 0; i < n; i++){
            int weight = graph->getWeight(u, i); // Gewicht der Kante zwischen Knoten u und i abrufen
            // Wenn die Kante existiert (Gewicht nicht INT_MAX) und ein kürzerer Pfad gefunden wird
            if(weight != INT_MAX && dist[i] > dist[u] + weight){
                dist[i] = dist[u] + weight; // Aktualisiere die Distanz
                pq.push(make_pair(dist[i], i)); // Füge den Nachbarknoten mit der aktualisierten Distanz in die Warteschlange ein
            }
        }
    }
    // Ausgabe der minimalen Distanzen von Startknoten zu allen anderen Knoten
    for(int i = 0; i < n; i++)
        cout << i << " : " << dist[i] << endl;
    /**********************************************************/
}

int main()
{
    int n, m;
    ifstream inputFile("B13A1.in");
    if (inputFile.is_open()) 
        inputFile >> n >> m;
    else cin >> n >> m;

    Graph graph = Graph(n);

    if (inputFile.is_open()){
    for (int i = 0; i < m; i++){
        int s, t, d;
        inputFile >> s >> t >> d;
        graph.addEdge(s, t, d);
    }
    inputFile.close();

    }else{
        for (int i = 0; i < m; i++){
            int s, t, d;
            cin >> s >> t >> d;
            graph.addEdge(s, t, d);
        }
    }

    cout << "Enter command (s to search, q to quit): ";
    char c;
    while(cin >> c){
        if(c == 'q') break;
        else if(c == 's'){
            int x;
            cin >> x;
            dijkstra(&graph, x, n);
        }
        cout << "Enter command (s to search, q to quit): ";
    }
    return 0;
}