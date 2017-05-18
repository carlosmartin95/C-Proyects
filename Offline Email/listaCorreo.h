#ifndef listaCorreo_h
#define listaCorreo_h

#include "correo.h"

using std::string;
using std:: ifstream;
using std:: ofstream;

const string ERROR = " Hubo problemas con el archivo ";
const int TAM_DEFECTO_CORREOS = 10;

typedef tCorreo *tArrayDinamicoCorr;

typedef struct {
				tArrayDinamicoCorr lista;
				int contador;
				int capacidad;
			   } tListaCorreos;

// resetea el array con una nueva capacidad pasada por parametro
void resetArray (tListaCorreos &correos, int nuevaCapacidad);

// inicializa el array con el tamaño por defecto
void inicializar(tListaCorreos &correos);

/* busqueda binaria de un id en una lista de correos, devolviendo
 * la posicion en la que esta, y si no esta, en la que deberia estar */
bool buscar(const tListaCorreos &correos, string id, int &pos);

/* Funcion que por medio de un algoritmo de ordenacion por inserccion,
 * introducimos un nuevo elementro en la lista ordenadamente */
void insertar(tListaCorreos &correos, const tCorreo &correo);

/* cargamos del archivo correspondiente (dependiendo del dominio)
 * los correos en la lista de correos */
bool cargar(tListaCorreos &correos, string dominio);

/* abrimos el archivo correspondiente, y guardamos en el
 * los correos de la lista */
void guardar(const tListaCorreos &correos, string dominio);

/* Ordenamos priemero por el asunto del correo, sino,
 * se ordena por fecha */
void ordenar_AF(tListaCorreos &correos);

// funcion operator que compara los parametros pasados
bool operator>(tCorreo opIzq, tCorreo opDer);

// funcion que elimina el posible " Re: " del asunto para poder ser ordenado correctamente
void despejarAsunto(string &asunto);

// funcion que destruye el array
void destruir(tListaCorreos &correos);

// devuelve un int habiendo calculado la capacidad nueva
int siguienteDecena(int capacidad);

// redimensiona el array a la capacidad calculada en siguienteDecena()
void redimensionar(tListaCorreos &correos, int nuevaCapacidad);

#endif