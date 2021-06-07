#include "Backtracking.h"

using namespace std;

//Esta funcion imprime la solucion
void Backtracking::imprimirSol(int resultado[11][21])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			cout << resultado[i][j] << " ";
		}
		cout << endl;
	}
}

//Esta funcion verifica si un espacio se encuentra dentro o fuera de la matriz
bool Backtracking::espacioValido(int matriz[11][21], int Xini, int Yini, int Xfin, int Yfin)
{
	//Si Xini y Yini no estan dentro de la matriz regresa falso
	if (Xini >= 0 && Xini < 11 && Yini >= 0 && Yini < 21 && //X y Y inicial estan dentro de la matriz
		Xfin >= 0 && Xfin < 11 && Yfin >= 0 && Yfin < 21 && //X y Y final estan dentro de la matriz
		matriz[Xini][Yini] == 0 && matriz[Xfin][Yfin] == 0)//El sapcio dentro de la matriz nom esta bloqueado
	{
		//cout << "Si cumple" << endl;
		return true;
	}
	else {
		//cout << "No cumple" << endl;
		return false;
	}
}

//La funciona encuentra el camino revursivamente
bool Backtracking::hallarCamino(int matriz[11][21], int Xini, int Yini, int Xfin, int Yfin, int resultado[11][21])
{
    if (Xini == Xfin && Yini == Yfin && matriz[Xini][Yini] == 0)
    {
        resultado[Xini][Yini] = 0;
        return true;
    }

    //Verifica si matriz[x][y] es un espacio valido
    if (espacioValido(matriz, Xini, Yini, Xfin, Yfin) == true) {
        //Revisa si el bloque actual ya es parte de la solucion
        if (resultado[Xini][Yini] == 0)
            return false;
        //Si no es parte de la solucion se agrega a la lista
        resultado[Xini][Yini] = 0;

        //Se mueve hacia la izquierda dentro de la matriz
        if (hallarCamino(matriz, Xini - 1, Yini, Xfin, Yfin, resultado) == true)//Izquierda
        {
            return true;
        }

        //Se mueve hacia abajo dentro de la matriz
        if (hallarCamino(matriz, Xini, Yini - 1, Xfin, Yfin, resultado) == true)//Arriba
        {
            return true;
        }

        //Se mueve hacia la derecha dentro de la matriz
        if (hallarCamino(matriz, Xini + 1, Yini, Xfin, Yfin, resultado) == true)//Derecha
        {
            return true;
        }

        //Se mueve hacia abajo dentro de la matriz
        if (hallarCamino(matriz, Xini, Yini + 1, Xfin, Yfin, resultado) == true)//Abajo
        {
            return true;
        }

        resultado[Xini][Yini] = 1;
        return false;
    }
    return false;
}


