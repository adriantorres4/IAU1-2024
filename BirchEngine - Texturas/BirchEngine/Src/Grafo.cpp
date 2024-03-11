
using namespace std;
#include "Grafo.h"
#include <stack>
//#include "Nodo.cpp"
//#include "Nodo.h"
Grafo::Grafo() {}

void Grafo::agregarNodo(Nodo nodo) {
    nodos.push_back(nodo);
}

Nodo Grafo::buscarNodo(int x, int y) {
    for (Nodo nodo : nodos) {
        if (nodo.getX() == x && nodo.getY() == y) {
            return nodo;
        }
    }
    return Nodo();
}

vector<Nodo> Grafo::algoritmoProfundidad(Nodo nodo_origen, Nodo nodo_destino) {
    std::stack<Nodo> pila;
    vector<Nodo> camino;

    pila.push(nodo_origen);
    nodo_origen.setVisitado(true);
    camino.push_back(nodo_origen);

    while (!pila.empty()) {
        Nodo nodo_actual = pila.top();
        pila.pop();

        if (nodo_actual.getValorCasilla() == nodo_destino.getValorCasilla()) {
            return camino;
        }

        for (Nodo nodo_adyacente : nodo_actual.getAdyacentes()) {
            if (!nodo_adyacente.isVisitado()) {
                pila.push(nodo_adyacente);
                nodo_adyacente.setVisitado(true);
                camino.push_back(nodo_adyacente);
            }
        }
    }

    return vector<Nodo>();
}