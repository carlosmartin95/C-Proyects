#include "gestor.h"

using namespace std;

void inicializar (tGestor &gestor, string dominio)
{
	gestor.dominio = dominio;
	inicializar(gestor.listaCorreos);
	inicializar(gestor.listaUsuarios);
	gestor.indice = -1;
}

bool arrancar(tGestor& gestor, string dominio)
{
	bool ok;

	inicializar(gestor, dominio);
	
	if ( cargar(gestor.listaUsuarios, dominio) && cargar(gestor.listaCorreos, dominio)) 
		ok = true;
	else ok = false;

return ok;
}

void apagar(tGestor &gestor)
{
	// guarda la lista de usuarios
	guardar(gestor.listaUsuarios, gestor.dominio);
	// guarda la lista de correos
	guardar(gestor.listaCorreos, gestor.dominio);
	//Destruir lista de correos y lista de usuarios
	destruir(gestor.listaUsuarios);
	destruir(gestor.listaCorreos);
}

bool crearCuenta(tGestor &gestor)
{
	string nombre, contrasena;
	bool correcto;
	int pos;
	tUsuario usuario;
	// se pide un usuarios y contraseña
	cout << "usuario: ";
	cin >> nombre;
	cout << "contrasena: ";
	cin >> contrasena;
	
	nombre = nombre + "@" + gestor.dominio;
	// se busca si el usuario existe
	if (!buscarUsuario(gestor.listaUsuarios, nombre, pos))
	{
		inicializar(usuario, nombre, contrasena);
		// se añade a la lista de usuarios		
		if (aniadir(gestor.listaUsuarios, usuario))
		{	
			buscarUsuario(gestor.listaUsuarios, nombre, pos);
			gestor.indice = pos;
			correcto = true; // devuelve true
		}
	}
	else
	{
		cout << " este nombre de usuario ya existe " << endl; // mensaje de error
		gestor.indice = -1;
		correcto = false; // devuelve false 
	}
	
return correcto;
}

 bool iniciarSesion(tGestor &gestor)
 {
	string nombre, contrasena;
	bool correcto;
	int pos;
	// pedimos un nombre de usuario y su contraseña
	cout << "usuario: ";
	cin >> nombre;
	cout << "contrasena: ";
	cin >> contrasena;

	nombre = nombre + "@" + gestor.dominio;

	/* buscamos en la lista de usuarios si el nombre y la contraseña introducidos
	 * existe y nos devuelve su posicon en la lista */
	if (buscarUsuario(gestor.listaUsuarios, nombre, pos) && validarContrasena(*(gestor.listaUsuarios.lista[pos]), contrasena))
	{
		correcto = true; // devolvemos true
		gestor.indice = pos; // la posicion devuelta por la busqueda binaria es el usuario-activo (usuario actual)
	}
	else 
	{	
		correcto = false;
		gestor.indice = -1; // si la busqueda devuelve false, mensaje de error y usuario-activo = -1
		cout << " Usuario o contrasena no validas " << endl << endl;
	}

return correcto;  
 }

 int menuBandeja(tGestor &gestor, bool entrada)
 {
	int opcion;
	string comando;
	tListaRegistros registros;

	if(entrada)
		comando = "salida";
	else comando = "entrada";
		
	// usamos una lista de registros auxiliar
	traerListaReg(gestor, registros, entrada);
	// obtenemos la cabecera
	cabecera(gestor, registros, entrada);
	
	// escribimos el menu de por pantalla y pedimos una opcion
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << " Elija una opcion:" << endl;
	cout << "   " << "1- Leer correo" << endl;
	cout << "   " << "2- Enviar correo" << endl;
	cout << "   " << "3- Borrar correo" << endl;
	cout << "   " << "4- Ver bandeja de " << comando << endl;
	cout << "   " << "5- Lectura rapida de correos sin leer" << endl;
	cout << "   " << "0- Cerrar sesion" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << " Introduzca una opcion: ";
	cin >> opcion;

	// mientras la opcion no este entre 0 y 5 se repite el mensaje
	while (opcion < 0 || opcion > 5)
	{
		cout << " Opcion no valida, Introduzca una opcion: ";
		cin >> opcion;
	}
		
return opcion;
 }
 
 void traerListaReg (const tGestor &gestor, tListaRegistros& registros, bool entrada)
 {
	 if (entrada)
	{
		resetArray(registros, gestor.listaUsuarios.lista[gestor.indice]->recibidos.contador);

		for (int i = 0; i < gestor.listaUsuarios.lista[gestor.indice]->recibidos.contador; i++)
		{
			registros.lista[i] = gestor.listaUsuarios.lista[gestor.indice]->recibidos.lista[i];
			registros.contador++;
		}
					
					
	 }
	else 
	{
		resetArray(registros, gestor.listaUsuarios.lista[gestor.indice]->enviados.contador);
		
		for (int i = 0; i < gestor.listaUsuarios.lista[gestor.indice]->enviados.contador; i++)
		{
			registros.lista[i] = gestor.listaUsuarios.lista[gestor.indice]->enviados.lista[i];
			registros.contador++;
		}
	}
		
 }

 void modificarRegGestor(tGestor& gestor, const tListaRegistros& registros, bool entrada)
 {
	if (entrada)
	{	
		for (int i = 0; i < registros.contador; i++)
		{
			gestor.listaUsuarios.lista[gestor.indice]->recibidos.lista[i] = registros.lista[i];
		}	
	
		gestor.listaUsuarios.lista[gestor.indice]->recibidos.contador = registros.contador;	
	}
	else 
	{
		for (int i = 0; i < registros.contador; i++)
		{
			gestor.listaUsuarios.lista[gestor.indice]->enviados.lista[i] = registros.lista[i];
		}
	
		gestor.listaUsuarios.lista[gestor.indice]->enviados.contador= registros.contador;	
	}
		
 }
 
 void ejecutarMenuBandeja(tGestor &gestor, int opcion, bool &entrada)
 {
	 tCorreo correo;
	 tListaRegistros registros;
	
	 // hacemos uso de la lista de registros auxiliar
	

	 switch (opcion)
	 {
	// Cerramos sesion. Guardamos en archivo los datos que hay en las Listas
	 case 0:{
				 guardar(gestor.listaCorreos, gestor.dominio);
				 guardar(gestor.listaUsuarios, gestor.dominio);
			}	 break;
	 
		 // Leemos un correo de la bandeja de entrada/salida
	 case 1:{
				 traerListaReg(gestor, registros, entrada);
				 leerCorreo(gestor, registros); 
				 modificarRegGestor(gestor, registros, entrada); // devolvemos la lista de registros
			 }   break;
	 case 2:{
				correoNuevo(correo, gestor.listaUsuarios.lista[gestor.indice]->nombre);
				enviarCorreo(gestor, correo); 
			 }  break;
	 // Borramos un correo de la lista de registros tanto del emisor como del receptor
	 case 3:{
				 traerListaReg(gestor, registros, entrada);	 
				 borrarCorreo(gestor, registros);
				 modificarRegGestor(gestor, registros, entrada); // devolvemos la lista de registros
			 }	 break;
	// mostramos la bandeja de entrada/salida dependiendo del parametro de entrada/salida "entrada"
	 case 4: entrada = !entrada; break;
	 case 5:{
				traerListaReg(gestor, registros, entrada);
				lecturaRapida(gestor, registros); 
				modificarRegGestor(gestor, registros, entrada);// devolvemos la lista de registros
				system("PAUSE");// colocamos un system pause para poder visualizar los correos sin leer
			}	break;
	 }
 }

 void leerCorreo(tGestor& gestor, tListaRegistros& registros)
 {
	int numero, pos;
	tCorreo correoOriginal;
	string auxiliar;
	
	// pedimos el correo a leer
	cout << CORREO_A_LEER;
	cin >> numero;
 		
	// invertimos el numero de correo elegido, ya que en la lista esta alreves
	numero = registros.contador - numero;

	if ( numero >= 0 && buscar( gestor.listaCorreos, registros.lista[numero].unico, pos))
	{	
		registros.lista[numero].leido = true;
		// mostramos informacion sobre el correo
		cout << aCadena(gestor.listaCorreos.lista[pos]) << endl;
		correoOriginal = gestor.listaCorreos.lista[pos];
		menuLeerCorreo(gestor, correoOriginal);
	}

	else cout << " No hay mensajes que leer " << endl;

 }

 void menuLeerCorreo (tGestor &gestor, const tCorreo &correoOriginal)
 {
	 int opcion;
	 tCorreo correo;
	 	 
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << setw(2) << "1- Contestar correo" << endl;
	cout << setw(2) << "0 - Volver a la bandeja" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << " Introduzca una opcion:";
	cin >> opcion;
 
	if(opcion==1)
	{
		// nuevo correo de contestacion
		correoContestacion(correoOriginal, correo, gestor.listaUsuarios.lista[gestor.indice]->nombre);
		// enviamos dicho correo
		enviarCorreo(gestor, correo); 
	}
}

 void enviarCorreo (tGestor &gestor, const tCorreo &correo)
 {
	 tRegistro registroUsuario, registroReceptor;
	 int pos;

	 /* si el destinatario del correo a enviar no existe, simplemente se inserta
	 * un registro en la lista de enviados del usuario activo */
	 if (!buscarUsuario(gestor.listaUsuarios, correo.destinatario, pos))
	 {	
		insertar(gestor.listaCorreos, correo);
		registroUsuario.unico = correo.unico;
		registroUsuario.leido = false;
		insertar(gestor.listaUsuarios.lista[gestor.indice]->enviados, registroUsuario);
	 }	  
	 else {
			insertar(gestor.listaCorreos, correo);
			// auxiliar de tipo tRegistro;
			registroUsuario.unico = correo.unico;
			registroUsuario.leido = false;
			// insertamos el nuevo registro en la bandeja de enviados del usuario activo
			insertar(gestor.listaUsuarios.lista[gestor.indice]->enviados, registroUsuario);
			// auxiliar de tipo tRegistro;
			registroReceptor.unico = correo.unico;
			registroReceptor.leido = false;
			//buscamos en que posicion se encuentra el destinatario en la lista de usuarios
			buscarUsuario(gestor.listaUsuarios, correo.destinatario, pos);
			// y lo insertamos en su lista de recibidos
			insertar(gestor.listaUsuarios.lista[pos]->recibidos, registroReceptor);
		}
 }

 void borrarCorreo(tGestor& gestor, tListaRegistros& registros)
 {
	int numero;

	// pedimos el correo a borrar	
	cout << CORREO_BORRAR << endl;
	cin >> numero;
	
	// invertimos el numero de correo elegido, ya que en la lista esta alreves
	numero = registros.contador - numero;
  
	for (int i = numero; i < registros.contador-1; i++)
	{
		registros.lista[i] = registros.lista[i+1];
	}
	// restamos una posicion al contador	
	registros.contador--;
}

