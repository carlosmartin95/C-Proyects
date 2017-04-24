/*******************************************
 * FUNDAMENTOS DE PROGRAMACIÓN
 * Facultad de Informática
 * Universidad Complutense de Madrid
 * 
 * Autores: Carlos Martín Gutiérrez 51098295-T
 *			Francisco Rafael García rofes
 * Práctica: 2048
 * Fecha de creación: 1/3/2015
 * Fecha de última modificación: 25/3/2015
 * Contacto: camart12@ucm.es
 *			 franga06@ucm.es
 *
 *******************************************/

// declaracion de bibliotecas
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath>
#include <conio.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

// constantes
const int DIM = 4;
const string CARGAR_SN= " Quieres cargar un tablero? [s/n] : ";
const string QUE_ARCHIVO= " Que archivo quieres cargar : ";
const string MENSAJE_ERROR= " El archivo no se pudo cargar ";
const string DIRECCION= " Introduce una direccion (flechas de direccion), o ESC";
const string GANADO = " HAS GANADO!! ";
const string LLENO = " No se pueden realizar mas movimientos, HAS PERDIDO. ";
const string NOMBRE = " Introduce tu numbre: ";
const string NOMBRE_ARCHIVO = " Introduce el nombre del archivo: ";
const string QUIERES_GUARDAR = " Quieres guardar la partida? [S/N]: ";
const string GUARDADO = " Guardado con exito ";
const string SEGURO_SALIR = " Estas seguro de que quieres salir? [S/N]: ";
const string TOP_10 = " HAS ENTRADO EN EL TOP 10 !! ";
const string CENTINELA = "???";
const string NO_RECORD = " No has entrado en el TOP 10";
const string NO_CARGAR = " No se pudo cargar el archivo ";
const string MENSAJE_DESP = " Hasta otra !! ";
const string RESP_NOVALE = " Opcion no valida (introduzca s o n) ";

// declaracion de tipos 
typedef int tTablero[DIM][DIM];
typedef enum tAccion {ARRIBA, ABAJO, IZQUIERDA, DERECHA, SALIR, NADA};

// declaracion de funciones
bool lleno(const tTablero tablero);
int log2(int num);
int mayor(const tTablero tablero);
void inicializar (tTablero tablero);
void setBackgroundColor(int color);
void visualiza (const tTablero tablero, int puntos, int total);
void carga(tTablero tablero, int &total, bool &ok);
void linea_superior();
void interior(const tTablero tablero, int fila);
void mediana();
void linea_inferior();
void mover (tTablero tablero, tAccion accion);
void obtenerParametros(tTablero tablero, int incremento_x,int incremento_y, int ini_x, int ini_y);
void combinaFichas(tTablero tablero, tAccion accion, int &puntos);
void combinar( tTablero tablero, int incremento_x,int incremento_y,int &puntos);
void nuevaFicha (tTablero tablero);
void guarda(const tTablero tablero, int puntos);
tAccion leeAccion();


