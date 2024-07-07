#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

class Node;
class Edge;


class Edge
{
private:
    Node *src;
    Node *dst;

public:
    /**********************************************************/
    /**** Langaufgabe 12.1: ****/
    Edge(Node *src, Node *dst) : src(src) , dst(dst) {}

    Node* getSrc() const {return src;}

    Node* getDst() const {return dst;}
    /**********************************************************/
};

class Node
{
private:
    int id;
    std::list<Edge> edges;

public:
    /**********************************************************/
    /**** Langaufgabe 12.1: ****/
    Node(int id) : id(id) {}

    int getId() const {return id;}

    void addEdge(Node *dst) {edges.push_back(Edge(this, dst));}

    const std::list<Edge>& getEdges() const {return edges;}
    /**********************************************************/
};

class Graph
{
private:
    int n, m;
    Node **nodes;

public:
    /**********************************************************/
    /**** Langaufgabe 12.1: ****/
    Graph(int n) : n(n), m(0) {
        nodes = new Node*[n];
        for (int i = 0; i < n; ++i)
            nodes[i] = new Node(i);
    }

    ~Graph() {
        for (int i = 0; i < n; ++i)
            delete nodes[i];
        delete[] nodes;
    }

    Node* getNode(int id) const {
        if (id < 0 || id >= n)
            return nullptr;
        return nodes[id];
    }

    void addEdge(int src, int dst) {
        if (src < 0 || src >= n || dst < 0 || dst >= n)
            return;
        nodes[src]->addEdge(nodes[dst]);
        ++m;
    }

    void print() const {
        for (int i = 0; i < n; ++i) {
            std::cout << nodes[i]->getId() << ":";
            for (const auto& edge : nodes[i]->getEdges()) {
                std::cout << " " << edge.getDst()->getId();
            }
            std::cout << std::endl;
        }
    }

    int getN() const {return n;}

    int getM() const {return m;}

    /**********************************************************/
};