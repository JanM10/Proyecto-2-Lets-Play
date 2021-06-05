#include "Backtracking.h"

using namespace std;

//int matriz[4][4] = {
//    {0,0,0,0},//0
//    {1,0,1,0},//1
//    {0,1,0,0},//2
//    {1,0,1,0} };//3

int resultado[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1} };

//int resultado[11][21]{
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//};


//Esta funcion imprime la solucion
void imprimirSol(int resultado[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << resultado[i][j] << " ";
        }
        cout << endl;
    }
}

//Esta funcion verifica si un espacio se encuentra dentro o fuera de la matriz
bool espacioValido(int matriz[4][4], int Xini, int Yini, int Xfin, int Yfin)
{
    //Si Xini y Yini no estan dentro de la matriz regresa falso
    if (Xini >= 0 && Xini < 4 && Yini >= 0 && Yini < 4 && //X y Y inicial estan dentro de la matriz
        Xfin >= 0 && Xfin < 4 && Yfin >= 0 && Yfin < 4 && //X y Y final estan dentro de la matriz
        matriz[Xini][Yini] == 0 && matriz[Xfin][Yfin] == 0)//El sapcio dentro de la matriz nom esta bloqueado
    {
        cout << "Si cumple" << endl;
        return true;
    }
    else {
        cout << "No cumple" << endl;
        return false;
    }
}

//La funciona encuentra el camino revursivamente
bool hallarCamino(int matriz[4][4], int Xini, int Yini, int Xfin, int Yfin, int resultado[4][4])
{
    if (Xini == Xfin && Yini == Yfin && matriz[Xini][Yini] == 0)
    {
        resultado[Xini][Yini] = 0;
        imprimirSol(resultado);
        return true;
    }

    //Verifica si matriz[x][y] es un espacio valido
    if (espacioValido(matriz, Xini, Yini, Xfin, Yfin) == true) {
        //Revisa si el bloque actual ya es parte de la solucion
        if (resultado[Xini][Yini] == 0)
            return false;
        //Si no es parte de la solucion se agrega a la lista
        resultado[Xini][Yini] = 0;

        //Se mueve hacia la derecha dentro de la matriz
        if (hallarCamino(matriz, Xini + 1, Yini, Xfin, Yfin, resultado) == true)//Derecha
        {
            cout << "DERECHA" << endl;
            return true;
        }

        //Se mueve hacia abajo dentro de la matriz
        if (hallarCamino(matriz, Xini, Yini + 1, Xfin, Yfin, resultado) == true)//Abajo
        {
            cout << "ABAJO" << endl;
            return true;
        }

        //Se mueve hacia la izquierda dentro de la matriz
        if (hallarCamino(matriz, Xini - 1, Yini, Xfin, Yfin, resultado) == true)//Izquierda
        {
            cout << "IZQUIERDA" << endl;
            return true;
        }

        //Se mueve hacia abajo dentro de la matriz
        if (hallarCamino(matriz, Xini, Yini - 1, Xfin, Yfin, resultado) == true)//Arriba
        {
            cout << "ARRIBA" << endl;
            return true;
        }

        resultado[Xini][Yini] = 1;
        return false;
    }
    return false;
}

//Limpia la ruta del resultado para que se pueda volver a usar
void limpiarMatriz(int resultado[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultado[i][j] = 1;
        }
    }
    imprimirSol(resultado);
}