// funcion principal
int main()
{
	// declaracion e inicializacion de variables
	tTablero tablero;
	tAccion accion;
	string nombre;
	int puntos=0, total=0;
	bool ok = false;
	string respuesta;
	srand(time(NULL));
	
	do
	{
		// preguntamos si queremos cargar un tablero
		cout <<  endl << CARGAR_SN;
		cin >> respuesta;
		cout << endl;
		
		// si la respuesta es si, cargamos tablero
		if ( respuesta == "s")
		{
			while (!ok)
			{	
				carga(tablero, total, ok); // llamamos a cargar
			}
		}
		// si la respuesta es no, inicializamos un nuevo tablero
		else if (respuesta == "n")
			{
				ok = true;
				inicializar(tablero); // llamamos a inicializar
			}
			else cout << RESP_NOVALE << endl; // respuesta no valida
	}
	// repetimos mientras la respuesta no sea valida
	while ( respuesta != "s" && respuesta != "n");
	
	system("cls");
	cout << endl;
	visualiza(tablero, puntos, total); // visualizamos el tablero
	
	cout << DIRECCION << endl;
	do	
	{
		accion = leeAccion(); //pedimos una direccion
	}
	// repetimos mientras la direccion no sea valida
	while ( accion == NADA ); 

	// si la accion es = SALIR
	if (accion == SALIR)
	{		
		// mensaje con el usuario, de seguro salir
		cout << endl << SEGURO_SALIR; 
		cin >> respuesta;
		// si la respuesta es no...
		if ( respuesta == "n")
		{
			do	
			{
				system("cls");
				cout << endl;
				visualiza(tablero, puntos, total); // visualizamos
				cout << DIRECCION << endl;
				accion = leeAccion(); // pedimos direccion
			}
			// repetimos si la accion = NADA
			while ( accion == NADA );
		}
		// si la respuesta es si, HASTA OTRA
		else cout << MENSAJE_DESP << endl;
	}
	// mientras la direccion en la que mover sea diferente de SALIR...
	while  ( accion != SALIR )
	{
 		system("cls"); // borramos la pantalla
		cout << endl << endl;
		mover(tablero, accion); // llamamos a mover
		combinaFichas(tablero, accion, puntos); // combinamos
		mover(tablero, accion); // movemos de nuevo
		nuevaFicha(tablero); // colocamos una nueva ficha
		total = total + puntos; // calculamos los puntos
		visualiza(tablero, puntos, total); // visualizamos el tablero
		puntos = 0; // ponemos los puntos del movimiento actual a 0
			
		// si has ganado...
		if (mayor(tablero) >= 2048)
		{
			accion = SALIR;
			cout << GANADO << endl << endl;
		}
		// si el tablero esta lleno...
		else if(lleno(tablero))
		{
			accion = SALIR;
			cout << LLENO << endl << endl;
		}
		// sino pedimos direccion para mover de nuevo
		else 
		{
			cout << DIRECCION << endl;
			do
			{
				accion = leeAccion();
			}			
			while ( accion == NADA);
		}	
		
		// si la accion es salir y el tablero no esta lleno...
		if (accion == SALIR && !lleno(tablero))
		{
			// mensaje para guardar partida
			cout << endl << QUIERES_GUARDAR; 
			cin >> respuesta;
			
			if (respuesta == "s")
				guarda(tablero, total); // llama a guardar
						
			if (mayor(tablero) < 2048)
			{
				// mensaje para si estas seguro de salir
				cout << endl << SEGURO_SALIR; 
				cin >> respuesta;
				// si la respuesta es NO
				if ( respuesta == "n") 
				{
					/* borramos la pantalla, visualizamos el tablero 
					   y pedimos de nuevo una direccion */
					system("cls");
					visualiza(tablero, puntos, total);
					cout << DIRECCION;
					do
					{
						accion = leeAccion();
					}			
					while ( accion == NADA);
				}		
				// mensaje de despedida
				else cout << endl << MENSAJE_DESP << endl; 
			}
		}
	}

system ("PAUSE");
return 0;
}

// Funcion que inicializa el tablero
void inicializar (tTablero tablero)
{
	// variables
	int a, b, fila1, columna1, fila2, columna2;
	
	// rellenamos el tablero con (posiciones vacias)
	for (int i=0; i<DIM; i++)
	{
		for (int j=0; j<DIM; j++)
		{
			tablero[j][i]=1;
		}
	}
			
	do 
	{
		/*calculamos dos filas y dos columnas aleatorias
		y dos numero aleatorios entre 0 y 100*/
		fila1 = rand() % DIM;
		fila2 = rand() % DIM;
		columna1 = rand() % DIM;
		columna2 = rand() % DIM;
		a = rand() % 100;
		b = rand () % 100;
	
		// si las filas o columnas son diferentes
		if (fila1 != fila2 || columna1 != columna2)
		{
			/*95% probabilidad para obtener un 2
			 5% probabilidad para obtener un 4*/

			if (a <= 95 && b <= 95)
			{	
				tablero[fila1][columna1] =2;
				tablero[fila2][columna2] = 2;
			}
			else if ( b >95)
			{
				tablero[fila1][columna1]=2;
				tablero[fila2][columna2] = 4;
			}
			else if ( a > 95)
			{
				tablero[fila1][columna1]=4;
				tablero[fila2][columna2] = 2;
			}
		}
	} 
	// while si las filas y columnas son iguales
	while ( fila1 == fila2 && columna1 == columna2);
}

