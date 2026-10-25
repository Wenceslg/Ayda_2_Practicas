#include "AdyPonderado.h"
#include "Vertice.h"

using namespace std;

AdyPonderado::AdyPonderado(Vertice* v, int costo){
    this-> adyacente = v;
    this-> costo = costo;
}

Vertice* AdyPonderado::getAdyacente() const{
    return adyacente;
}

void AdyPonderado::setAdyacente(Vertice* v){
    adyacente = v;
}

int AdyPonderado::getCosto() const{
    return costo;
}

void AdyPonderado::setCosto(int i){
    costo = i;
}
