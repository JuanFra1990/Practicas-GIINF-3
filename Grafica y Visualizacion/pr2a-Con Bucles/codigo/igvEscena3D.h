#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>

class igvEscena3D {
	protected:
		// Atributos

		bool ejes;
		bool opcionA1;
		bool opcionA2;
		bool opcionB1;
		bool opcionB2;
		bool opcionC;

	public:
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar();

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
		bool get_opcionA1(){ return opcionA1; };
		void set_opcionA1(bool _opcion){ opcionA1 = _opcion; };
		bool get_opcionA2(){ return opcionA2; };
		void set_opcionA2(bool _opcion){ opcionA2 = _opcion; };
		bool get_opcionB1(){ return opcionB1; };
		void set_opcionB1(bool _opcion){ opcionB1 = _opcion; };
		bool get_opcionB2(){ return opcionB2; };
		void set_opcionB2(bool _opcion){ opcionB2 = _opcion; };
		bool get_opcionC(){ return opcionC; };
		void set_opcionC(bool _opcion){ opcionC = _opcion; };
};

#endif
