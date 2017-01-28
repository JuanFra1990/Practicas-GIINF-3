#include <cstdlib>
#include <stdio.h>

#include "igvTablero.h"
#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"



igvTablero::igvTablero(float _tamano)
{
	tamano = _tamano;
}

void igvTablero::pintar(){

	//Dibujamos una base al QUADS
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(3, -0.25, 3);
	glScalef(1, 0.08, 1);
	glutSolidCube(tamano);
	glPopMatrix();

	float ini_x = 0.0;
	float ini_z = 0.0;
	float div = 24.0;


	float divisionX = tamano/div;
	float divisionZ = tamano/div;

	float altura = 0;
	altura = 1.0 / div;
	float ancho = 0;
	ancho = 1.0 / div;

	float contmapx = 0.0;
	float contmapz = 1.0;

	for (float i = 0.0; i <= tamano; i += divisionX){
		contmapz = 1.0;
		for (float j = 0.0; j <= tamano; j += divisionZ){

			glNormal3f(0, 1, 0);
			glBegin(GL_QUADS);

			glTexCoord2f(contmapx, contmapz);
			glVertex3f(i, 0.0, j);

			glTexCoord2f(contmapx, contmapz - altura);
			glVertex3f(i, 0.0, j + divisionZ);

			glTexCoord2f(contmapx + ancho, contmapz - altura);
			glVertex3f(i + divisionX, 0.0, j + divisionZ);

			glTexCoord2f(contmapx + ancho, contmapz);
			glVertex3f(i + divisionX, 0.0, j);

			glEnd();
			contmapz = contmapz - altura;
		}
		contmapx = contmapx + ancho;
	}
}

igvTablero::~igvTablero()
{
}