// Funcion que devuelve la potencia de 2 del numero que recive
int log2(int num)
{
	int numero;
	
	//numero que recive
	switch (num)
	{
	case 2: numero=1; break;
	case 4: numero=2;  break;
	case 8: numero=3; break;
	case 16: numero=4; break;
	case 32: numero=5; break;
	case 64: numero=6; break;
	case 128: numero=7; break;
	case 256: numero=8; break;
	case 512: numero=9; break;
	case 1024: numero=10; break;
	case 2048: numero=11; break;
	default: numero = 0; break;
	}
 //devuelve la potencia de dos
 return numero;
}

/*Funcion que dependiendo del entero que reciba
 *cambia el color de fondo*/
void setBackgroundColor(int color) 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

// Funcion que dibuja la parte superior del tablero
void linea_superior()
{
	// escribe el caracter ┌
	cout << setw(4) << char(218);   

	for (int i = 0; i < DIM-1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// escribe caracteres ─
			cout << char(196); 
		}
		// escribe ┬
		cout << char(194); 
	}
	
	for (int j = 0; j < 6; j++)
	{
		// escribe caracteres ─
		cout << char(196); 
	}
	// acaba con la esquina ┐
	cout <<char(191) << endl; 
}

// Funcion que muestra por pantalla el tablero en si
void visualiza(const tTablero tablero, int puntos, int total)
{
	// fondo a negro
	setBackgroundColor(0);
	// ponemos los puntos y el total de puntos
	cout << setw(12) << puntos << setw(10) << total << endl;
	
	// llamanos a la funcion que visualiza la parte superior del tablero
	linea_superior();

	for (int i = 0; i < DIM; i++)
	{
		// dejamos 4 espacios y escribe │
		cout << setw(4) << char(179);
		
		/* llamamos a la funcion interior y le pasamos el tablero 
		   y la posicion del for por la que vayamos */
		interior(tablero, i);
		// dejamos 4 espacios y escribe │
		cout << setw(4) << char(179);
		
		for (int j=0; j<DIM; j++)
		{
			// cambiamos el fondo de color
			setBackgroundColor(log2(tablero[i][j]));
			cout << setw(6); // dejamos 6 espacios
			
			/* escribimos el valor de la poscion actual del array
			   mientras sea diferente de 1 (vacio) */
			if ( tablero[i][j] !=1)
				cout << tablero[i][j];
			else cout << " ";
			
			setBackgroundColor(0); // color de fondo a negro
			cout << char(179); // escribe │
		}
		// dejamos 4 espacios y escribe │
		cout << endl << setw(4) << char(179);
		// llamamos de nuevo a la funcion interior
		interior(tablero,i);
		// llamamos a la funcion para escribir la mediana del tablero
		if (i < DIM-1)
			mediana();
	}
	// llamamos a la funcion para escribir la parte inferior
	linea_inferior();
}

// Funcion que dibuja el interior del tablero
void interior(const tTablero tablero, int fila)
{
	for (int i = 0; i < DIM; i++)
	{ 
		/*cambia el color del fondo dependiendo del contenido del array
		llamando a la funcion setBackgroundColor*/
		setBackgroundColor(log2(tablero[fila][i]));
		// dejamos 6 espacios 
		for (int j=0; j<6; j++)
		{
			cout << " ";
		}
		// volver a pintar de negro
		setBackgroundColor(0); 
		// escribe │
		cout << char(179);
	}
	cout << endl;
}

void mediana()
{
	// escribe ├
	cout << setw(4) << char(195); 

	// uso del for para repetir el proceso
	for (int i = 0; i < DIM-1; i++){

		for (int j = 0; j < 6; j++){ 
			// luego  ─
			cout << char(196); 
		}
		// escribe ┼
		cout << char(197); 
	}
	for (int i = 0; i < 6; i++){
		// luego  ─
		cout << char(196);
	}
	// acaba con ┤
	cout << char(180) << endl; 
}

void linea_inferior()
{
	// escribe el caracter └
	cout << setw(4) << char(192);   
	
	// uso del for para repetir el proceso
	for (int i = 0; i < DIM-1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// escribe caracteres ─
			cout << char(196); 
		}
		// escribe ┴
		cout << char(193); 
	}

	for (int j = 0; j < 6; j++)
	{
		// escribe caracteres ─
		cout << char(196); 
	}
	
	cout <<char(217) << endl << endl;

}

