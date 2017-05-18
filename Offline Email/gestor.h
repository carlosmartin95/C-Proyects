#ifndef gestor_h
#define gestor_h

#include "listaUsuarios.h"
#include "listaCorreo.h"

const string CORREO_A_LEER = " Que correo quieres leer?: ";
const string CORREO_BORRAR = " Que correo quieres borrar?: ";

typedef struct {
				string dominio;
				tListaUsuarios listaUsuarios; 
				tListaCorreos listaCorreos; // guarda la única copia de los correos que existirá en la aplicación
				int indice;
				} tGestor;

// inicializa el gestor
void inicializar (tGestor &gestor, string dominio);

/* inicializa o carga las lista de usuarios y de correos
 * y devuelve true si se ha hecho correctamente y false si no */
bool arrancar(tGestor& gestor, string dominio);

// guarda todas las listas en el momento actual
void apagar(tGestor &gestor);

/* se pide un usuarios y contraseña, a partir de ahi, 
 * se busca si ese usuario existe, se registra y devuelve true,
 * sino, devuelve false */
bool crearCuenta(tGestor &gestor);

// iniciamos sesion
bool iniciarSesion(tGestor &gestor);

 /* muestra la bandeja de entrada/salida del usuario activo mediante un for
  * que muestra si esta leido, el id del correo, al asunto y la fecha */
int menuBandeja(tGestor &gestor, bool entrada);
 
// mostramos por pantalla la cabecera de la bandeja de entrada/salida
void cabecera(const tGestor &gestor,const tListaRegistros registros, bool entrada);

 /* Dependiendo de la opcinon introducida en el menu mostrado por pantalla,
  * ejecutamos la opcion correspondiente */
void ejecutarMenuBandeja(tGestor &gestor, int opcion, bool &entrada);

/* una vez mostrado un correo por pantalla , mostramos un pequeño menu que
  * da opcion a contestar el correo leido o volver a la bandeja de entrada/salida */
void menuLeerCorreo (tGestor &gestor, const tCorreo &correoOriginal);

 // leemos un correo de la lista de la bandeja de entrada/salida
void leerCorreo(tGestor& gestor, tListaRegistros& registros);

 // enviamos un correo a un destinatario
void enviarCorreo(tGestor& gestor, const tCorreo &correo);

 /* borramos un correo de la lisa de registros del usuario correspondiente,
  * no se borra de la lista de correos */
void borrarCorreo(tGestor& gestor, tListaRegistros& registros);

/*  esta funcion muestra todos los correos sin leer ordenados por asunto
 * y por fecha. Al finalizar, los correos sin leer quedarán marcados como leídos */
void lecturaRapida(tGestor& gestor, tListaRegistros &registros);

 /* pasamos el gestor la entrada y una lista de registros auxiliar que, dependiendo de la entrada,
  * copia los registros de enviados (entrada = true) o de recibidos (entrada = false)*/ 
void traerListaReg(const tGestor& gestor, tListaRegistros &registros, bool entrada);

 /* Funcion que dada una lista auxiliar de registros copia de vuelta a la lista de enviados
  * o recibidos dependiendo de la entrada que le llegue */
void modificarRegGestor(tGestor& gestor,const tListaRegistros &registros, bool entrada);

#endif