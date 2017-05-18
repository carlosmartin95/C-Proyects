/************************************************************
*				PRÁCTICA 2 - EL MAGO
*
* 
* FUNDAMENTOS DE PROGRAMACIÓN
* Facultad de Informática
* Universidad Complutense de Madrid
* 
* Autores: Carlos Martín Gutiérrez Francisco García Rofes		
* Práctica: la baraja
* Fecha de creación: 12/12/2014
* Fecha de última modificación: 25/1/2015
* Contacto: camart12@ucm.es  /  franga06@ucm.es
*
*************************************************************/

// Blibliotecas
#include <iostream>
// entrada y salida de archivos
#include <fstream>
// cadena de caracteres
#include <string>
// acceder a la hora del sistema
#include <ctime>
// gestion de espacios
#include <iomanip>
// biblioteca para "trucos en windows"
#include <Windows.h>
using namespace std;


// Declaracion de constantes int y char
const int CARTASPORPALO = 13;
const int  MAXCARTAS = 53;
const int CENTINELA = 52;
const char CENTINELA_ARCHIVO = 'x';
// Declaracion de constantes tipo string
const string MENSAJE_BIENVENIDA = " Bienvenido a este juego de cartas";
const string MENSAJE_ERROR = " Archivo no encontrado ";
const string NO_CORTAR = " El mazo no se pudo cortar ";
const string NO_GUARDAR = " El mazo no se pudo guardar ";
const string NO_CARGAR = " El mazo no se pudo cargar ";
const string NO_TRUCO = " No se pudo realizar el truco ";
const string MEMORIZAR = " Memorice una carta ";
const string MISMA_CARTA = " Recuerda que la carta debe ser siempre la misma ";
const string INTRODUCIR_ARCH = " Introduzca el nombre del archivo: ";
const string MAZO_VACIO = " El mazo esta vacio ";
const string NO_BARAJAR = " El mazo no se pudo barajar ";
const string CARTA_CORTAR = " Por que carta quieres cortar?: ";
const string INTENTOS = " intentos "; 
const string NO_UNIR = " No se pudo unir ";
const string INTRODUCIR_OPCION = " Porfavor introduzca una opcion: ";
const string MAZO_CARTA = " En que mazo se encuentra la carta?: ";
const string NO_REPARTIR = " El mazo no se pudo repartir ";
const string CUANTOS_MAZOS = " En cuantos mazos quieres repartir?: ";
const string DONDE_GUARDAR = " En que archivo quiere guardar el mazo? ";
const string UNIMOS_MAZOS = " Unimos los mazos... ";
const string REPARTIR_EN = " Repartimos el mazo en ";
const string ALTAS_BAJAS = " Altas y Bajas ";
const string NEGRO_ROJO = " Negras y Rojas ";

// Tipos definidos: Enumerados, int, y array de int
typedef enum { PICAS, TREBOLES, DIAMANTES, CORAZONES} tPalo;
typedef enum { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, OCHO , NUEVE, DIEZ, J, Q, K} tNumero;
typedef int tCarta;
typedef tCarta tMazo[MAXCARTAS];

// Declaracion de todas las funciones usadas
int menu();
int cuantasenMazo(const tMazo mazo);
char devolverLetra(int num);
int devolverCarta(int ltr);
void opcionCargarMazo(tMazo mazo);
void opcionBarajarMazo(tMazo mazo);
void opcionUnirMazos(tMazo mazo);
void opcionCortarMazo(tMazo mazo);
void opcionRepartirNegroRojo(tMazo mazo);
void opcionRepartirAltasBajas(tMazo mazo);
void opcionRepartirIntercalando(tMazo mazo, int enCuantosMazos);
void escribirCarta(tCarta carta);
void escribirMazo(const tMazo mazo);
void barajarMazo(tMazo mazo);
void cortarMazo(tMazo mazo, int cuantas);
void crearMazoVacio(tMazo mazo);
void guardarMazo(const tMazo mazo);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
void trucoTresMontones();
void trucoPosada();
bool mazoVacio(tMazo mazo);
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);
bool cargarMazo(tMazo mazo);
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino);
tPalo darPalo(tCarta carta);
tNumero darNumero(tCarta carta);

/* La primera parte del programa. Primero se declaran variables 
 * que van a ser usadas y a continuacion pasara a un switch que 
 * llamara a la funcion menu que sera la funcion principal del
 * programa
 */

