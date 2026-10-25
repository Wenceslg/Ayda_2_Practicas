#include "Vertice.h"
#include "AdyPonderado.h"
#include<vector>
#include<String>
using namespace std;

int Vertice::contador = 0;

Vertice::Vertice(){
    contador++;
    id = contador;
    tDescubrimiento = 0;
    tFinalizacion = 0;
    color = "BLANCO";
    predecesor = nullptr;
    longitudBFS = 0;
    componente = -1;
}

int Vertice::getContador() const{
    return contador;
}

int Vertice::getId() const{
    return id;
}

string Vertice::getColor() const{
   return color;
}

void Vertice::setColor(string color){
   this->color = color;
}

int Vertice::gettDescubrimiento() const{
   return tDescubrimiento;
}

void Vertice::settDescubrimiento(int t){
   tDescubrimiento = t;
}

int Vertice::gettFinalizacion() const{
   return tFinalizacion;
}

void Vertice::settFinalizacion(int t){
   tFinalizacion = t;
}

const vector<Vertice*>& Vertice::getAdyacentes() const {
    return adyacentes;
}

void Vertice::agregarAdyacente(Vertice *v){
    adyacentes.push_back(v);
}

void Vertice::agregarAdyacente(Vertice* v, int costo){
   AdyPonderado* ady = new AdyPonderado(v, costo);
   adyPonderado = ady;
}

void Vertice::agregarArista(Vertice* v){
   adyacentes.push_back(v);
   v->agregarAdyacente(this);
}

void Vertice::agregarArista(Vertice* v, int costo){
   this->agregarAdyacente(v, costo);
   v->agregarAdyacente(this, costo);
}

Vertice* Vertice::getPredecesor() const{
   return predecesor;
}

void Vertice::setPredecesor(Vertice* p){
   predecesor = p;
}

int Vertice::getlongitudBFS() const{
   return longitudBFS;
}

void Vertice::setLongitudBFS(int l){
   longitudBFS = l;
}

int Vertice::getComponente() const{
   return componente;
}

void Vertice::setComponente(int i){
   componente = i;
}
