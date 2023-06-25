#ifndef GRAFOESCALERAPALABRAS_GRAPH_H
#define GRAFOESCALERAPALABRAS_GRAPH_H
#include <iostream>
#include <vector>
using namespace std;
template<class T>
struct Edge;
template<class T>
class Vertex;
template<class T>
class Edge{
public:
    Vertex<T>* to;
    int weight;
    friend ostream &operator<<(ostream &out, Edge<T>* edge) {
        out << "To: " << edge->to->data;
        out << ", Weight: " << edge->weight << endl;
        return out;
    }
};
template<class T>
class Vertex{
public:
    T data;
    int inDegree;
    int outDegree;
    vector<Edge<T>*> connectedTo;
    Vertex<T>* predecessor;
    int distance;
    char color;
    Vertex(const T& value);
    ~Vertex();
    void addNeighbor(Vertex<T>* to, int weight=0);

    int getWeight(const T& value);
    friend ostream &operator<<(ostream &out, Vertex<T>* vertex) {
        out << vertex->data << endl;
        out << "In degree: " << vertex->inDegree << endl;
        out << "out degree: " << vertex->outDegree << endl;
        out << "Edges: " << endl;
        vertex->connectedTo.print();
        return out;
    }
};
template<class T>
class Graph {
public:
    int count;
    vector<Vertex<T>*> vertexList;
    Graph();
    ~Graph();
    void deleteVertex(int position);
    Vertex<T>* addVertex(const T& value);
    Vertex<T>* getVertex(const T& value);
    void addEdge(const T& from, const T& to, int weight=0);
};
#endif