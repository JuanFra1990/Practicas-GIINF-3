#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#include <GL/glut.h>
#include <string>

#include "igvEscena3D.h"
#include "igvCamara.h"

using namespace std;

class igvInterfaz {
protected:
	// Atributos
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion
	bool perspective; //Controla vista perspectiva
	int contador; //Contador que nos permite saber si mostrar alzado planta o perfil
	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	igvCamara camara; // c�mara que se utiliza para visualizar la escena

public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();

	// Metodos est�ticos
	// callbacks de eventos
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // m�todo que define la camara de vision y el viewport
	// se llama autom�ticamente cuano se camba el tama�o de la ventana
	static void set_glutDisplayFunc(); // m�todo para visualizar la escena


	// Metodos
	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los par�metros para crear una ventana de visualizaci�n
	void configura_entorno(int argc, char** argv, // parametros del main
		int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizaci�n
		int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizaci�n
		string _titulo // t�tulo de la ventan de visualizaci�n
		);
	void inicializa_callbacks(); // inicializa todas los callbacks

	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// m�todos get_ y set_ de acceso a los atributos
	int get_ancho_ventana(){ return ancho_ventana; };
	int get_alto_ventana(){ return alto_ventana; };

	void set_ancho_ventana(int _ancho_ventana){ ancho_ventana = _ancho_ventana; };
	void set_alto_ventana(int _alto_ventana){ alto_ventana = _alto_ventana; };

	bool get_perspective(){ return perspective; };
	void set_perspective(bool _perspective){ perspective = _perspective; };

	int get_contador() { return contador; };
	void set_contador() { contador++; };
	void set_contador_0() { contador = 0; };

};

#endif