// Funcion que carga un tablero de archivo
void carga(tTablero tablero, int &total, bool &ok)
{
	// variables 
	ifstream archivo;
	string nomb;
	int dimension, valor;

	// obtencion del archivo deseado
	cout << QUE_ARCHIVO;
	cin >> nomb;
	nomb = nomb + ".txt";

	// apertura y comprobacion de apertura del archivo indicado
	archivo.open(nomb);
	if (archivo.is_open())
	{
		// lectura de datos del archivo
		archivo >> dimension;			

		if (dimension == DIM)
		{
			for (int k=0; k<DIM; k++)	
			{
				for(int i=0; i<DIM; i++)
				{
					/*leemos un valor de cada linea del archivo
					y lo guardamos en la posicion del array correspondiente*/
					archivo >> valor;
					tablero[k][i]=valor;
				}
			}
		
			// leemos el total de puntos
			archivo >> total;
			archivo.close(); // cerramos el archivo
			ok = true;
		}
		else ok=false;
	}
	// sino mensaje de error y ok valdra false
	else
	{
		cout << MENSAJE_ERROR << endl << endl;
		ok=false;
	}
}

// funcion de tipo que devuelve una accion
tAccion leeAccion()
{
	// declaracion variables
	int dir;
	tAccion accion;

	// leemos la direccion
	cin.sync();
	dir = _getch();
	
	// si es de tipo espeacial... (flechas de direccion)
	if (dir ==0xe0)
	{
		// leemos de nuevo 
		dir = _getch();
		// siwtch para el segundo valor leido
		switch (dir)
		{
			case 77: accion = DERECHA; break;
			case 75: accion = IZQUIERDA; break;
			case 72: accion = ARRIBA; break;
			case 80: accion = ABAJO; break;
		}
	}
	// si no es tipo especial... y si es en codigo ASCII 27
	else if (dir == 27)
			accion = SALIR;
		// si es cualquier otro valor...
		 else
			accion = NADA;  

// devuelve la accion	
return accion;
}

void obtenerParametros ( tTablero tablero,tAccion accion,  int &incremento_x, int &incremento_y, int &ini_x, int &ini_y, int z)
{
	/*switch que dependiendo de la accion que reciba
	devolvera unos incrementos y unas posiciones*/ 
	
	switch (accion)
	{
		case ARRIBA:
			incremento_x = 1; 
			incremento_y = 0; 
			ini_x=0; 
			ini_y=z; break;
		
		case ABAJO: 
			incremento_x = -1; 
			incremento_y = 0; 
			ini_x=3;
			ini_y=z; break;
		
		case IZQUIERDA: 
			incremento_x = 0;
			incremento_y = 1; 
			ini_x=z; 
			ini_y=0; break;
			
		case DERECHA: 
			incremento_x = 0; 
			incremento_y = -1; 
			ini_x=z;
			ini_y=3; break;
	}
}

// funcion booleana
bool paramvalidos(tAccion accion, int x, int y, int ini_x, int ini_y)
{
	bool valido;
	
	//si x , ini_x , y, ini_y son iguales devuelve false
	if (x==ini_x && y == ini_y )
			valido = false;
	// sino devuelve true
	else valido = true;

return valido;
}

// Funcion que mueve las fichas del tablero
void mover(tTablero tablero, tAccion accion)
{
	bool valido = true, encontrado = false;
	int ini_x, ini_y, incremento_x, incremento_y, x, y, contador = 0;
		
	for (int i = 0; i < DIM; i++)
	{
		// obtenemos los parametros
		obtenerParametros(tablero, accion, incremento_x, incremento_y, ini_x, ini_y, i);
	
		// igualamos
		x = ini_x;
		y = ini_y;

 		while (!encontrado && valido)
		{						
			if (tablero[x][y] != 1 && paramvalidos( accion, x, y, ini_x, ini_y))
				encontrado = true;	
									
			// si encontrado es true
			if (encontrado)		
			{
				tablero[ini_x][ini_y] = tablero[x][y]; // igualamos
				tablero[x][y] = 1; // colocamos el 1
				encontrado = false;
			}
						
			while ( tablero[ini_x][ini_y] != 1 && contador < DIM)
			{
				// sumatorios para la siguiente casilla
				ini_x += incremento_x;
				ini_y += incremento_y;
				x = ini_x;
				y = ini_y;
				contador++;
			}
			// sumatorios			
			x += incremento_x;
			y += incremento_y;
						
			// comprobamos que no las posiciones a comprobar no se salgan del tablero
			if ( x < 0 ||  x >= DIM || y < 0 || y >= DIM)
				valido = false;
		}
		valido = true;
		contador = 0;
	}
}
	
