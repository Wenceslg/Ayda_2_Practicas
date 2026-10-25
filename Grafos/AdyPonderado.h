#ifndef ADYPONDERADO_H
#define ADYPONDERADO_H


using namespace std;

class Vertice;

class AdyPonderado{
private:
    Vertice* adyacente;
    int costo;
public:
    AdyPonderado(Vertice* v, int costo);

    Vertice* getAdyacente() const;
    void setAdyacente(Vertice* v);

    int getCosto() const;
    void setCosto(int costo);
};

#endif