void lecturaRapida(tGestor& gestor, tListaRegistros &registros)
{
	tListaCorreos listaAux;
	int pos;

	inicializar(listaAux);
		 
	for (int i = 0; i < registros.contador; i++)
	{
		if (registros.lista[i].leido == false)
		{	
			buscar(gestor.listaCorreos, registros.lista[i].unico, pos);
			insertar(listaAux, gestor.listaCorreos.lista[pos]); // lo insertamos en la lista de correos auxiliar
			correoLeido(registros, registros.lista[i].unico); // marcamos como leido el correo
		}
	}
	
	if (listaAux.contador >= 0)
	{
		// ordenamos por asunto y sino por fecha
		ordenar_AF(listaAux);
		for (int i = 0; i < listaAux.contador; i++)
		{		
			cout << aCadena(listaAux.lista[i]);
			cout << endl << "--------------------------------------------------------------------------------";
		}
	}

	else cout << " No hay mensajes 'SIN LEER' " << endl; 
} 

void cabecera(const tGestor &gestor,const tListaRegistros registros, bool entrada)
{
	string comando, asterisco;
	int contador=1, pos;
	
	if (entrada)
		comando = " entrada";
	else comando = " salida";
	
	cout << "correo de: " << gestor.listaUsuarios.lista[gestor.indice]->nombre << endl
	<< "---------------------------------- Bandeja de" << comando << " --------------------------"
	<< "-------------------------------------------------------------------------------- "
	<< "L  N   EMISOR " << setw(27) << " ASUNTO " << setw(27) << " FECHA " << endl
	<< "--------------------------------------------------------------------------------" << endl;

	// mostramos los correos
	for ( int i = registros.contador-1; i >= 0; i--)
	{			
		if ( !registros.lista[i].leido)		
				asterisco = '*';
		else asterisco = ' ';
		
		// buscamos el correo en la lista de correos
		buscar(gestor.listaCorreos, registros.lista[i].unico, pos);
		cout << asterisco << setw(3) << contador << " - " << setw(33);
		// escribimos la informacion obtenida en la lista de correos en la posicio POS
		cout << obtenerCabecera(gestor.listaCorreos.lista[pos]); 
		contador++; // contador +1
	}
}