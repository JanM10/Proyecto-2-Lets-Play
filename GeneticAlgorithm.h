#pragma once
#include <string>
#include <iostream>

//Numero de individuos de cada generacion
#define NUM_POBLACION 100
using namespace std;

class GeneticAlgorithm
{
public:
	const string genes = "";
	const string objetivo = "";
	string crear_genoma();
	string cromosoma;

	int numero_aleatorio(int start, int end);
	int masApto;
	int mas_Apto();

	char genes_mutados();

	GeneticAlgorithm(string cromosoma);
	GeneticAlgorithm companero(GeneticAlgorithm padre2);
};


