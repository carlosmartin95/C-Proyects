#ifndef usuario_h
#define usuario_h

#include "listaRegistros.h"

const string CENTINELA_FINAL = "XXX";

typedef struct {
				string nombre;
				string contrasena;
				tListaRegistros recibidos;
				tListaRegistros enviados;
				} tUsuario;

typedef tUsuario *tUsuPtr;

// cargamos de archivo pasado por parametro datos sobre el usuario
bool cargar(tUsuario &usuario, ifstream& archivo);

// guardamos en el archivo pasado por parametro
void guardar(const tUsuario& usuario, ofstream& archivo);

// inicializamos datos sobre el usuario
void inicializar(tUsuario& usuario, string id, string contrasena);

// comprobamos una contraseña pasada por parametro
bool validarContrasena(const tUsuario &usuario, string contrasena);

// destruye las listas de recibidos y enviados
void destruye (tUsuario usuario);

#endif