int main()
{
	// Declaracion de 3 variables
	bool salir = false;
	tMazo mazo;
	int enCuantosMazos=0;
	
	// Mensaje de bienvenida
	cout << endl <<  setw(10) << MENSAJE_BIENVENIDA << endl << endl;
	// cargamos un mazo principal vacio
	crearMazoVacio(mazo);

	// Bucle cuando bool salir sea false 
	while ( !salir)
	{
		/* Switch que llama a menu la cual devuelve un int 
		 * que se comparara con los cases del propio switch
		 * y dirige a la funcion indicada pasando el mazo
		 */
		switch (menu())
		{
		case 0: salir= true; break;
		case 1: opcionCargarMazo(mazo); break;
		case 2: opcionBarajarMazo(mazo); break;
		case 3:	opcionUnirMazos(mazo); break;
		case 4: opcionCortarMazo(mazo); break;
		case 5: guardarMazo(mazo); break;
		case 6: opcionRepartirNegroRojo(mazo); break;
		case 7: opcionRepartirAltasBajas(mazo); break;
		case 8: opcionRepartirIntercalando(mazo, enCuantosMazos); break;
		case 9: trucoTresMontones(); break;
		case 10: trucoPosada(); break;
		}
		// Para mantener en pantalla el cmd
		system("PAUSE");
		// Borrar el contenido de la pantalla
		system("CLS");
	}
return 0;
}

// Funcion menu
int menu()
{
	int opcion;
	cout << endl;
	// Conjunto de cout que muestran un menu
	cout << " 1 - Cargar mazo de fichero " << endl;
	cout << " 2 - Barajar mazo " << endl;
	cout << " 3 - Unir mazo " << endl;
	cout << " 4 - Cortar mazo " << endl;
	cout << " 5 - Guardar mazo " << endl;
	cout << " 6 - Repartir Negras y Rojas " << endl;
	cout << " 7 - Repartit Altas y Bajas " << endl;
	cout << " 8 - Repartir mazo " << endl;
	cout << " 9 - Truco de los 3 montones " << endl;
	cout << " 10 - Truco de la posada " << endl;
	cout << " 0 - Salir " << endl << endl;
	
	cout << INTRODUCIR_OPCION;
	// Guarda la opcion elegida
	cin >> opcion;
// Devuelve la opcion elegida
return opcion;
}

