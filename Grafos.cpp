#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const int INF = 999999;


void dijkstra(map<char, list<pair<char, int> > > &grafo) {
	char origen;
    map<char, int> distancia;
    map<char, bool> visitado;
    
    cout << "Ingrese el v?rtice de origen para Dijkstra: ";
    cin >> origen;

    for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        distancia[it->first] = INF;
        visitado[it->first] = false;
    }

    distancia[origen] = 0;

    for (int i = 0; i < grafo.size(); i++) {
        char u = ' '; 

        for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
            if (!visitado[it->first] && (u == ' ' || distancia[it->first] < distancia[u])) {
                u = it->first;
            }
        }

        visitado[u] = true;

        for (list<pair<char, int> >::iterator lit = grafo[u].begin(); lit != grafo[u].end(); ++lit) {
            char v = lit->first;
            int peso = lit->second;

            if (distancia[u] != INF && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
            }
        }
    }

    cout << "Distancias M?nimas desde " << origen << " usando Dijkstra:" << endl;
    for (map<char, int>::iterator it = distancia.begin(); it != distancia.end(); ++it) {
        cout << "Distancia a " << it->first << ": " << it->second << endl;
    }
}

void DeleteNode()


int main() {
    ifstream archivo("arista.txt");

    int n;
    archivo >> n;
    archivo.ignore();

    map<char, list<pair<char, int> > > listaAdyacencia;

    char origen, destino, flecha1, flecha2;
    int peso;

    while (archivo >> origen >> flecha1 >> flecha2 >> destino >> peso) {
        listaAdyacencia[origen].push_back(make_pair(destino, peso));
    }


    archivo.close();
    
    
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

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrizAdyacencia[i][k] + matrizAdyacencia[k][j] < matrizAdyacencia[i][j]) {
                    matrizAdyacencia[i][j] = matrizAdyacencia[i][k] + matrizAdyacencia[k][j];
                }
            }
        }
    }

    bool esFuertementeConexo = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrizAdyacencia[i][j] == INF) {
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
    


    dijkstra(listaAdyacencia);


    char nodoAEliminar;
    cout << "Ingrese la letra del nodo que desea eliminar: ";
    cin >> nodoAEliminar;

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
