#include "usuario.h"

using namespace std;

bool cargar(tUsuario &usuario, ifstream& archivo)
{
	bool cargado = false;
	string aux;

	archivo >> aux;

	if ( aux != CENTINELA_FINAL)
	{
		usuario.nombre = aux; // nombre de usuario
		archivo >> usuario.contrasena; // contraseña del usuario
		cargar(usuario.recibidos, archivo); // su lista de correos recibidos
		cargar(usuario.enviados, archivo); // lista de correos enviados

		cargado = true;
	}

	return cargado;
}

void guardar(const tUsuario& usuario, ofstream& archivo)
{
	archivo << usuario.nombre<< endl; // escribimos el nombre de usuario,
	archivo << usuario.contrasena << endl; // la cotraseña,
	guardar(usuario.recibidos, archivo); //  la lista de recibidos,
	guardar(usuario.enviados, archivo); // y la lista de enviados
}

void inicializar(tUsuario& usuario, string id, string contrasena)
{
	usuario.nombre = id; // su id 
	usuario.contrasena = contrasena; // su contraseña
	inicializar(usuario.enviados); // su lista de enviados
	inicializar(usuario.recibidos); // y la de recibidos
}

bool validarContrasena(const tUsuario &usuario, string contrasena)
{
	return ( usuario.contrasena == contrasena);
}

void destruye(tUsuario usuario)
{
	destruir(usuario.enviados);
	destruir(usuario.recibidos);
}