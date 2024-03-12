#include <vector>
using namespace std;
#include <iostream>
class Nodo {
public:
    Nodo(int x, int y, int tipo_casilla, int valor_casilla);
    Nodo();
    int getX() const;
    int getY() const;
    int getTipoCasilla() const;
    int getValorCasilla() const;
    bool isVisitado() const;
    vector<Nodo> getAdyacentes();
    void setVisitado(bool visitado);
    void agregarAdyacente(Nodo nodo);

    // Función miembro para realizar una copia profunda
    Nodo& copia(const Nodo& other) {
        this->x = other.x;
        this->y = other.y;
        this->tipo_casilla = other.tipo_casilla;
        this->valor_casilla = other.valor_casilla;
        this->adyacentes = other.adyacentes;
        this->visitado= other.visitado;

        return *this;
    }

private:
    int x;
    int y;
    int tipo_casilla;
    int valor_casilla;
    bool visitado;
    vector<Nodo> adyacentes;
};