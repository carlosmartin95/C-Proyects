/*******************************************
 * FUNDAMENTOS DE PROGRAMACIÓN
 * Facultad de Informática
 * Universidad Complutense de Madrid
 * 
 * Autores: Carlos Martin Gutierrez 51098295-T
			Francisco  Rafael Garcia Rofles
 * Práctica: CORREO 2.0
 *******************************************/

#include <iostream>
#include "gestor.h"
#include <vld.h>

using namespace std;

const string dominio = "fdimail.com";
const string MENSAJE_BV = " Bienvenido al correo de ";

int menuprincipal();
void destruir(tListaCorreos &correos, tListaRegistros &registros);

int main()
{
	tGestor gestor;
	bool entrada, repetir = false, salir = false;
	int opcion;

	cout << MENSAJE_BV << dominio << endl << endl;
	
	/* Arrancamos el gestor: Cargamos de fichero a las listas los datos necesarios.
	 * si devuelve false, significa que no ha encontrado el archivo porque no esta creado
	 * o que ha habido error en la carga. SE SUPONE ARCHIVO NO VACIO.
	 * Para poder gaurdar el proceso sera encesario cerrar sesion. */
	if (!arrancar(gestor, dominio))
	{
		cout << " El archivo no existe, se han creado unos archivos por defecto" << endl << endl;
		// si devuelve false las listas empezaran vacias
		system("PAUSE");
	}
	
	// mientras salir sea false se repetira el proceso
	while (!salir)
	{
		entrada = true;
		
		switch (menuprincipal())
		{
			
		case 0:{
					system("CLS");
					apagar(gestor);// apagamos el gestor, es decir, guardamos todas las listas
					salir = true;
					cout << " Hasta otra! " << endl;
				} break;
		case 1:{
					//repetimos el inicio de sesion hasta que se introduzcan datos validos
					while(!repetir) 
					{   
						// iniciamos sesion
						if (iniciarSesion(gestor)) 
							repetir = true;
					} 
					// repetimos la ejecucion del menuBandeja mientras no cerremos sesion con 0
					while (repetir)
					{
						system("CLS");
						opcion = menuBandeja(gestor, entrada);
						system("CLS");
						ejecutarMenuBandeja(gestor, opcion, entrada);
			
						if (opcion == 0)
							repetir = false;
					}
						
				} break;
		case 2:{
					//repetimos la creacion de usuario hasta que se introduzcan datos validos
					while(!repetir)
					{ 
						system("CLS");
						if (crearCuenta(gestor))
							repetir = true;
					} 
					// repetimos la ejecucion del menuBandeja mientras no cerremos sesion con 0
					while (repetir)
					{
						system("CLS");
						opcion = menuBandeja(gestor, entrada);
						system("CLS");
						ejecutarMenuBandeja(gestor, opcion, entrada);
			
						if (opcion == 0)
							repetir = false;
					}
			   
			   } break;
		}
	}
		
system("PAUSE");
return 0;
}

// menu principal mostrado por pantalla y que devuelve una opcion
int menuprincipal()
{
	int opcion;
	
	cout << " Elija una opcion:" << endl;
	cout << " " << " 1 - Acceder a mi cuenta de correo " << endl;
	cout << " " << " 2 - Crear cuenta de correo " << endl;
	cout << " " << " 0 - Salir" << endl;
	cin >> opcion;

return opcion;
}

void destruir(tListaCorreos &correos, tListaRegistros &registros) 
{
	delete [] correos.lista;
	delete [] registros.lista;
	correos.contador = 0;
}