void setcolor(unsigned short color)  
{                                                   
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

/* Funcion que devulve el palo 
 * dependiendo de la carta entrante
 */
tPalo darPalo(tCarta carta)
{
	/* Divide la carta entrante entre 13 (CARTASPORPALO)
	 * y dependiendo del resultado entra en una de las 
	 * opciones del switch
	 */
	switch (carta/CARTASPORPALO)
	{
	case 0: return PICAS;break;
	case 1: return TREBOLES;break;
	case 2: return DIAMANTES;break;
	case 3: return CORAZONES;break;
	}
}

/* Funcion que devuelve el enumerado tCarta
 *  dependiendo de la carta entrante
 */ 
tNumero darNumero(tCarta carta)
{
	/* Modulo de la carta entrante y CARTASPORPALO
	 * que  valdra pala obtener la opcion del switch
	 */
	switch (carta%CARTASPORPALO)
	{
	case 0: return AS; break;
	case 1: return DOS; break;
	case 2: return TRES; break;
	case 3: return CUATRO; break;
	case 4: return CINCO; break;
	case 5: return SEIS; break;
	case 6: return SIETE; break;
	case 7: return OCHO; break;
	case 8: return NUEVE; break;
	case 9: return DIEZ; break;
	case 10: return J; break;
	case 11: return Q; break;
	case 12: return K; break;
	}
}

// Funcion que crea un mazo vacio
 void crearMazoVacio(tMazo mazo)
{
 //coloca el CENTINELA en la primera posicion
 mazo[0]=CENTINELA;
}

/* Funcion tipo bool que devulve true 
 * si en la primera posicion esta el CENTINELA
 */
bool mazoVacio(tMazo mazo)
{
 return mazo[0]==CENTINELA;
}

// Funcion tipo int que devulve las cartas que hay en el mazo
int cuantasenMazo(const tMazo mazo)
{
	// int como contadores
	int cuantas=0, i=0;

	/* mientras que el valor del array en i
	 * sea diferente a CENTINELA
	 */
	while ( mazo[i] != CENTINELA)
	{
		// sumamos uno a i y a int cuantas
		cuantas++;
		i++;
	}	
// devolvemos el valor de cuantas
return cuantas;
}

/* Llamada desde el menu, recibe el array mazo
 * y se lo pasa a la funcion cargar, si esta devulve true
 * escribira por pantalla el mazo, sino mensaje error
 */
void opcionCargarMazo(tMazo mazo) 
{
	// LLama a cargarMazo pasandole el array mazo
	if (cargarMazo(mazo)) 
		escribirMazo(mazo);
	// mensaje error, no se pudo cargar
	else cout << endl << NO_CARGAR << endl;
}

// Funcion que carga un mazo de archivo
bool cargarMazo(tMazo mazo)
{
	// Declaracion de diferentes variables		
	ifstream archivo;
	string nomb;
	bool mazocargado = false;
	char palo;
	int num, i=0, j=3;
		
	// Bucle para j diferente de 1 y de 0
	while ( j !=0  && !mazocargado)
	{
		/* Mensaje con el usuario que pide
		 * el nombre del archivo a cargar */
		cout << INTRODUCIR_ARCH;
		// guarda en un string nomb el nombre introducido
		cin >> nomb;
		// añade ".txt" al nombre del archivo para poder reconocerlo
		nomb = nomb +".txt";

		// Abrirmos el archivo
		archivo.open(nomb);
		// Si el arhivo esta abierto...
		if (archivo.is_open())
		{
			/* Leemos la primera linea del archivo y 
			 * guardamos en char palo la letra y en
			 * int num el numero
			 */
			archivo >> palo >> num;
			// Bucle para palo diferente a x (CENTINELA_ARCHIVO)
			while ( palo != CENTINELA_ARCHIVO) 
			{	
				// Si palo es 'p'
				if (palo =='p')
					// Guarda en la posicion i del mazo el numero - 1
					mazo[i]=num-1;
				// Si palo es 't'
				else if (palo == 't')
					// Guarda en la posicion i del mazo 13 + el numero - 1
					mazo[i] = CARTASPORPALO + num-1;
				// Si palo es 'd'
				else if (palo == 'd')
					// Guarda en la posicion i del mazo 2*13 + el numero - 1
					mazo[i] = 2*CARTASPORPALO + num-1;
				// Si palo es 'c'
				else if (palo == 'c')
					// Guarda en la posicion i del mazo 3*13 + el numero - 1
					mazo[i]= 3*CARTASPORPALO +num-1;
			
				/* lee la siguiente linea del archivo y vuelve
				 * a guardar la letra y el numero en palo y num
				 */
				archivo >> palo >> num;
				// suma uno a i
				i++;
			}
			// guarda en la posicion actual del mazo (i) el CENTINELA
			mazo[i]=CENTINELA;
			// se cierra el archivo
			archivo.close();
			mazocargado = true;
		}
		// Sino bool mazocargado es false
		else
		{
			j--;
			if( j != 0)
				// si j es diferente de 0, mensaje error con los intentos restantes
				cout << endl << NO_CARGAR << "( " << j << INTENTOS << " )" << endl << endl;
		}
	}

return mazocargado;
}

// Funcion encargada de escribir el mazo que le llega
void escribirMazo(const tMazo mazo)
{
	int n = 0;

	cout << endl;
	// Bucle para mazo diferente de CENTINELA
	while(mazo[n] != CENTINELA)
	{
		/* Llamada a escribirCarta pasandole
		 * el mazo en la posicion n (inicialmente 0)
		 */
		escribirCarta(mazo[n]);
		cout << endl;
		// suma uno a int n
		n++;
	}
	cout << endl;
}

/* Funcion que recibe un valor tipo tCarta
 * y esribe por pantalla el valor correspondiente
 */
void escribirCarta(tCarta carta)
{
	 /* Llama a la funcion darNumero 
	  * pasandole el valor carta que devulve
	  * un enumerado
	  */
	switch (darNumero(carta))
	{
	case AS: cout << " A "; break;
	case DOS: cout << " 2 "; break;
	case TRES: cout << " 3 "; break;
	case CUATRO: cout << " 4 "; break;
	case CINCO: cout << " 5 "; break;
	case SEIS: cout << " 6 "; break;
	case SIETE: cout << " 7 "; break;
	case OCHO: cout << " 8 "; break;
	case NUEVE: cout << " 9 "; break;
	case DIEZ: cout << " 10 "; break;
	case J: cout << " J "; break;
	case Q: cout << " Q "; break;
	case K: cout << " K "; break;
	}

	/* Llama a la funcion darPalo pasandole 
	 * la carta y devulve el enumerado correspondiente
	 */
	switch (darPalo(carta))
	{ 
	case PICAS: setcolor(8); cout << char(6); setcolor(7); break;
	case TREBOLES: setcolor(8); cout << char(5); setcolor(7); break;
	case DIAMANTES: setcolor(4); cout << char(4); setcolor(7); break;
	case CORAZONES: setcolor(4); cout << char(3); setcolor(7); break;
	}
}
/* Funcion llamada desde el menu pasandole 
 * el mazo y barajandolo
 */
void opcionBarajarMazo(tMazo mazo)
{
	// Si mazo esta vacio, mensaje de error
	if (mazoVacio(mazo))
		cout << MAZO_VACIO << endl << NO_BARAJAR << endl;
	else
	{	
		// Escribe el mazo cargado
		escribirMazo(mazo);
		// LLama a barajarMazo devolviendo el mazo barajado
		barajarMazo(mazo);
		// Escribe el mazo barajado
		escribirMazo(mazo);
		cout << endl;
	}
}

// Funcion que baraja el mazo pasandole un mazo
void barajarMazo(tMazo mazo)
{	
	// int j sera igual al numero de cartas el mazo
	int j = cuantasenMazo(mazo);
	int x, y, tmp;
		
	/* For que se repetira dependiendo del
	 * numero de cartas que haya en el mazo
	 */
	for (int i=0; i <= 3*j; i++) 
	{
		/* x e Y = un numero aleatorio entre 0 y
		 * cuantas cartas en mazo -1
		 */
		x = rand()% (cuantasenMazo(mazo)-1);
		y = rand()% (cuantasenMazo(mazo)-1);
		
		// int tmp = el valor de mazo en la posion x aleatoria
		tmp= mazo[x];
		/* asignamos el valor de mazo en posicion "y" aleatorio
		 * a la posicon "x" aleatoria de mazo
		 */
		mazo[x] = mazo[y];
		// en la posicon "y" aleatoria del mazo, gaurdamos int tmp
		mazo[y] = tmp;
	}
}

// Funcion que partira en dos mazos el mazo
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino)
{
	int i = 0;
	bool partir_mazo = false;
	// igualamos "b" a cuantas cartas hay en el mazo original
	int b = cuantasenMazo(mazoOrigen);

	/* Correcto para cuantasCoger menor que el 
	 * numero de cartas que hay en el mazo
	 */
	if( cuantasCoger < cuantasenMazo(mazoOrigen))
	{	
		// Bucle para cuando i es menor que cuantasCoger
		while (i < cuantasCoger)
		{
			/* copiamos en mazoDestino lo que hay en mazoOrigen 
			 * en la posicion i
			 */
			mazoDestino[i] = mazoOrigen[i];
			// Sumamos uno a i 
			i++;
		}
		// en la posicion i le colocamos el CENTINELA (52)
		mazoDestino[i]=CENTINELA;
					
		for (int j=0; i <= b; j++)
		{
			/* colocamos al principio de mazoOrigen lo que hay a partir 
			 * de la posicon i de ese mismo mazo (incluido CENTINELA)
			 */
			mazoOrigen[j]= mazoOrigen[i];
			// sumamos uno a i
			i++;
		}
	// partirmazo pasa a ser true
	partir_mazo = true;
	}
// devolvemos bool partirmazo
return partir_mazo;
}

