#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>

#include "igvMallaTriangulos.h"

class igvEscena3D {
	protected:
		// Atributos

		bool ejes;

	public:
		// atributos públicos
		igvMallaTriangulos *malla; // malla de triángulos asociada a la escena

		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar();

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
};

#endif
