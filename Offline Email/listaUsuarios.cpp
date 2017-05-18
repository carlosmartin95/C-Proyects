#include "listaUsuarios.h"

using namespace std;

void inicializar(tListaUsuarios &usuarios)
{
	usuarios.contador = 0;
}

bool cargar(tListaUsuarios& usuarios, string dominio)
{
	ifstream archivo;
	string nombarch;
	tUsuario usuarioAuxiliar;
	bool cargado = false;

	nombarch = dominio + "_usuarios.txt";
	
	archivo.open(nombarch);
	
	if (archivo.is_open())
	{
		while ( cargar(usuarioAuxiliar, archivo) && usuarios.contador < MAXUSUARIOS)
		{
			aniadir(usuarios, usuarioAuxiliar);
		}
		
		cargado = true;
		archivo.close();
	}
	
	return cargado;
}

void guardar(const tListaUsuarios& usuarios, string dominio)
{
	ofstream archivo;
	string nombarch;
	int i = 0;
	
	nombarch = dominio + "_usuarios.txt";
	
	archivo.open(nombarch);

	if (archivo.is_open())
	{
		while ( usuarios.contador < MAXUSUARIOS && usuarios.contador > i)
		{
			guardar(*(usuarios.lista[i]), archivo);		
			i++;
		}
	
		archivo << CENTINELA_FINAL;
		archivo.close();
	}
}

bool aniadir(tListaUsuarios& usuarios, tUsuario usuario)
{
	bool aniadir = false;
	int pos;
	
	// comprueba que la lista de usuarios no esta llena
	if(usuarios.contador == MAXUSUARIOS)
		aniadir=false;
	// buscamos el nombre la lista de usuarios
	
	else if(!buscarUsuario(usuarios, usuario.nombre, pos))
	{
		// desplazamos a la derecha desde la posicion del contador
		for(int j = usuarios.contador; j > pos; j--)
		{
			usuarios.lista[j] = usuarios.lista[j - 1];
		}
		// metemos en pos la posicion devuelta por la busqueda binaria
		usuarios.lista[pos] = new tUsuario(usuario); 
		usuarios.contador++;
		aniadir = true;
	}

 return aniadir;
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion)
{
	int ini = 0, fin = usuarios.contador-1, mitad;
	bool encontrado = false;
	
	while (( fin >= 0 && ini <= fin) && !encontrado) 
	{
		mitad = (ini + fin) / 2;
		
		if (id == usuarios.lista[mitad]->nombre)
			encontrado = true;
		
		else if (id < usuarios.lista[mitad]->nombre) 
				fin = mitad-1;
			else ini = mitad + 1;
	}
	
	if (!encontrado)
		posicion = ini;
	else posicion = mitad;

	return encontrado;
}

void destruir(tListaUsuarios &listaUsuarios)
{
	for (int i = 0; i < listaUsuarios.contador; i++)
	{
		//Destruir las listas de registros del usuario
		destruye(*(listaUsuarios.lista[i]));
		//Destruir usuario 
		delete listaUsuarios.lista[i];
	}
	listaUsuarios.contador = 0;
}