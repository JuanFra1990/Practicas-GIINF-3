#include <cstdlib>

#include "igvInterfaz.h"
#include "igvTextura.h"

// Objetos globales
// objeto que contiene la configuración y la interacción con la ventana de visualización
igvInterfaz interfaz;

int main (int argc, char** argv) {
	// inicializa la ventana de visualización
	interfaz.configura_entorno(argc,argv,
		                         500,500, // tamaño de la ventana
														 100,100, // posicion de la ventana
														 "Informática Gráfica y Visualización. Proyecto" // título de la ventana
														 );

	// establece las funciones callbacks para la gestión de los eventos
	interfaz.inicializa_callbacks();

	//Carga la textura
	glEnable(GL_TEXTURE_2D);
	igvTextura *tablero = new igvTextura("tablero.bmp");
	tablero->aplicar();

	// inicia el bucle de visualización de OpenGL
	interfaz.inicia_bucle_visualizacion();

	//Desactiva la textura
	glDisable(GL_TEXTURE_2D);

	return(0);
}
