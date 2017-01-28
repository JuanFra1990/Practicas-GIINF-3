#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#include <GL/glut.h>

class igvMallaTriangulos {
	protected:
		// Atributos

		long int num_vertices; // número de vértices de la malla de triángulos
		float *vertices; // array con las (num_vertices * 3) coordenadas de los vértices
		float *normales; // array con las (num_vertices * 3) coordenadas de la normal a cada vértice (para el calculo y su posterior aplicacion)

		long int num_triangulos; // número de triángulos de la malla de triángulos
		unsigned int *triangulos; // array con los (num_triangulos * 3) índices a los vértices de cada triángulo

		// Apartado C: Añadir aquí los atributos con los ángulos de rotación en X, Y y Z.
		float x,y,z;

		//Apartado E: Para facilitar la ejecucion de los distintos apartados
		bool aparA , aparB , aparD ;


	public:
		// Constructor y destructor
		// Apartado A: constructor de la malla de triángulos
		igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos);
    
		// Apartado D: genera una esfera centrada en el origen de radio r y con div_u divisiones en u y div_v divisiones en v
		igvMallaTriangulos(float r, int div_u, int div_v); 
		                                                   

		~igvMallaTriangulos();

		// Métodos
		// método con las llamadas OpenGL para visualizar la malla de triángulos
    void visualizar();

		// Apartado C: métodos para incrementar los ángulos en X, y Z
		void rotarX(float angulo){x += angulo;};
		void rotarY(float angulo){y += angulo;};
		void rotarZ(float angulo){z += angulo;};


		// Apartado C: métodos para obtener los valores de los ángulos en X, y y Z
		float get_X() {return x;};
		float get_Y() {return y;};
		float get_Z() {return z;};

		//Apartado E: metodos SET y GET de las variables aparA, aparB y aparC

		void set_aparA(bool _aparA){ aparA = _aparA; };
		void set_aparB(bool _aparB){ aparB = _aparB; };
		void set_aparD(bool _aparD){ aparD = _aparD; };

		bool get_aparA(){ return aparA; };
		bool get_aparB(){ return aparB; };
		bool get_aparD(){ return aparD; };

};

#endif
