#include <iostream>
#include <vector>
#include "Vertice.h"
#include <queue> 
#include <list>

using namespace std;

int tiempo = 0;

// ============================
// METODOS
// ============================

void DFS(Vertice* origen, list<Vertice*>& lista, int& conexos) {
    tiempo = tiempo + 1;
    origen->settDescubrimiento(tiempo);
    cout << "El vertice " << origen->getId() << "\033[32m" << " Descubireto en TIEMPO: " << tiempo << "\033[0m" << endl;
    origen->setColor("GRIS");
    origen->setComponente(conexos);
    for(Vertice* v : origen->getAdyacentes()){
        if(v->getColor() == "BLANCO"){
            cout << "\033[33m" << "Se ecuentra un arco de ARBOL" << "\033[0m" << endl;
            v->setPredecesor(origen);
            DFS(v, lista, conexos);
        } else if(v->getColor() == "GRIS"){
            cout << "\033[35m" << "Se ecuentra un arco de RETROCESO" << "\033[0m" << endl;
        } else if(v->getColor() == "NEGRO"){
            if(v->gettDescubrimiento() > origen->gettDescubrimiento())
                 cout << "\033[34m" << "Se ecuentra un arco de ADELANTAMIENTO" << "\033[0m" << endl;
            cout << "\033[36m" << "Se ecuentra un arco de CRUCE" << "\033[0m" << endl;
        }

    }
    origen->setColor("NEGRO");
    tiempo = tiempo + 1;
    origen->settFinalizacion(tiempo);
    lista.push_front(origen);
    cout << "El vertice " << origen->getId() << "\033[31m" << " Fianlizado en TIEMPO: " << tiempo << "\033[0m"  << endl;
}

void DFSForest(const vector<Vertice*>& grafo) {
    for(int i=0; i< grafo.size(); i++){
        Vertice* v = grafo[i];
        v->setColor("BLANCO");
        v->setPredecesor(nullptr);
        v->settDescubrimiento(0);
        v->settFinalizacion(0);
    } 
    tiempo = 0;
    int conexos = 0; // pueden ir y volver
    list<Vertice*> lista; // UTILIZADA PARA OREDEN TOPOLOGICO
    for(Vertice* v : grafo){
        if (v->getColor() == "BLANCO")
            conexos++;
            DFS(v, lista, conexos);
    } 
    /*    // IMPRIME ORDEN TOPOLOGICO
    cout << "ORDEN TOPOLOGICO: ";
    for (Vertice* v : lista) {
        cout << v->getId() << "  " ;
    }*/
        // IMPRIME COPONENTES CONEXAS 
    for(Vertice* v : grafo){
        cout << "El vertice " << v->getId() << " pertenece a el conjunto " << v->getComponente() << endl;
    }
}

void BFS(vector<Vertice*> grafo, Vertice* origen) {
    tiempo = 1;
    queue<Vertice*> f;
    f.push(origen);
    //cout << "El vertice " << origen->getId() << "\033[32m" << " Descubireto en TIEMPO: " << tiempo << "\033[0m" << endl;
    while (!f.empty()){
        Vertice* u = f.front();
        for(Vertice* v : u->getAdyacentes()){
            if(v->getColor() == "BLANCO"){
                tiempo++;
                v->setLongitudBFS(u->getlongitudBFS() + 1);
                cout << "Longitud de " << origen->getId() << " a " << v->getId() << " es de: " << v->getlongitudBFS() << endl;
                v->setColor("GRIS");
                v->settDescubrimiento(tiempo);
                //cout << "El vertice " << v->getId() << "\033[32m" << " Descubireto en TIEMPO: " << tiempo << "\033[0m" << endl;
                v->setPredecesor(u);
                f.push(v);
            }
        }
        tiempo++;
        u->setColor("NEGRO");
        u->settDescubrimiento(tiempo);
       // cout << "El vertice " << u->getId() << "\033[31m" << " Fianlizado en TIEMPO: " << tiempo << "\033[0m"  << endl;
        f.pop();
    }
}

void dijkstra(vector<Vertice*> grafo, ){

}

void prim(){

}


// ============================
// MAIN
// ============================

int main() {

    vector<Vertice*> grafo;

    Vertice* a = new Vertice(); // 1 
    Vertice* b = new Vertice(); // 2 
    Vertice* c = new Vertice(); // 3 
    Vertice* d = new Vertice(); // 4
    Vertice* e = new Vertice(); // 5
    Vertice* f = new Vertice(); // 6
    //Vertice* g = new Vertice(); // 7
    //Vertice* h = new Vertice(); // 8
    //Vertice* i = new Vertice(); // 9

/*  // GRAFO DE EJERCICIO 1 - USA HASTA VERTICE f
    a->agregarAdyacente(b);
    a->agregarAdyacente(d);
    b->agregarAdyacente(c);
    b->agregarAdyacente(d);
    c->agregarAdyacente(b);
    d->agregarAdyacente(c);
    d->agregarAdyacente(e);
    d->agregarAdyacente(f);
    e->agregarAdyacente(c);
    f->agregarAdyacente(c);
*/
  /*//GRAGFO EJERCICIO 4 - ORDEN TOPOLOGICO - USA HASTA VERTICE i
    a->agregarAdyacente(d);
    a->agregarAdyacente(g);
    c->agregarAdyacente(e);
    d->agregarAdyacente(b);
    e->agregarAdyacente(a);
    f->agregarAdyacente(i);
    h->agregarAdyacente(a);
*/


    grafo.push_back(a);
    grafo.push_back(b);
    grafo.push_back(c);
    grafo.push_back(d);
    grafo.push_back(e);
    grafo.push_back(f);
    //grafo.push_back(g);
    //grafo.push_back(h);
   //grafo.push_back(i);


    cout << "DFS Grafo 1: " << endl;
    //DFS(a); // para usar solo dfs deben sacarse todos los demas parametros
    cout << endl;


    cout << "DFS Forest Grafo 2: " << endl;
    DFSForest(grafo);
    cout << endl;

    cout << "BFS Grafo 3: " << endl;
    //BFS(grafo, a);
    cout << endl;

    return 0;
};

/*
cout << "\033[31m" << "Texto rojo" << "\033[0m" << endl;
cout << "\033[32m" << "Texto verde" << "\033[0m" << endl;
cout << "\033[33m" << "Texto amarillo" << "\033[0m" << endl;
cout << "\033[34m" << "Texto azul" << "\033[0m" << endl;
cout << "\033[35m" << "Texto magenta" << "\033[0m" << endl;
cout << "\033[36m" << "Texto cian" << "\033[0m" << endl;
*/