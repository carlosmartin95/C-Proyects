#include "listaRegistros.h"

using namespace std;

void resetArray (tListaRegistros &listaReg, int nuevaCapacidad)
{
	listaReg.contador = 0;
	listaReg.capacidad = nuevaCapacidad;
	listaReg.lista = new tRegistro[nuevaCapacidad];
}

void inicializar(tListaRegistros &listaReg)
{
	resetArray(listaReg, TAM_DEFECTO);
}

void guardar(const tListaRegistros &listaReg, ofstream &archivo)
{
	archivo << listaReg.contador << endl;
	
	for (int i = 0; i < listaReg.contador; i++)
	{
		archivo << listaReg.lista[i].unico << " " << listaReg.lista[i].leido << endl;
	}
}

void cargar(tListaRegistros &listaReg, ifstream &archivo)
{
	int numero, capacidad, i=0;
	tRegistro registro;
	
	if (archivo.is_open())
	{	
		archivo >> numero;
	
		if (numero != 0)
		{	
			if ( numero < TAM_DEFECTO)
				inicializar(listaReg);
			else 
			{  
				capacidad = siguienteDecena(numero);
				resetArray(listaReg, capacidad);
			}
			
			do
			{
				archivo >> registro.unico;
				archivo >> registro.leido;
				insertar(listaReg, registro);
				i++;
				
			} while ( i < numero);
		}
		else inicializar(listaReg);
	}
	else inicializar(listaReg);
}

void insertar(tListaRegistros &listaReg, tRegistro registro)
{
	int nuevaCapacidad;
	
	// si no hay hueco en la lista se añade
	if (listaReg.contador == listaReg.capacidad)
	{
		//Redimensionamos el array con la nueva capacidad 
		nuevaCapacidad =  (listaReg.capacidad* 3) / 2 + 1;
		redimensionar(listaReg, nuevaCapacidad);
	}	
	
	listaReg.lista[listaReg.contador] = registro;
	listaReg.contador++;
}

void redimensionar(tListaRegistros &registros, int nuevaCapacidad)
{
	tArrayDinamicoReg arrayAux = new tRegistro[nuevaCapacidad];

	for (int i = 0; i < registros.contador; i++)
		arrayAux[i] = registros.lista[i];
	
	destruir(registros);
	registros.lista = arrayAux;
	registros.capacidad = nuevaCapacidad;
}

bool borrar(tListaRegistros &listaReg, string id)
{
	bool borrado;
	int aux;

	aux = buscar(listaReg, id);

	if ( aux == listaReg.contador)
		borrado = false;
	
	else
	{
		// copiamos desde la posicon que queremos borrar hasta el contador
		for (int i = aux; i < listaReg.contador-1; i++)
		{
			listaReg.lista[i] = listaReg.lista[i+1];
		}
		// restamos el cotador par retrasar una posicion en el array y asi eliminar dicha posicon
		listaReg.contador--; 
	
		borrado = true;
	}
	
return borrado;
}

bool correoLeido(tListaRegistros &listaReg, string id)
{
	bool leido;
	int aux;

	aux = buscar(listaReg, id);

	if (aux == listaReg.contador)
		leido = false;
	else 
	{	
		listaReg.lista[aux].leido = true;
		leido = true;
	}
	
return leido;
}

int buscar(const tListaRegistros &listaReg, string id)
{
	int posicion = 0;
	
	while (posicion < listaReg.contador && id != listaReg.lista[posicion].unico )
	{
		posicion++;
	}
	
	return posicion;
}

void destruir(tListaRegistros &listaReg)
{
	delete[] listaReg.lista;
	listaReg.lista = NULL;
}
