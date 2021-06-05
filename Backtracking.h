#pragma once
#include <stdio.h>
#include <iostream>

class Backtracking
{
public:

	void imprimirSol(int resultado[11][21]);

	bool espacioValido(int matriz[11][21], int Xini, int Yini, int Xfin, int Yfin);

	bool hallarCamino(int matriz[11][21], int Xini, int Yini, int Xfin, int Yfin, int resultado[11][21]);

};






