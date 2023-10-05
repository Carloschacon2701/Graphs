#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const int INF = 999999;

void dijkstra(map<char, list<pair<char, int> > > &grafo);
void isConexus(int n, map<char, list<pair<char, int> > > &listaAdyacencia);
void DeleteNode(map<char, list<pair<char, int> > > &listaAdyacencia);


#endif
