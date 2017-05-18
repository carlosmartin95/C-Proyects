#ifndef listaRegistros_h
#define listaRegistros_h

#include "listaCorreo.h"

const int TAM_DEFECTO = 10;

typedef struct {string unico;
				bool leido;
				} tRegistro;

typedef tRegistro *tArrayDinamicoReg;

typedef struct {tArrayDinamicoReg lista;
				int contador;
				int capacidad;
				} tListaRegistros;

// reseteamos el array 
void resetArray (tListaRegistros &listaReg, int nuevaCapacidad);

// inicializamos el array con el tamaño por defeto
void inicializar(tListaRegistros &listaReg);

// Dado un nuevo registro a insertar, se coloca al final de la lista
void insertar(tListaRegistros &listaReg, tRegistro registro);

// Cargamos de archivo, ya abierto, el id unico y si esta leido o no
void cargar(tListaRegistros &listaReg, ifstream &archivo);

/* guardamos en el archivo corresponiente (dependiente del dominio)
 * una lista de registros */
void guardar(const tListaRegistros &listaReg, ofstream &archivo);

/* Funcion que realiza una busqueda de una posicion
 * dada una lista. Devuelve la posicion si se ha
 *  encontrado, sino, devuelve false */
int buscar(const tListaRegistros &listaReg, string id);

/* dado un identificador, se busca dicho elemento en la
 * lista. Si se encuentra se elimina sin dejar huecos en
 * la lista y devuelve true, si no, devuelve false */
bool borrar(tListaRegistros &listaReg, string id);

/* Dado un identificador a buscar, lo buscamos en la
 * lista de registros. Si es encontrado es que esta leido,
 * por tantoTRUE, sino, no lo esta y devuelve FALSE */
bool correoLeido(tListaRegistros &listaReg, string id);

// destruimos array dinamico
void destruir(tListaRegistros &listaReg);

// redimensionamos el array con la nueva capacidad
void redimensionar(tListaRegistros &registros, int nuevaCapacidad);

#endif