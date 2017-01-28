#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include "igvTablero.h"
#include "igvPeon.h"
#include "igvTorre.h"

// Metodos constructores 

igvEscena3D::igvEscena3D () {
	ejes = true;
	RDIF = 0.0;
	RESP = 0.0;
	POSFOCX = 0.0;
	POSFOCY = 0.0;
	PHONG = 0.0;
	dpulsado=false;
	DPulsado=false;
	spulsado = false;
	SPulsado = false;
	pPulsado = false;
	PPulsado = false;
	arribaPulsado = false;
	abajoPulsado = false;
	izqPulsado = false;
	derPulsado = false;
}

igvEscena3D::~igvEscena3D() {
}


// Metodos publicos 

void pintar_ejes(void) {
  GLfloat rojo[]={1,0,0,1.0};
  GLfloat verde[]={0,1,0,1.0};
  GLfloat azul[]={0,0,1,1.0};

  glMaterialfv(GL_FRONT,GL_EMISSION,rojo);
	glBegin(GL_LINES);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,verde);
	glBegin(GL_LINES);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);
	glEnd();

  glMaterialfv(GL_FRONT,GL_EMISSION,azul);
	glBegin(GL_LINES);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}


void igvEscena3D::visualizar(void) {
	//glShadeModel(GL_FLAT);
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

		// se pintan los ejes
	  if (ejes) pintar_ejes();

		// Ponemos una luz puntual
	  igvPunto3D posPuntual(1.0, 1.0, 1.0);
	  igvColor ambientalPuntual(0.0, 0.0, 0.0, 1.0);
	  igvColor difusoPuntual(1.0, 1.0, 1.0, 1.0);
	  igvColor especularPuntual(1.0, 1.0, 1.0, 1.0);

	  igvFuenteLuz luzPuntual(GL_LIGHT0, posPuntual, ambientalPuntual, difusoPuntual, especularPuntual, 1.0, 0.0, 0.0);


/*Comienza el Proyecto del Ajedrez*/
igvPunto3D posicion[4];
GLfloat color[] = { 1, 0, 0, 1.0 };
igvTablero tablero(6);
igvPeon peon(posicion,false,color);
igvTorre torre(posicion, false, color);

float contador = 0;
glPushMatrix();
	tablero.pintar();
	for (float i = 0.0; i < 8.0; i++){
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
			glTranslatef(1.2,0.1,0.4+contador);
			peon.pintar();
		glPopMatrix();
		contador = contador + 0.8;
	}
	glPushMatrix();
	glTranslatef(0.4, 0.1, 0.4);
		torre.pintar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0.1, 5.8);
	torre.pintar();
	glPopMatrix();
glPopMatrix();


	glPopMatrix (); // restaura la matriz de modelado
}