// Funcion llamada desde el menu que corta el mazo
void opcionCortarMazo(tMazo mazo)
{
	int cuantas;
	// si el mazo esta vacio, mensajes de error
	if (mazoVacio(mazo))
		cout << MAZO_VACIO << endl << NO_CORTAR << endl;
	else
	{	
		// escribe el mazo
		escribirMazo(mazo);
		// pregunta al usuario por que carta quiere cortar
		cout << CARTA_CORTAR;
		// guarda en int cuantas la carta
		cin >> cuantas;
		// cortarMazo devuelve el mazo cortado
		cortarMazo(mazo, cuantas);
		// escribe el mazo ya cortado
		escribirMazo(mazo);
	}
}

// Recibe el mazo y por donde se quiere cortar
void cortarMazo(tMazo mazo, int cuantas)
{
	// Declaramos un mazoDestino
	tMazo mazoDestino;
		
	/* Si por donde quieres cortar es menor a
	 * las cartas que hay en el mazo...
	 */
	if ( cuantas < cuantasenMazo(mazo))
	{	
		// si partirMazo no se realiza correctamente...
		if (!partirMazo(mazo, cuantas, mazoDestino))
			// mensaje al usuario, no se pudo cortar
			cout << NO_CORTAR << endl;
		// si unirMazo no se realiza correctamente
		else if (!unirMazos(mazo, mazoDestino))
			// mensaje al usuario, no se pudo cortar
			cout << NO_CORTAR << endl;
	}
	// mensaje al usuario, no se pudo cortar
	else cout << NO_CORTAR << endl;
} 

