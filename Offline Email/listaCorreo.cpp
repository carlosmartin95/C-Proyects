#include "listaCorreo.h"

using namespace std;

void resetArray (tListaCorreos &correos, int nuevaCapacidad)
{
	correos.contador = 0;
	correos.capacidad = nuevaCapacidad;
	correos.lista = new tCorreo[nuevaCapacidad];
}

void inicializar(tListaCorreos &correos)
{
	resetArray(correos, TAM_DEFECTO_CORREOS);
}
	
bool buscar(const tListaCorreos &correos, string id, int &pos)
{
	int ini = 0, fin = correos.contador-1, mitad;
	bool encontrado = false;
	
	while ((ini <= fin) && !encontrado) 
	{
		mitad = (ini + fin) / 2;
		
		if (id == correos.lista[mitad].unico)
			encontrado = true;
		
		else if (id < correos.lista[mitad].unico)
				fin = mitad-1;
			else ini = mitad + 1;
	}
	
	if (!encontrado)
		pos= ini;
	else pos = mitad; 
	
return encontrado;
}	

void insertar(tListaCorreos &correos, const tCorreo &correo)
{
	int nuevaCapacidad, pos;
	
	// si no hay hueco en la lista se añade
	if (correos.contador == correos.capacidad)
	{
		//Redimensionamos el array con la nueva capacidad calculada con siguienteDecena()
		nuevaCapacidad =  (correos.capacidad* 3) / 2 + 1;
		redimensionar(correos, nuevaCapacidad);
	}
	
	buscar(correos, correo.unico, pos);
	for(int j = correos.contador; j > pos; j--)
	{
		correos.lista[j] = correos.lista[j - 1];
	}

	correos.lista[pos] = correo;
	correos.contador++;
}

bool cargar(tListaCorreos &correos, string dominio)
{
	int numero, i=0, capacidad;
	bool ok = false;
	ifstream archivo;
	string listacorreos;
	tCorreo correo;
	
	listacorreos = dominio + "_correos.txt";
	archivo.open(listacorreos);
		
	if (archivo.is_open())
	{	
		ok = true;
		archivo >> numero;
	
		if (numero > 0)
		{	
			if ( numero < TAM_DEFECTO_CORREOS)
				inicializar(correos);
			
			else
			{
				capacidad = siguienteDecena(numero);
				resetArray(correos, capacidad);
			}
			
			do
			{
				cargar(correos.lista[correos.contador], archivo);
				insertar(correos, correos.lista[correos.contador]);
				i++;

			} while ( i < numero);
		}		
	
		archivo.close();
	}
	else inicializar(correos);

return ok;
}
	
void guardar(const tListaCorreos &correos, string dominio)
{
	ofstream archivo;
	string listacorreos;
	tCorreo cargando;

	listacorreos = dominio + "_correos.txt";

	archivo.open(listacorreos);

	if (archivo.is_open())
	{
		if (correos.contador != 0)
		{	
			archivo << correos.contador << endl;
			for (int i = 0; i < correos.contador; i++)
			{
				guardar(correos.lista[i], archivo);
			}
		}
		archivo.close();
	}
}

bool operator>(tCorreo opIzq, tCorreo opDer) 
{
	bool mismoAsunto = false;
	string asuntoIzq, asuntoDer;

	asuntoIzq = opIzq.asunto;
	asuntoDer = opDer.asunto;
	despejarAsunto(asuntoIzq);
	despejarAsunto(asuntoDer);

	if (asuntoIzq == asuntoDer)
		if (opIzq.fecha > opDer.fecha)
			mismoAsunto = true;
	else if (asuntoIzq  > asuntoDer)
			mismoAsunto = true;
			
return mismoAsunto;
}

void ordenar_AF(tListaCorreos &correos)
{
	tCorreo nuevo;
		
	for (int i = 1; i < correos.contador; i++) 
	{		
		if (correos.lista[i-1] > correos.lista[i])
		{
			nuevo = correos.lista[i];
			correos.lista[i] = correos.lista[i-1];
			correos.lista[i-1]= nuevo;
		}
	}	
}

void despejarAsunto(string &asunto)
{
	while ( "Re: " == asunto.substr(0,4) )
	{
		asunto.erase(0,4);
	}
}

int siguienteDecena(int capacidad)
{ 
	return ((capacidad + 10) - (capacidad % 10));
}

void destruir(tListaCorreos &correos)
{
	delete[] correos.lista;
	correos.lista = NULL;	
}

void redimensionar(tListaCorreos &correos, int nuevaCapacidad)
{
	tArrayDinamicoCorr arrayAux = new tCorreo[nuevaCapacidad];

	for (int i = 0; i < correos.contador; i++)
		arrayAux[i] = correos.lista[i];
	
	destruir(correos);
	correos.lista = arrayAux;
	correos.capacidad = nuevaCapacidad;
}