#pragma once
#include <stdio.h>
#include <iostream>

class Backtracking
{
public:

	void imprimirSol(int resultado[4][4]);

	bool espacioValido(int matriz[4][4], int Xini, int Yini, int Xfin, int Yfin);

	bool hallarCamino(int matriz[4][4], int Xini, int Yini, int Xfin, int Yfin, int resultado[4][4]);

	void limpiarMatriz(int resultado[4][4]);
};