// Funcion llamada desde el menu  que une el mazo
void opcionUnirMazos(tMazo mazo)
{
	string nomb;
	tMazo nuevoMazo;
	// si el mazo esta vacio, mensajes de error
	if (mazoVacio(mazo))
		cout << MAZO_VACIO << endl << NO_UNIR << endl;
	else
	{
		// cargamos el nuevo mazo a unir
		if (!cargarMazo(nuevoMazo))
			cout << NO_UNIR << endl;
		// escribe el mazo anterior
		escribirMazo(mazo);
		// escribe el nuevo mazo ya cargado
		escribirMazo(nuevoMazo);
		//llama a la funcion unir que devulve el mazo ya unido
		unirMazos(mazo, nuevoMazo);
		//esccribe el mazo ya unido
		escribirMazo(mazo);
	}
}

// Funcion que recibe dos mazos y que los unira
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo)
{	
	bool unir = false;
 	// int b y j = al numero de cartas en cada mazo
	int b = cuantasenMazo(mazoOriginal);
	int j = cuantasenMazo(nuevoMazo);

	// si los dos mazos a unir no supera MAXCARTAS (53)
	if ( b + j < MAXCARTAS)
	{		
		/* bucle desde 0 hasta el numero de cartas que
		 * haya en el nuevo mazo
		 */
		for( int i= 0; i <= j; i++)
		{
			// copiamos el nuevo mazo detras del mazo original
			mazoOriginal[b] = nuevoMazo[i];
			// sumamos uno a b
			b++;
		}
		// bool unir pasa a ser true
		unir = true;
	}
	// sino... mensaje de error
	else cout << NO_UNIR << endl;
		
return unir;
}

/* Funcion llamada desde menu que guardara el mazo
 * correspondiente en un fichero 
 */
void guardarMazo(const tMazo mazo)
{
	ofstream archivo;
	string nomb_archivo;
	int j = cuantasenMazo(mazo), num;
	
	/* pedimos al usuario que indique el archivo donde 
	 * quiere guardar dicho mazo
	 */
	cout << DONDE_GUARDAR;
	cin >> nomb_archivo;
	// añadimo ".txt" al nombre introducido para que sea legible
	nomb_archivo = nomb_archivo + ".txt";
	// abrimos dicho archivo
	archivo.open(nomb_archivo);
	// si el archivo se abrio sin problema...
	if (archivo.is_open())
	{
		// desde i=0 hasta
		for (int i = 0; i < j; i++)
		{
			/* guardamos en int num el numero que hay en el arry mazo
			 * en la posion i
			 */
			num = mazo[i];
			/* escribimos en el archivo lo que nos devuelve la llamada 
			 * a devolverLetra y delvolverCarta a las cuales les pasamos
			 * el numero guardado en cada posicion del array
			 */
			archivo << devolverLetra(num) << " " << devolverCarta(num) << endl;
		}
		// escribimos el CENTINELA_ARCHIVO (x) al final del archivo
		archivo <<	CENTINELA_ARCHIVO;
		archivo.close();
	}
	// sino... mensaje de error
	else cout << MENSAJE_ERROR << endl;
}

// Funcion que recibe un int num
int devolverCarta(int num)
{
	// Si devolverLetra devuelve una p
	if(devolverLetra(num) == 'p')
		// sumamos 1 a int num
		num = num + 1;
	// si devulve t
	else if(devolverLetra(num) == 't')
		// sumamos uno a int num y le restamos 13
		num = num+1 -  CARTASPORPALO;
	// si devuleve d
	else if(devolverLetra(num) == 'd')
		// sumamos uno a int num y le restamos 2*13
		num = num+1 - 2*CARTASPORPALO;
	// si devulve c
	else if(devolverLetra(num) == 'c')
		// sumamos uno a int num y le restamos 3*13
		num = num+1 - 3*CARTASPORPALO;
// devolvemos el valor de num
return num;
}

