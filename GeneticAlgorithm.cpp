#include "GeneticAlgorithm.h"

//Se elige el mas apto entre los demas
int GeneticAlgorithm::mas_Apto()
{
	int len = objetivo.size();
	int fitness = 0;
	for (int i = 0; i < len; i++)
	{
		if (cromosoma[i] != objetivo[i])
			fitness++;
	}
	return fitness;
};

//Crear genes aleatorios para la mutación
char GeneticAlgorithm::genes_mutados()
{
	int len = genes.size();
	int r = numero_aleatorio(0, len - 1);
	return genes[r];
}

//Producir nuevas crías
GeneticAlgorithm GeneticAlgorithm::companero(GeneticAlgorithm padre2)
{
	//Cromosoma para la descendencia
	string cromosoma_hijo = "";

	int len = cromosoma.size();
	for (int i = 0; i < len; i++)
	{
		//Probabilidad aleatoria
		float p = numero_aleatorio(0, 100) / 100;

		//Si la probabilidad es inferior a 0,45, inserte el gen del padre 1
		if (p < 0.45) {
			cromosoma_hijo += cromosoma[i];
		}
			
		//Si la probabilidad está entre 0,45 y 0,90, inserte gen del padre 2
		else if (p < 0.90) {
			cromosoma_hijo += padre2.cromosoma[i];
		}

		//Si no se cumplen los casos anteriores
		else {
			cromosoma_hijo += genes_mutados();
		}
	}

	//Crear un nuevo individuo (descendiente) con cromosoma generado para la descendencia
	return GeneticAlgorithm(cromosoma_hijo);
};

//Función para generar números aleatorios en un rango dado
int GeneticAlgorithm::numero_aleatorio(int start, int end)
{
	int range = (end - start) + 1;
	int random_int = start + (rand() % range);
	return random_int;
}

//El cromosoma actual se convierte en el mas apto
GeneticAlgorithm::GeneticAlgorithm(string cromosoma)
{
	this->cromosoma = cromosoma;
	masApto = mas_Apto();
};

//Crear cromosoma o cadena de genes
string GeneticAlgorithm::crear_genoma()
{
	int len = objetivo.size();
	string gnome = "";
	for (int i = 0; i < len; i++)
		gnome += genes_mutados();
	return gnome;
}