// funcion que combina fichas iguales 
void combinaFichas(tTablero tablero, tAccion accion, int &puntos)
{
	bool valido = true, encontrado = false;
	int ini_x, ini_y, incremento_x, incremento_y;
		
	for (int i = 0; i < DIM; i++)
	{
		// obtenemos los parametros necesarios
		obtenerParametros(tablero, accion, incremento_x, incremento_y, ini_x, ini_y, i);
	
 		while (!encontrado && valido)
		{						
			if (tablero[ini_x+incremento_x][ini_y+incremento_y] == tablero[ini_x][ini_y]  && tablero[ini_x][ini_y] != 1)
				encontrado = true;	
									
			// si se ha encontrado...
			if (encontrado)		
			{
				// cambiamos la ficha por la correspondiente y ponemos un 1 en la "restante"
				tablero[ini_x][ini_y] = tablero[ini_x+incremento_x][ini_y+incremento_y] *2;
				tablero[ini_x+incremento_x][ini_y+incremento_y] = 1;
				puntos = puntos + tablero[ini_x][ini_y];
				encontrado = false;
			}
						
			do 
			{
				// incrementos
				ini_x += incremento_x;
				ini_y += incremento_y;
							
				if ( ini_x < 0 ||  ini_x > DIM-1 || ini_y < 0 || ini_y > DIM-1)
					valido = false;
			}
			while (tablero[ini_x][ini_y] == 1 && valido);
		}
		valido = true;
	}
}

// Funcion que devuelve el numero mayor en el tablero
int mayor(const tTablero tablero)
{
	int mayor=1;
	
	// recorremos el array bidimensional
	for (int i=0; i < DIM; i++)
	{
		for(int j=0; j<DIM; j++) 
		{
			// si encontramos un valor mayor que el anterior...
			if ( tablero[i][j] > mayor)
				mayor=tablero[i][j];
		}
	}
// devuelve el numero mayor
return mayor;
}

// Funcion que devuelve si el tablero esta lleno de fichas
bool lleno (const tTablero tablero)
{
	// inicializacion
	bool lleno = true;
	int i=0, j=0;

	// busqueda por el array de alguna posicion = 1
	while (j < DIM && lleno)
	{		
		while(i < DIM && lleno)
		{
			// si alguna posicion es = 1,el tablero no esta lleno
			if(tablero[i][j] == 1)
				lleno = false;
			i++;
		}
		j++;
		i = 0;
	}
// devuelve lleno true o lleno false
return lleno;
}

// Funcion que produce una nueva ficha en el tablero
void nuevaFicha (tTablero tablero)
{
	// variables
	int a, nueva, fila, columna;
	bool b = false;
	
	/* producimos un valor entre 0 y 100, una fila y
	una columna aleatorias*/
	a = rand() % 100;
	fila = rand() % DIM;
	columna = rand() % DIM;

	/* 5 % de probabilidade de salir un 4
	   95 % de probabilidad de salir un 2 */
	if (a <= 95)
		nueva = 2;
	else nueva = 4;
	
	// Repetimos mientras el booleano sea false
	while (!b)
	{
		/*comprobamos que la fila y la columna aleatorias que hemos
		  obtenido esten vacias ( =1 ) */
		if (tablero[fila][columna] == 1)
		{	
			// y la colocamos
			tablero[fila][columna] = nueva;
			b = true;
		}

		// Si no lo esta, calculamos otras posiciones y repetimos
		else 
		{
			fila = rand() % DIM;
			columna = rand() % DIM;		
		}
	}
}

void guarda(const tTablero tablero, int puntos)
{
	// declaracion de variables
	string nombre;
	ofstream archivo;
	
	// guardamos el nombre del archivo pedido al usuario
	cout << NOMBRE_ARCHIVO;
	cin >> nombre;
	nombre = nombre + ".txt";

	// apertura y comprobacion de apertura del archivo
	archivo.open(nombre);

	if (archivo.is_open())
	{
		// escribimos la dimension del tablero
		archivo << DIM << endl;
		
		/*escribimos en el archivo el contenido de cada posicion 
		del array. Cada dato en un linea*/
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j  < DIM; j ++)
				archivo << tablero[i][j] << endl;
		}
		// escribimos los puntos
		archivo << puntos;
		// mensaje al usuario de guardado
		cout << GUARDADO << endl;
	}
}

	