/* Funcion tipo char que transforma el int num 
 * que recibe dependiendo de su valor
 */
char devolverLetra(int num)
{
	// declaramos las 4 opciones char
	char p = 'p';
	char t = 't';
	char d = 'd';
	char c = 'c';
	
	/* divide num-1 entre CARTASPORPALO (13)
	 * y devuelve un char, es decir, uno de los 
	 * casos del switch
	 */
	switch ((num-1)/CARTASPORPALO)
	{
	case 0: return p; break;
	case 1: return t; break;
	case 2: return d; break;
	case 3: return c; break;
	}
}

/* Funcion llamada desde el menu que reparte
 * el mazo en cartas negras y rojas
 */
void opcionRepartirNegroRojo(tMazo mazo)
{
	// Declaramos dos mazos nuevos
	tMazo mazoNegro, mazoRojo;

	// Si el mazo esta vacio..
	if (mazoVacio(mazo))
		// mensaje de error, mazo vacio
		cout << MAZO_VACIO << endl;
	else 
	{
		// escribe el mazo que recibe
		escribirMazo(mazo);
		cout << REPARTIR_EN << NEGRO_ROJO << endl;
		/* llama a la funcion repartirNegroRojo
		 * pasandole el mazo y los mazos rojo y negro */
		repartirNegroRojo(mazo, mazoNegro, mazoRojo);
		// escribe el mazo negro
		escribirMazo(mazoNegro);
		// escribe el mazo rojo
		escribirMazo(mazoRojo);
	}
}

// Funcion que hace el reparto del mazo en negras y rojas
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro,tMazo mazoRojo)
{
	// declaramos x, y, j usados como contadores
	int x = 0, i = 0, j = 0;
	
	// bucle para x menor que las cartas que hay en el mazo
	while ( x < cuantasenMazo(mazo))
	{
		// si darPalo en la posicion x devuelve PICAS o TREBOLES
		if ( darPalo(mazo[x]) == PICAS || darPalo(mazo[x]) == TREBOLES)
		{
			/* llenamos el mazoNegro en la posicon i
			 * con el valor de mazo en la posicion x
			 */
			mazoNegro[i]=mazo[x];
			//sumamos uno a i
			i++;
		}
		// sino...
		else
		{	
			/* llenamos el mazoRojo en la posicon j
			 * con el valor de mazo en la posicion x */
			mazoRojo[j]=mazo[x];	
			// sumamos uno a j
			j++;
		}
	// sumamos uno a x
	x++;
	}
	/* ponemos en la posicion actual del 
	 * mazoNegro y del mazoRojo el CENTINELA */
	mazoNegro[i]=CENTINELA;
	mazoRojo[j]=CENTINELA;
}

// Funcion llamada desde el menu que reparte la baraja en altas y bajas	
void opcionRepartirAltasBajas(tMazo mazo)
{
	// declaramos dos nuevos mazos
	tMazo mazoAltas, mazoBajas;
	// si el mazo esta vacio, mensaje de error
	if (mazoVacio(mazo))
		cout << MAZO_VACIO << endl;
	else
	{
		// escribimos el mazo cargado
		escribirMazo(mazo);
		/* esta funcion nos devuelve el mazo,
		 * un mazo con cartas altas y otro con cartas bajas */
		repartirBajaAlta(mazo, mazoAltas, mazoBajas);
		// mensaje al usuario
		cout << REPARTIR_EN << ALTAS_BAJAS << endl;
		// escribir el mazo de cartas altas
		escribirMazo(mazoAltas);
		cout << endl << endl;
		// escribe el mazo de cartas bajas
		escribirMazo(mazoBajas);
		cout << endl << endl;
	}
}

// Funcion que reparte el mazo en cartas bajas y altas
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas)
{
	// Declaramos tres variables tipo int que usaremos localmente
	int x=0, i=0, j=0;

	// bucle para x menor que las cartas que haya en el mazo
	while ( x < cuantasenMazo(mazo))
	{
		// si la posicon x del mazo es menor que OCHO...
		if ( darNumero(mazo[x]) < OCHO )
		{	
			/* colocamos en mazoBajas en la posicion j
			 * la carta que haya en la posicon x del mazo*/
			mazoBajas[j]=mazo[x];
			// sumamos uno a j
			j++;
		}
		// si no...
		else 
		{
			/* colocamos en mazoAltas en la posicion i
			 * la carta que haya en la posicon x del mazo*/
			mazoAltas[i]=mazo[x];
			// sumamos uno a i
			i++;	
		}
	// sumamos uno a x
	x++;
	}
	/* colocamos el centinela al final de cada
	 * uno de los mazos */
	mazoAltas[i]=CENTINELA;
	mazoBajas[j]=CENTINELA;
}

