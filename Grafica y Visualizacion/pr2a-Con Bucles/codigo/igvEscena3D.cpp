#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores -----------------------------------

igvEscena3D::igvEscena3D () {ejes = true;}

igvEscena3D::~igvEscena3D() {}


// Metodos publicos ----------------------------------------

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

void pintar_tubo() {
  GLUquadricObj *tubo;
  GLfloat color_tubo[]={0,0,0.5};

  glMaterialfv(GL_FRONT,GL_EMISSION,color_tubo);
  
  tubo=gluNewQuadric();
  gluQuadricDrawStyle(tubo,GLU_FILL);

	glPushMatrix();
	glTranslatef(0,0,-0.5);
  gluCylinder(tubo,0.25,0.25,1,20,20);
	glPopMatrix();

  gluDeleteQuadric(tubo);
}

void igvEscena3D::visualizar(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// luces
	GLfloat luz0[] = { 10, 8, 9, 1 }; // luz puntual
	glLightfv(GL_LIGHT0, GL_POSITION, luz0);
	glEnable(GL_LIGHT0);

	glPushMatrix(); // guarda la matriz de modelado

	// se pintan los ejes
	if (ejes) pintar_ejes();

	// se pintan los objetos de la escena
	GLfloat color_cubo[] = { 0, 0.25, 0 };

	/***************************************************************/
	/* Ejercicio A.1: tubo + cubo sin utilizar la pila de matrices */
	/***************************************************************/
	
	// añadir aquí las transformaciones geométricas del tubo 
	if (opcionA1){
		if (opcionA2 || opcionB1 || opcionB2 || opcionC){
			color_cubo[0] = { 1};
		}
		glTranslatef(1, 2, 0);
		glRotatef(90, 0, 1, 0);
		pintar_tubo();
		glRotatef(-90, 0, 1, 0);
		glTranslatef(-1, -2, 0);

		// añadir aquí las transformaciones geométricas del cubo 

		glTranslatef(0, 2, 0);

		glMaterialfv(GL_FRONT, GL_EMISSION, color_cubo);
		glutSolidCube(1);
		glTranslatef(0, -2, 0);
	}
	/*************************************************************/
	/* Ejercicio A.2: tubo + cubo UTILIZANDO la pila de matrices */
	/* para probar el ejercicio A.2 pon entre comentarios lo     */
	/* implementado anteriormente para el ejercicio A.1          */
	/*************************************************************/
	if (opcionA2) {
		if (opcionA1 || opcionB1 || opcionB2 || opcionC){
			color_cubo[0] = { 0.25 };
			color_cubo[1] = { 1 };
		}
		glPushMatrix();
		// añadir aquí las transformaciones geométricas del tubo
			glTranslatef(1,2,0);
			glRotatef(90,0,1,0);
			pintar_tubo();
		
		glPopMatrix();

		glPushMatrix();

		// añadir aquí las transformaciones geométricas del cubo

			glTranslatef(0,2,0);
			glMaterialfv(GL_FRONT,GL_EMISSION,color_cubo);
			glutSolidCube(1);
		glPopMatrix();
	}
	/**********************************************************************/
	/* Ejercicio B.1: rejilla de cubos sin utilizar la pila de matrices,  */
	/* tres bucles anidados y una única llamada a glutSolidCube()         */
	/* para probar el ejercicio B.1 pon entre comentarios lo implementado */
	/* anteriormente para el ejercicio A.2                                */
	/**********************************************************************/
	if (opcionB1) {
		if (opcionA1 || opcionA2 || opcionB2 || opcionC){
			color_cubo[0] = { 0.25 };
			color_cubo[1] = { 0.5 };
		}
		glTranslatef(-2.5,-2.5,-2.5);
		for(GLfloat i=0; i<4.5; i+=1.5){
			for(GLfloat j=0;j<4.5;j+=1.5){
				for(GLfloat k=0; k<4.5;k+=1.5){
					glTranslatef(j+1,i+1,k+1);
					glMaterialfv(GL_FRONT,GL_EMISSION,color_cubo);
					glutSolidCube(1);
					glTranslatef(-(j+1),-(i+1),-(k+1));
				}
			}
		}
		glTranslatef(2.5, 2.5, 2.5);
	}

	/************************************************************************/
	/* Ejercicio B.2: rejilla de cubos utilizando la pila de matrices, tres */
	/* bucles anidados y una única llamada a glTranslatef()                 */
	/* para probar el ejercicio B.2 debes poner entre comentarios lo        */
	/* implementado anteriormente para el ejercicio B.1                     */
	/************************************************************************/
	if (opcionB2) {
		if (opcionA1 || opcionA2 || opcionB1 || opcionC){
			color_cubo[0] = { 1 };
			color_cubo[1] = { 1 };
		}
		glTranslatef(-2.5,-2.5,-2.5);
		for(GLfloat i=0; i<4.5; i+=1.5){
			for(GLfloat j=0;j<4.5;j+=1.5){
				for(GLfloat k=0; k<4.5;k+=1.5){
					glPushMatrix();
						glTranslatef(j+1,i+1,k+1);
						glMaterialfv(GL_FRONT,GL_EMISSION,color_cubo);
						glutSolidCube(1);
					glPopMatrix();
				}
			}
		}
		glTranslatef(+2.5, +2.5, +2.5);
	}


	/************************************************************************/
	/* Ejercicio C: utilizando la pila de matrices, añadir al resultado del */
	/* ejercicio B.2 las cuatro barras independientemente                   */
	/**********************************************************************/
	if (opcionC) {
		if (opcionA1 || opcionA2 || opcionB1 || opcionB2){
			color_cubo[0] = { 0 };
			color_cubo[1] = { 0 };
			color_cubo[2] = { 0 };
		}
		glTranslatef(-2.5, -2.5, -2.5);
		for (GLfloat i = 0; i < 4.5; i += 1.5){
			for (GLfloat j = 0; j < 4.5; j += 1.5){
				for (GLfloat k = 0; k < 4.5; k += 1.5){
					//Pintar Malla de cubos
					glPushMatrix();
						glTranslatef(j + 1, i + 1, k + 1);
						glMaterialfv(GL_FRONT, GL_EMISSION, color_cubo);
						glutSolidCube(1);
					glPopMatrix();
				}
			}
		}
		glTranslatef(+2.5, +2.5, +2.5);
	//Pintar cuatro tubos

		//Coleccion tubos horizontales
		for (GLfloat i = -2; i <= 1.5; i += 0.5){
			glPushMatrix();
				glTranslatef(1.5, 1.5, i + 0.25);
				pintar_tubo();
			glPopMatrix();
		}

		for (GLfloat i = -2; i <= 1.5; i += 0.5){
			glPushMatrix();
				glTranslatef(1.5, -1.5, i + 0.25);
				pintar_tubo();
			glPopMatrix();
		}

		//Coleccion tubos verticales

		for (GLfloat j = -1.5; j < 2; j += 1.5) {
			for (GLfloat i = -1.5; i < 2; i += 0.5){
				glPushMatrix();
					glRotatef(90, 1, 0, 0);
					glTranslatef(1.5, j, i + 0.25);
					pintar_tubo();
				glPopMatrix();
				glPushMatrix();
					glRotatef(90, 1, 0, 0);
					glTranslatef(1.5, j, i - 0.25);
					pintar_tubo();
				glPopMatrix();
			}
		}
	}
	
	/*
	D) Para facilitar la ejecución de todos los apartados de la práctica, añade el código necesario para que al pulsar las teclas 
	que se indican a continuación se visualice el resultado del apartado correspondiente. Si el resultado de un apartado es el 
	mismo que el del apartado anterior, cambia el color de los objetos para que se vea el cambio:    
	Tecla 1 – apartado A.1  
	Tecla 2 – apartado A.2  
	Tecla 3 – apartado B.1  
	Tecla 4 – apartado B.2  
	Tecla 5 – apartado C 
	*/
	
	glPopMatrix (); // restaura la matriz de modelado
  glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

