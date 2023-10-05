#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const int INF = 999999;

void dijkstra(map<char, list<pair<char, int> > > &grafo, char origen) {
    map<char, int> distancia;
    map<char, bool> visitado;

    // Inicializar las distancias con INF y los vértices como no visitados
    for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        distancia[it->first] = INF;
        visitado[it->first] = false;
    }

    // La distancia al nodo de inicio es 0
    distancia[origen] = 0;

    // Iterar para encontrar las distancias mínimas
    for (int i = 0; i < grafo.size(); i++) {
        char u = ' '; // Inicializar con un vértice no visitado

        // Encontrar el vértice no visitado con la distancia mínima
        for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
            if (!visitado[it->first] && (u == ' ' || distancia[it->first] < distancia[u])) {
                u = it->first;
            }
        }

        // Marcar el vértice como visitado
        visitado[u] = true;

        // Actualizar las distancias a los vértices adyacentes
        for (list<pair<char, int> >::iterator lit = grafo[u].begin(); lit != grafo[u].end(); ++lit) {
            char v = lit->first;
            int peso = lit->second;

            if (distancia[u] != INF && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
            }
        }
    }

    cout << "Distancias Minimas desde " << nodoOrigen << " usando Dijkstra:" << endl;
    for (map<char, int>::iterator it = distanciasDijkstra.begin(); it != distanciasDijkstra.end(); ++it) {
        cout << "Distancia a " << it->first << ": " << it->second << endl;
    }
}
