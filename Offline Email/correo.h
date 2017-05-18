#ifndef correo_h
#define correo_h

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

using std:: string;
using std:: ifstream;
using std:: ofstream;

const char CENTINELA_CUERPO = 'X';

typedef time_t tFecha;

typedef struct { 
				 string emisor;
				 string destinatario;
				 string asunto;
				 string cuerpo;
				 string unico;
				 tFecha fecha;
				} tCorreo;

// obtenemos los datos necesarios para un correo nuevo
void correoNuevo (tCorreo &correo, string emisor);

// obtenemos los datos para un correo de contestacion
void correoContestacion (const tCorreo &correoOriginal, tCorreo &correo, string emisor);

// para obtener la fecha y la hora
string mostrarFecha(tFecha fecha);

// para obtener la fecha
string mostrarFechaSoloDia(tFecha fecha);

// para mostrar todos los datos sobre el correo
string aCadena (const tCorreo &correo);

// escribimos por pantalla la cabecera, es decir, la bandeja de entrada/salida
string obtenerCabecera(const tCorreo &correo);

/* cargamos de un archivo ya abierto los datos
 * y si todo va bien, devuelve true, sino false */
void cargar(tCorreo &correo, ifstream& archivo);

/* guardamos en archivo los datos de un correo y si todo va bien
 * devolvemos true, sino false */ 
void guardar(const tCorreo &correo, ofstream& archivo);

#endif