// Funcion llamada desde el menu que repartira el mazo en diferentes montones
void opcionRepartirIntercalando(tMazo mazo, int enCuantosMazos)
{
	tMazo mazoNuevo;
	// si el mazo esta vacio, mensaje de error
	if (mazoVacio(mazo))
		cout << MAZO_VACIO << endl;
	else
	{
		// Si en cuantos mazos repartir es diferente de 3 y 4
		if ( enCuantosMazos != 3 && enCuantosMazos != 4)
		{		
			// mensaje al usuario y guarda en cuantos mazos repartir
			cout << CUANTOS_MAZOS;
			cin >> enCuantosMazos;	
		}

		for ( int i=1; i<= enCuantosMazos; i++)
		{	
			/* a esta funcion le pasamos el mazo a repartir,
			 * en cuantos mazos repartir y nos devolvera para 
			 * cada i un mazoNuevo  */
			repartirIntercalando(mazo, enCuantosMazos, i, mazoNuevo);
			// escribira el mazoNuevo
			escribirMazo(mazoNuevo);
		}
	}
}

/* Funcion que a partir de un mazo, te devuelve uno nuevo
 * en funcion del mazo que pido y de cuantos mazo repartir
 */
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo)
{
	// declaramos int que serviran como contadores
	int i=0, j= queMazoPido-1;

	// si hay mas cartas que mazos a repartir...
	if ( enCuantosMazos < cuantasenMazo(mazo))
	{
		// bucle para j menor que las cartas que hay en el mazo
		while ( j < cuantasenMazo(mazo))
		{		
			/*  copiamos en el mazoNuevo la carta que
			 * hay en mazo en la posicion j */
 			mazoNuevo[i]= mazo[j];
			// sumamos uno a i
			i++;
			// j sera su valor actual + el numero de mazos
			j= j + enCuantosMazos;
		}
		// colocamos el CENTINELA en la ultima posicion
		mazoNuevo[i]=CENTINELA;
	}
	// mensaje de error al usuario
	else cout << NO_REPARTIR << endl;
}

/* Funcion que realizara un truco en el que se  repartira un mazo
 * en tres montones en el que el usuario pensara una carta y esta
 * sera adivinada por el programa
 */
