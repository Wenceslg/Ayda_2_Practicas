#include <iostream>
#include <vector>

using namespace std;

const int N = 8;
const int Ntareas = 10;
const int Mprocesadores = 3;
const int Nrobot = 4;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int salas[][N] = {
        {1,0,1,1,1,0,1,0},
        {1,1,0,1,0,1,0,0},
        {0,1,1,0,1,0,1,1},
        {1,1,1,1,1,1,1,1},
        {0,0,1,1,1,0,0,0},
        {1,1,1,0,0,0,1,1},
        {0,0,1,0,0,0,0,0},
        {1,1,1,1,1,1,1,1}
    };

const int Nsopas = 6;

bool visitado[Nsopas][Nsopas] = {};

vector<vector<char>> sl = {
    {'a', 's', 'o', 'm', 'l', 'm'},
    {'l', 'a', 'l', 't', 'g', 'e'},
    {'e', 'l', 'g', 'i', 't', 'm'},
    {'p', 'r', 'o', 'r', 'i', 'o'},
    {'a', 'l', 'r', 'l', 'r', 's'},
    {'r', 'c', 'i', 'z', 'm', 'a'}
};

struct Posicion{
    int x;
    int y;
};

//  ==========================================
//      EJERCICIO DE LAS N REINAS
//  ==========================================

bool poda(int reinas[], int nroReina){

    for (int i = 1; i < nroReina; i++) {

        // Misma columna
        if (reinas[i] == reinas[nroReina]) {
            return true;
        }

        // Misma diagonal
        if (abs(reinas[i] - reinas[nroReina]) == abs(i - nroReina)) {
            return true;
        }
    }
    return false;
}


void imprimir(int reinas[]) {
    for (int i = 1; i <= N; i++) {
        cout << "Reina " << i << " en columna " << reinas[i] << endl;
    }
}

int backNReinas(int reinas[], int nroReina){
    if(nroReina == N + 1){ // cuando el nuemero de reinas sea igual a la cantidad de columnas que tiene el tablero + 1
                           // esto porque en un tablero de NxN se pueden ubicar N reinas siempre, menos para tableros de 2x2 y 3x3
        imprimir(reinas);
        return nroReina;
    } else {
        int columna = 1;
        int solucion = 0;
        
        while (columna < N + 1 && solucion == 0) { // mientras no se haya ubicado una reina en esa columna
            reinas[nroReina] = columna; // prueba reina en esa columna

            if(!poda(reinas, nroReina)){// poda prueba si se cumplen las condiciones de posicionar una reina en esa columna
                solucion = backNReinas(reinas, nroReina + 1); // como se encontró donde poner una reina, se agrega a la solucion
            }                                                 // manda a el arreglo n en la columna que se probó e intenta 

            columna++;
        }
        return solucion;
    }
}

//  ==========================================
//      EJERCICIO 1 TP BACKTRACKING
//  ==========================================

void imprimirSolucion(vector<Posicion> solucion){
    for(Posicion p : solucion){
        cout << "Camino mas largo: " << p.x << ", " << p.y << endl;
    }
    cout << solucion.size() << " Salas" << endl;
}

bool enRango(int fila, int columna){
    return fila >= 0 && columna >= 0 &&
           fila < N && columna < N &&
           salas[fila][columna] == 1;
}

void backtrackingSalas(Posicion salida, Posicion posicionActual, vector<Posicion> caminoActual, vector<Posicion>& caminoMax){
    if ((posicionActual.x == salida.x) && (posicionActual.y == salida.y)){
        if (caminoActual.size() > caminoMax.size()){
        caminoMax = caminoActual;
        //imprimirSolucion(caminoActual);
        return;
        }
    } else {
        for(int k=0; k < 4; k++){
            int fila = posicionActual.x + dx[k];
            int columna = posicionActual.y + dy[k];
            
            if(enRango(fila, columna)){
                salas[fila][columna] = 0;
                caminoActual.push_back({fila, columna});

                backtrackingSalas(salida, {fila, columna}, caminoActual, caminoMax);
                
                caminoActual.pop_back();
                salas[fila][columna] = 1;
            }
        }
    }
}

//  ==========================================
//      ASIGNACION DE TAREAS A PROCESADORES
//  ==========================================

int calcularMaximo(int p[3]){
    int max=0;
    for(int i=0; i< Mprocesadores; i++){
        if(max < p[i])
            max = p[i];
    }
    return max;
}

