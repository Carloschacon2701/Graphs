#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const int INF = 999999;




// Función para aplicar el algoritmo de Dijkstra
map<char, int> dijkstra(map<char, list<pair<char, int> > > &grafo, char origen) {
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

    return distancia;
}


int main() {
    // Abrir el archivo "arista.txt"
    ifstream archivo("arista.txt");

    // Leer la cantidad de vértices
    int n;
    archivo >> n;
    archivo.ignore();

    // Crear la lista de adyacencia utilizando un mapa de listas
    map<char, list<pair<char, int> > > listaAdyacencia;

    // Leer las aristas y agregarlas a la lista de adyacencia
    char origen, destino, flecha1, flecha2;
    int peso;

    while (archivo >> origen >> flecha1 >> flecha2 >> destino >> peso) {
        // Agregar la arista a la lista de adyacencia
        listaAdyacencia[origen].push_back(make_pair(destino, peso));
    }

    // Cerrar el archivo
    archivo.close();
    
    

    // Mostrar el grafo original
    cout << "Grafo Original:" << endl;
    for (map<char, list<pair<char, int> > >::iterator it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
        cout << it->first << ": ";
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ++lit) {
            cout << lit->first << "(" << lit->second << ") ";
        }
        cout << endl;
    }
    
    vector<vector<int> > matrizAdyacencia(n, vector<int>(n, INF));

    for (map<char, list<pair<char, int> > >::iterator it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
        char u = it->first;
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ++lit) {
            char v = lit->first;
            int w = lit->second;
            matrizAdyacencia[u - 'A'][v - 'A'] = w;
        }
    }

    // Aplicar el algoritmo de Warshall-Floyd
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrizAdyacencia[i][k] + matrizAdyacencia[k][j] < matrizAdyacencia[i][j]) {
                    matrizAdyacencia[i][j] = matrizAdyacencia[i][k] + matrizAdyacencia[k][j];
                }
            }
        }
    }

    // Verificar si el grafo es fuertemente conexo
    bool esFuertementeConexo = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrizAdyacencia[i][j] == INF) {
                // Si hay algún par de vértices que no están conectados, el grafo no es fuertemente conexo
                esFuertementeConexo = false;
                break;
            }
        }
        if (!esFuertementeConexo) {
            break;
        }
    }

    if (esFuertementeConexo) {
        cout << "El grafo es fuertemente conexo." << endl;
    } else {
        cout << "El grafo no es fuertemente conexo." << endl;
    }
    
        char nodoOrigen;
    cout << "Ingrese el v?rtice de origen para Dijkstra: ";
    cin >> nodoOrigen;

    map<char, int> distanciasDijkstra = dijkstra(listaAdyacencia, nodoOrigen);

    // Mostrar las distancias m?nimas desde el v?rtice de origen usando Dijkstra
    cout << "Distancias M?nimas desde " << nodoOrigen << " usando Dijkstra:" << endl;
    for (map<char, int>::iterator it = distanciasDijkstra.begin(); it != distanciasDijkstra.end(); ++it) {
        cout << "Distancia a " << it->first << ": " << it->second << endl;
    }

    // Eliminar un nodo ingresando la letra por teclado
    char nodoAEliminar;
    cout << "Ingrese la letra del nodo que desea eliminar: ";
    cin >> nodoAEliminar;

    // Eliminar todas las aristas que salen o llegan al nodo a eliminar
    listaAdyacencia.erase(nodoAEliminar);
    for (map<char, list<pair<char, int> > >::iterator it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ) {
            if (lit->first == nodoAEliminar) {
                lit = it->second.erase(lit);
            } else {
                ++lit;
            }
        }
    }

    // Mostrar el grafo después de eliminar el nodo
    cout << "Grafo Después de Eliminar el Nodo " << nodoAEliminar << ":" << endl;
    for (map<char, list<pair<char, int> > >::iterator it = listaAdyacencia.begin(); it != listaAdyacencia.end(); ++it) {
        cout << it->first << ": ";
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ++lit) {
            cout << lit->first << "(" << lit->second << ") ";
        }
        cout << endl;
    }

    return 0;
}