void trucoTresMontones()
{
	/* Declaramos dos tipos tMazo y dos tipos int para
	 * pasarselos a la funcion repartirIntercalando */
	tMazo mazo, mazoAux_1, mazoAux_2, mazoAux_3;
	int queMazoPido, enCuantosMazos=3, x=0;
		
	/* cargamos un mazo atraves de cargarMazo, 
	* y si lo carga correctamente...*/
	if (cargarMazo(mazo))
		// baraja el mazo cargado anteriormente
		barajarMazo(mazo); 
		
	for (int i=0; i<3; i++)
	{
		// mensaje al usuario " repartir en.."
		cout << endl << REPARTIR_EN << enCuantosMazos << " ..." << endl;

		// Funcion que repare el mazo cargado en 4 partes y los muestra
		opcionRepartirIntercalando(mazo, enCuantosMazos);
		// Mensaje al usuario dice al usuario que la carta debe ser la misma
		if ( i!=0)
			cout << MISMA_CARTA << endl << endl;
		else
			// Mensaje que pide al usuario que memorice una carta
			cout << MEMORIZAR << endl << endl;
		
		// pide al usuario que indique en que mazo se encuentra su carta
		cout << MAZO_CARTA;
		cin >> queMazoPido;
		
		/* Llamamos a la funcion que reparte el mazo, 
		 * pasandole el numero de mazos en lo que lo queremos repartir (3) y
		 * donde guardamos cada mazo resultante (mazoAux_1, mazoAux_2...*/
		repartirIntercalando(mazo, 3, 1, mazoAux_1);
		repartirIntercalando(mazo, 3, 2, mazoAux_2);
		repartirIntercalando(mazo, 3, 3, mazoAux_3);
		// si esta en el 1 mazo...
		if ( queMazoPido == 1)
		{	
			/* unimos el mazo 2 con el mazo 1 y a continuacion con el 3
			 *  poniendo el mazo que ha indicado el usuario en medio
			 * de los otros dos restantes */
			unirMazos(mazoAux_2, mazoAux_1);
			unirMazos(mazoAux_2, mazoAux_3);
			// for desde j=0 hasta las cartas que haya en mazoAux_2
			for ( int j=0; j <= cuantasenMazo(mazoAux_2); j++)
			{	
				// copiamos en mazo lo que hay en el mazoAux_2
				mazo[x]=mazoAux_2[j];
				// sumamos uno a x
				x++;
			}
		}
		// si esta en el 2 mazo...
		else if (queMazoPido==2)
		{
			/* unimos el mazo 1 con el mazo 2 y a continuacion con el 3
			 *  poniendo el mazo que ha indicado el usuario en medio
			 * de los otros dos restantes */
			unirMazos(mazoAux_1, mazoAux_2);
			unirMazos(mazoAux_1, mazoAux_3);
			// for desde j=0 hasta las cartas que haya en mazoAux_1
			for ( int j=0; j <= cuantasenMazo(mazoAux_1); j++)
			{
				// copiamos en mazo lo que hay en el mazoAux_1
				mazo[x]=mazoAux_1[j];
				// sumamos uno a x
				x++;
			}
		}
		// si esta en el 3 mazo...
		else if (queMazoPido==3)
		{
			/* unimos el mazo 1 con el mazo 3 y a continuacion con el 2
			 *  poniendo el mazo que ha indicado el usuario en medio
			 * de los otros dos restantes */
			unirMazos(mazoAux_1, mazoAux_3);
			unirMazos(mazoAux_1, mazoAux_2);
			// for desde j=0 hasta las cartas que haya en mazoAux_1
			for ( int j=0; j <= cuantasenMazo(mazoAux_1); j++)
			{	
				// copiamos en mazo lo que hay en el mazoAux_1
				mazo[x]=mazoAux_1[j];
				// sumamos uno a x
				x++;
			}
		}
	// actualizamos x=0
	x=0;
	}
	
	/* mostramos la carta elegida por el usuario 
	 * que estara en la 10 posicion del mazo */
	cout << " La carta es ";
	escribirCarta(mazo[10]);
	cout << endl << endl;
}

/* Truco de la posada repartira un mazo de 21 cartas en 4 partes
 *  los unira dos a dos en un solo mazo. A continuacion partira por una
 * posicion pedida al usuario y lo volvera a repartir en 4 partes 
 */
void trucoPosada()
{
	tMazo mazo, mazoAux1, mazoAux2, mazoAux3, mazoAux4;
	int posicion, enCuantosMazos=4;

	// LLamamos a la funcion cargarMazo para obtener el mazo necesario
	cargarMazo(mazo);
	/* Pasamos el mazo cargado a opcionRepartirIntercalando
	 * y en cuantos mazos vamos a repartir */
	opcionRepartirIntercalando(mazo, enCuantosMazos);
	/* Llamamos a la funcion que reparte el mazo, 
	 * pasandole el numero de mazos en lo que lo queremos repartir (4) y
	 * donde guardamos cada mazo resultante (mazoAux1, mazoAux2...*/
	repartirIntercalando(mazo, 4, 1, mazoAux1);
	repartirIntercalando(mazo, 4, 2, mazoAux2);
	repartirIntercalando(mazo, 4, 3, mazoAux3);
	repartirIntercalando(mazo, 4, 4, mazoAux4);
	// mensaje al usuario 
	cout << UNIMOS_MAZOS << endl;
	
	//unimos los 4 mazos resultantes dos a dos
	unirMazos(mazoAux1, mazoAux2);
	unirMazos(mazoAux3, mazoAux4);
	unirMazos(mazoAux1, mazoAux3);
	// escribimos el mazo ya unido 
	escribirMazo(mazoAux1);
	// pedimos al usuario por donde quiere cortar
	cout << CARTA_CORTAR;
	cin >> posicion;
	/* llamamos a la funcion encargada de cortar el mazo
	* pasandole el mazo y la posicion por donde cortar */
	cortarMazo(mazoAux1, posicion);
	// si posicion es menor a las cartas en mazo
	if ( posicion < cuantasenMazo(mazoAux1))
		// volvemos a repartir el mazo en 4 partes y lo mostramos
		opcionRepartirIntercalando(mazoAux1, enCuantosMazos);
	// sino, mensaje de error
	else cout << NO_TRUCO << endl;
}