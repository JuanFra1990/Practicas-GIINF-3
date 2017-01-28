#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>

class igvEscena3D {
	protected:
////// Apartado B: añadir quí los atributos para el control de los grados de libertad del modelo
		float base;
		
		float braderechox;
		float braderechoz;
		float pelo1braderecho;

		float braderechosupx;
		float braderechosupz;
		float pelo1braderechosup;

		float braizquierdox;
		float braizquierdoz;
		float pelo1braizquierdo;


		float braizquierdoinfx;
		float braizquierdoinfz;
		float pelo1braizquierdoinf;


////// Apartado D: añadir aquí el atributo/s para el control del objeto seleccionado y colorearlo en amarillo
		int objeto_seleccionado;

		// Otros atributos		
		bool ejes;

	public:
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar(void);

	//Metodos para dibujar los diferentes elementos de la escena
	void dibuja_base();
	void dibuja_brazoder();
	void dibuja_brazoizq();
	void dibuja_brazodersup();
	void dibuja_brazoizqinf();

	void dibuja_pelo1_brazoizq();
	void dibuja_pelo1_brazoder();
	void dibuja_pelo1_brazoizqinf();
	void dibuja_pelo1_brazodersup();

	void dibuja_figura();
	


////// Apartado B: añadir aquí los métodos para modificar los grados de libertad del modelo
	void rotarBase(float valor);
	void rotarBrazoizqx(float valor);
	void rotarBrazoizqz(float valor);
	void rotarBrazoderx(float valor);
	void rotarBrazoderz(float valor);
	void rotarBrazoizqinfx(float valor);
	void rotarBrazoizqinfz(float valor);
	void rotarBrazodersupx(float valor);
	void rotarBrazodersupz(float valor);

	void rotarPelo1Brazodersup(float valor);
	void rotarPelo1Brazoder(float valor);
	void rotarPelo1Brazoizqinf(float valor);
	void rotarPelo1Brazoizq(float valor);

////// Apartado D: añadir aquí el método/s para indicar el objeto seleccionado
	void objetoseleccionado(int objeto){ objeto_seleccionado = objeto; };

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
};

#endif
