#ifndef GRAFOESCALERAPALABRAS_GRAPH_CPP
#define GRAFOESCALERAPALABRAS_GRAPH_CPP
#include "Graph.h"
template<class T>
Vertex<T>::Vertex(const T& value) {
    data = value;
    inDegree = 0;
    outDegree = 0;
    connectedTo = {};
    predecessor = 0;
    distance = 0;
    color = 'w';
    principal=false;
}
template<class T>
Vertex<T>::Vertex(const T& value,char sedee) {
    data = value;
    inDegree = 0;
    outDegree = 0;
    connectedTo = {};
    predecessor = 0;
    distance = 0;
    color = 'w';
    sede=sedee;
    principal=false;
}
template<class T>
Vertex<T>::~Vertex() {
}
template<class T>
void Vertex<T>::addNeighbor(Vertex<T> *to, int weight) {
    Edge<T>* temp = new Edge<T>;
    temp->to = to;
    temp->weight = weight;
    outDegree++;
    to->inDegree++;
    connectedTo.push_back(temp);
}
template<class T>
int Vertex<T>::getWeight(const T &value) {
    for(int i=0; i < connectedTo.size(); i++){
        Edge<T>* temp = connectedTo.get(i);
        if(temp->to->data == value){
            return connectedTo.get(i)->weight;
        }
    }
    return NULL;
}
template<class T>
Graph<T>::Graph() {
    count = 0;
    vertexList = {};
    boquemonte=false;
    antonio= false;
    barcelona= false;
}
template<class T>
Graph<T>::~Graph() {
}
template<class T>
Vertex<T>* Graph<T>::addVertex(const T &value,char sede) {
    Vertex<T>* newVertex = new Vertex<T>(value,sede);
    vertexList.push_back(newVertex);
    count++;
    if (newVertex->sede=='A'&& antonio== false){
        newVertex->principal=true;
        antonio=true;
    }
    if (newVertex->sede=='B'&& barcelona== false){
        newVertex->principal=true;
        barcelona=true;
    }
    if (newVertex->sede=='C'&& boquemonte== false){
        newVertex->principal=true;
        boquemonte=true;
    }
    return newVertex;
}
template<class T>
Vertex<T>* Graph<T>::addVertex(const T &value) {
    Vertex<T>* newVertex = new Vertex<T>(value,'0');
    vertexList.push_back(newVertex);
    count++;
    return newVertex;
}
template<class T>
void Graph<T>::addEdge(const T& from, const T& to, int weight) {
    Vertex<T>* fromVertex = getVertex(from);
    if(!fromVertex){
        fromVertex = addVertex(from);
    }
    Vertex<T>* toVertex = getVertex(to);
    if(!toVertex){
        toVertex = addVertex(to);
    }
    fromVertex->addNeighbor(toVertex, weight);
}
template<class T>
Vertex<T> *Graph<T>::getVertex(const T &value) {
    for(int i=0; i < vertexList.size();i++ ){
        if(vertexList[i]->data == value) return vertexList[i];
    }
    return NULL;
}

template<class T>
void Graph<T>::deleteVertex(int position) {
    if (position < 0 || position >= vertexList.size()) {
        cout << "Posición de vértice inválida." << endl;
        return;
    }

    Vertex<T>* vertexToDelete = vertexList[position];

    // Eliminar las conexiones del vértice a borrar
    for (int i = 0; i < vertexList.size(); i++) {
        Vertex<T>* vertex = vertexList[i];
        for (int j = 0; j < vertex->connectedTo.size(); j++) {
            Edge<T>* edge = vertex->connectedTo[j];
            if (edge->to == vertexToDelete) {
                vertex->connectedTo.erase(vertex->connectedTo.begin() + j);
                vertex->outDegree--;
                vertexToDelete->inDegree--;
                break;
            }
        }
    }

    // Eliminar el vértice de la lista de vértices
    vertexList.erase(vertexList.begin() + position);

    delete vertexToDelete;
    count--;
}
#endif //GRAFOESCALERAPALABRAS_GRAPH_CPP