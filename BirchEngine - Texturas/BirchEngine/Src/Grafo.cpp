
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

vector<Nodo> Grafo::algoritmoProfundidad(Nodo nodo_origen, Nodo nodo_destino, Grafo grafoAuxiliar) {
    stack<Nodo> pila;
    vector<Nodo> camino;
    Nodo nodo_actual;
    nodo_origen.setVisitado(true);
    
    pila.push(nodo_origen);
    
    camino.push_back(nodo_origen);

    while (!pila.empty()) {
        nodo_actual = pila.top();
        nodo_actual.setVisitado(true);
        pila.pop();

        if (nodo_actual.getValorCasilla() == nodo_destino.getValorCasilla()) {
            return camino;
        }
        Nodo nodo_adyacente;
        for (int i = 0; i < nodo_actual.getAdyacentes().size();i++) {
            nodo_adyacente.copia(this->buscarNodo(nodo_actual.getAdyacentes().at(i).getX(), nodo_actual.getAdyacentes().at(i).getY()));
            if (!nodo_adyacente.isVisitado()) {
                this->buscarNodo(nodo_actual.getAdyacentes().at(i).getX(), nodo_actual.getAdyacentes().at(i).getY()).setVisitado(true);
                nodo_adyacente.setVisitado(true);
                pila.push(nodo_adyacente);
                camino.push_back(nodo_adyacente);
            }
        }
       /* for (Nodo nodo_adyacente : nodo_actual.getAdyacentes()) {
            if (!nodo_adyacente.isVisitado()) {
                nodo_adyacente.setVisitado(true);
                pila.push(nodo_adyacente);
                this->buscarNodo(pila.top().getX(), pila.top().getY()).setVisitado(true);
                camino.push_back(nodo_adyacente);
            }
        }*/
    }

    return vector<Nodo>();
}