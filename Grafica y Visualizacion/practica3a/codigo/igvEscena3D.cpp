#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvMallaTriangulos.h"

// Metodos constructores 

igvEscena3D::igvEscena3D () {
	ejes = true;

	// Apartado A: insertar aqu� el c�digo para crear la malla asociada a la escena equivalente a un cubo
	long int numV = 8;
	float coordenadas[24]={-0.5,0.5,0.5, -0.5,-0.5,0.5, 0.5,0.5,0.5, 0.5,-0.5,0.5, -0.5,-0.5,-0.5, -0.5,0.5,-0.5, 0.5,0.5,-0.5, 0.5,-0.5,-0.5};

	long int numT = 12;
	unsigned int vert[36] = { 0, 1, 3, 0, 2, 3, 0, 5, 1, 1, 4, 5, 2, 3, 6, 3, 6, 7, 4, 5, 6, 4, 6, 7, 0,2,5, 2,6,5, 1,3,4, 3,4,7};



	malla=new igvMallaTriangulos(numV,coordenadas,numT,vert);

	
	
}

igvEscena3D::~igvEscena3D() {

}


// Metodos publicos 

void pintar_ejes(void) {
  GLfloat rojo[]={1,0,0,1.0};
  GLfloat verde[]={0,1,0,1.0};
  GLfloat azul[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,verde);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,azul);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}

void igvEscena3D::visualizar(void) {
  GLfloat color_malla[]={0,0.25,0};
	// crear luces

  GLfloat luz0[4] = { 2.0, 2.5, 3.0, 1 }; // luz puntual para visualizar el cubo

	glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	  if (ejes) pintar_ejes();

	  if (malla->get_aparB() && malla->get_aparA()){
		//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena
		  color_malla[0] = 0.3;
		glMaterialfv(GL_FRONT,GL_EMISSION,color_malla);
	  }
	  else {
		  glMaterialfv(GL_FRONT, GL_EMISSION, color_malla);
	  }
		// Apartado A: la siguiente llamada hay que sustituirla por la llamada al m�todo visualizar de la malla
		
		if (malla->get_aparA() || malla->get_aparB()){
			glRotatef(malla->get_X(),1,0,0);
			glRotatef(malla->get_Y(),0,1,0);
			glRotatef(malla->get_Z(),0,0,1);
			malla->visualizar();
		}
		else {
			glutSolidCube(1);
		}

	glPopMatrix (); // restaura la matriz de modelado
}

