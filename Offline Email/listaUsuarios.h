#ifndef listaUsuarios_h
#define listaUsuarios_h

#include "usuario.h"

const int MAXUSUARIOS = 50;

typedef tUsuPtr tArrayUsu[MAXUSUARIOS];

typedef struct {
				 tArrayUsu lista;
				 int contador;
				 } tListaUsuarios;

// inicializamos el contador de la lista de usuarios
void inicializar(tListaUsuarios &usuarios);

// cargamos del archivo indicado por el dominio la lista de usuarios
bool cargar(tListaUsuarios& usuarios, string dominio);

// guardamos en el archivo indicado por el dominio la lista de usuarios
void guardar(const tListaUsuarios& usuarios, string dominio);

// añadimos un usuario en la lista de usuarios
bool aniadir(tListaUsuarios& usuarios, tUsuario usuario);

/* A traves de una busqueda binaria, devuelve true si se ha 
 * encontrado ademas de la posicion en la que se encuentra;
 * sino devuelve false y la posicion en la que deberia estar */
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion);

// destruimos el array
void destruir(tListaUsuarios &usuarios);

#endif