void backTrackingTareas(int tareas[10], int procesadores[3],  vector<int>& solucion, int& tMin, int tareasAsignadas){
    if(tareasAsignadas == Ntareas){
        int timepoActual = calcularMaximo(procesadores);
        if(tMin > timepoActual){
            tMin = timepoActual;
            for(int i=0; i < Mprocesadores; i++){
                solucion[i] = procesadores[i];
            }
        }
        return;
    }else{
        for(int p=0; p < Mprocesadores; p++){
            procesadores[p] += tareas[tareasAsignadas];
            if(calcularMaximo(procesadores) < tMin){
                backTrackingTareas(tareas, procesadores, solucion, tMin, tareasAsignadas + 1);
            }
            procesadores[p] -= tareas[tareasAsignadas];
        }
        
    }
}    

//  ==========================================
//      SOPA DE LETRAS
//  ==========================================

void impirmirPalabra(vector<Posicion> s){
    for(Posicion p: s){
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    return;
}

bool enRangoSopa(int x, int y){
    return  x < Nsopas && x >= 0 && 
            y < Nsopas && y >= 0 && 
            !visitado[x][y];

}

bool backSopas(Posicion p, vector<char> palabra, vector<Posicion>& solucion, int indice){
    if(palabra.size() == indice){

        return true;
    } else {
        for(int k=0; k < 4 ; k++){ // 4 movimientos posibles
            int x = p.x + dx[k];
            int y = p.y + dy[k];
            if(enRangoSopa(x, y)){
                if (sl[x][y] == palabra[indice]){
                    visitado[x][y] = true;
                    Posicion actual = {x, y};
                    solucion.push_back(actual);

                    if(backSopas(actual, palabra, solucion, indice + 1)) {
                        return true;
                    }

                    solucion.pop_back();
                    visitado[x][y] = false;
                }
            }
        }
    }
    return false;
}


//  ==========================================
//      PARCIAL 2025
//  ==========================================

bool rangoRobot(Posicion p, vector<vector<int>> matriz){
    return  p.x < Nrobot && p.x >= 0 && 
            p.y < Nrobot && p.y >= 0 && 
            matriz[p.x][p.y] == 1; 
}

bool backRobot(Posicion& inicial, int recursos, vector<vector<int>>& matriz, vector<Posicion> solucion){
    if(recursos == 0){
        imprimirSolucion(solucion);
        return true;
    } else {
        for(int k=0; k< 4; k++){
            int x = inicial.x + dx[k];
            int y = inicial.y + dy[k];
            Posicion actual = {x, y};
            if(rangoRobot(actual, matriz)){
                matriz[x][y] = 0;
                solucion.push_back(actual);
                recursos--;

                if(backRobot(actual, recursos, matriz, solucion))
                    return true;

                matriz[x][y] = 1;
                solucion.pop_back();
                recursos++;
            }
        }
    }
    return false;
}

//  ==========================================
//      MAIN
//  ==========================================

int main(){

/*  //REINAS
    int reinas[N + 1] = {}; // Esto crea un arreglo donde voy a guardar en que columna debe estar ubicada cada reina
                            // se asume que todas deben estar en filas distintas y que el tamaño reprecenta la cantidad
                            // como en un tablero no existe la posicion 0, es un arreglo de 1 a N
    //int i = backNReinas(reinas, 1); 
    Posicion posicionInicial{0,0};
    salas[0][0] = 0;
    vector<Posicion> caminoActual;
    vector<Posicion> caminoMax;
    caminoActual.push_back(posicionInicial);
    backtrackingSalas({7,7}, posicionInicial, caminoActual, caminoMax);
    imprimirSolucion(caminoMax);
*/  
/*  // PROCESADORES
    int tareas[10] = {10, 50, 40, 80, 100, 10, 10, 20, 30, 60};
    int procesadores[3] = {0, 0, 0};  // un procesador por posicion, en cada posicion tenemos el tiempo de completar tareas
    int tMin = 9999;
    vector<int> solucion = {-1, -1, -1};

    backTrackingTareas(tareas, procesadores, solucion, tMin, 0);
    for(int i=0; i < Mprocesadores; i++)
        cout << solucion[i] << ", " << endl;
    cout << tMin;
    */
   
    //SOPA DE LETRAS
/*    vector<char> palabra = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'm', 'o', 's'};
    vector<Posicion> solucion;
    Posicion inicial = {1,1};
    solucion.push_back(inicial);
    visitado[inicial.x][inicial.y] = true;
    backSopas(inicial, palabra, solucion, 1);
            impirmirPalabra(solucion);
 */

    Posicion inicial = {0, 0};
    vector<vector<int>> matriz = {
        {1, 1, 1, 0},
        {1, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };
    vector<Posicion> solucion;
    int recursos = 8;
    solucion.push_back(inicial);
    matriz[inicial.x][inicial.y] = 0;
    recursos --;
    backRobot(inicial, recursos, matriz, solucion);


    return 67;
}
/*Asignación de tareas a procesadores. Se tienen m procesadores idénticos y n tareas con un tiempo
de ejecución dado. Se requiere encontrar una asignación de tareas a procesadores de manera de
minimizar el tiempo de ejecución del total de tareas. */