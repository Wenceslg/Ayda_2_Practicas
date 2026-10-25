#ifndef VERTICE_H
#define VERTICE_H

#include<vector>
#include<String>

class AdyPonderado;

using namespace std;

class Vertice{
private: 
    static int contador;
    int id;
    int tDescubrimiento;
    int tFinalizacion;
    string color;
    vector<Vertice*> adyacentes;
    Vertice* predecesor;
    int longitudBFS;
    AdyPonderado* adyPonderado;
    int componente;

public: 
    Vertice();
    int getContador() const;
    int getId() const;

    string getColor() const;
    void setColor(string color);

    int gettDescubrimiento() const;
    void settDescubrimiento(int t);

    int gettFinalizacion() const;
    void settFinalizacion(int t);

    const vector<Vertice*>& getAdyacentes() const;
    void agregarAdyacente(Vertice *v);
    void agregarAdyacente(Vertice* v, int costo);
    void agregarArista(Vertice* v);
    void agregarArista(Vertice* v, int costo);

    Vertice* getPredecesor() const;
    void setPredecesor(Vertice* p); 
    
    int getlongitudBFS() const;
    void setLongitudBFS(int l);

    int getComponente() const;
    void setComponente(int i);
};

#endif
