#include "correo.h"

using namespace std;

void correoNuevo (tCorreo &correo, string emisor)
{
	stringstream id, cuerpo;
	string linea;
	
	cout << "De: " << emisor << endl;
	cout << "Para: ";
	cin >> correo.destinatario;
	cout << endl << "Asunto: ";
	cin.sync();
	getline(cin, correo.asunto);
	cout << endl;
	
	getline(cin, linea);

	while ( linea[0]!= CENTINELA_CUERPO)
	{
		cuerpo << linea << endl;
		getline(cin, linea);
	}

	correo.cuerpo = cuerpo.str();
	correo.fecha = time(0);
	correo.emisor = emisor;
		
	id << correo.emisor << "_" << correo.fecha;
	correo.unico = id.str();

}

void correoContestacion (const tCorreo &correoOriginal, tCorreo &correo, string emisor)
{
	stringstream id, cuerpo;
	string linea;
	
	cout << "De: " << correoOriginal.destinatario << endl;
	correo.destinatario = correoOriginal.emisor;
	cout << "Para: " << correoOriginal.emisor << endl;
	correo.emisor = correoOriginal.destinatario;
	correo.asunto = "Re: " + correoOriginal.asunto;
	cout << "Asunto: " << correo.asunto << endl << endl;	
		
	getline(cin, linea);
	while ( linea[0]!= CENTINELA_CUERPO)
	{
		cuerpo << linea << endl;
		getline(cin, linea);
	}

	correo.cuerpo = cuerpo.str();
	
	correo.fecha = time(0);

	id << correo.emisor << "_" << correo.fecha;
	correo.unico = id.str();
}

string mostrarFecha(tFecha fecha)
{
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm,&fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	resultado<<", "<< ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec;
	return resultado.str();
}	

string mostrarFechaSoloDia(tFecha fecha)
{
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm,&fecha);
	resultado<<1900 + ltm.tm_year<<"/"<<1 + ltm.tm_mon<<"/"<<ltm.tm_mday;
	return resultado.str();
}
string aCadena(const tCorreo &correo)
{
	stringstream cad;
	string cadena;
	
	// mostramos el emisor, la fecha, el destinatario, el asunto y el cuerpo del mensaje
	cad << "De: " << correo.emisor << setw(40) << mostrarFecha(correo.fecha) << endl
	<< "Para: " << correo.destinatario << endl
	<< "Asunto: " << correo.asunto << endl << endl
	<< correo.cuerpo << endl;

	cadena = cad.str();

return cadena;
}

string obtenerCabecera(const tCorreo &correo)
{
	stringstream cab;
	string cabecera;

	cab << correo.emisor << setw(20) << correo.asunto << setw(22) << mostrarFechaSoloDia(correo.fecha) << endl;
	
	cabecera = cab.str();

return cabecera;
}

void cargar (tCorreo &correo, ifstream &archivo)
{
	string linea, esp_basura;
		
	archivo >> correo.unico;
	archivo >> correo.fecha;
	archivo >> correo.emisor;
	archivo >> correo.destinatario;
	getline (archivo, esp_basura);
	getline(archivo, correo.asunto);
	
	getline(archivo, linea);
	while ( linea[0]!= CENTINELA_CUERPO)
	{		
		correo.cuerpo+=linea + "\n";
		getline(archivo, linea);
	}
}

void guardar(const tCorreo &correo, ofstream& archivo)
{
	/* escribimos en un archivo en cada linea,
	 * informacion del correo y un centinela al final de cada cuerpo */
	archivo << correo.unico << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo << endl;
	archivo << CENTINELA_CUERPO << endl;
}