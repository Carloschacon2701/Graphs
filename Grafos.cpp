#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const int INF = 999999;

//CARLOS DANIEL CHACON MENDEZ
//CEDULA: 30201599

void dijkstra(map<char, list<pair<char, int> > > &grafo) {
	char origen;
    map<char, int> distancia;
    map<char, bool> visitado;
    
    cout << "Ingrese el vertice de origen para Dijkstra: ";
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

    cout << "Distancias Minimas desde " << origen << " usando Dijkstra:" << endl;
    for (map<char, int>::iterator it = distancia.begin(); it != distancia.end(); ++it) {
        cout << "Distancia a " << it->first << ": " << it->second << endl;
    }
}

void DeleteNode(map<char, list<pair<char, int> > > &grafo){
	char nodoAEliminar;
    cout << "Ingrese la letra del nodo que desea eliminar: ";
    cin >> nodoAEliminar;

    grafo.erase(nodoAEliminar);
    for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ) {
            if (lit->first == nodoAEliminar) {
                lit = it->second.erase(lit);
            } else {
                ++lit;
            }
        }
    }

    cout << "Grafo Despues de Eliminar el Nodo " << nodoAEliminar << ":" << endl;
    for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        cout << it->first << ": ";
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ++lit) {
            cout << lit->first << "(" << lit->second << ") ";
        }
        cout << endl;
    }
}

void IsRelated(map<char, list<pair<char, int> > > &grafo, int vertices){
	    vector<vector<int> > matrizAdyacencia(vertices, vector<int>(vertices, INF));

    for (map<char, list<pair<char, int> > >::iterator it = grafo.begin(); it != grafo.end(); ++it) {
        char u = it->first;
        for (list<pair<char, int> >::iterator lit = it->second.begin(); lit != it->second.end(); ++lit) {
            char v = lit->first;
            int w = lit->second;
            matrizAdyacencia[u - 'A'][v - 'A'] = w;
        }
    }

    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (matrizAdyacencia[i][k] + matrizAdyacencia[k][j] < matrizAdyacencia[i][j]) {
                    matrizAdyacencia[i][j] = matrizAdyacencia[i][k] + matrizAdyacencia[k][j];
                }
            }
        }
    }

    bool esFuertementeConexo = true;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
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
}


int main() {
    ifstream archivo("arista.txt");

    int n;
    archivo >> n;
    archivo.ignore();

    map<char, list<pair<char, int> > > listaAdyacencia;

    char origen, destino, flecha1, flecha2;
    int peso, opcion;

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
    

 while(true){
 	    cout<<"\n"<<endl;
	    cout<< "Ingrese Una Opcion"<<endl;
	    cout<< "1. Borrar Nodo"<<endl;
	    cout<< "2. Encontrar rutas minimas"<<endl;
	    cout<< "3. Verificar si el grafo es conexo"<<endl;
	    cout<< "4. Salir"<<endl;
	    cout<<"tu opcion:";
	    cin >> opcion;
	    
	    switch(opcion){
	    	case 1:{
	    		DeleteNode(listaAdyacencia);
				break;
			};
			case 2:{
				dijkstra(listaAdyacencia);
				break;
			};
			case 3:{
				IsRelated(listaAdyacencia, n);
				break;
			}
			case 4:{
				return 0;
				break;
			}
		}
	}
    

    return 0;
}
