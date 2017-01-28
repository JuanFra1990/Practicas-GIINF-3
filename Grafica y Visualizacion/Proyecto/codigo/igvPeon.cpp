#include "igvPeon.h"
#include "igvPieza.h"


igvPeon::igvPeon(igvPunto3D _posicion[4], bool _comida, GLfloat _color[3]) : igvPieza(_posicion, _comida, _color)
{
}

void igvPeon::pintar(){
	GLfloat rojo[] = { 1, 0, 0, 1.0 };
	glPushMatrix();	
	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glScalef(1,0.5,1);
	glutSolidCube(0.5);
		glPushMatrix();
			GLUquadricObj *cuerpopeon = gluNewQuadric();
			glTranslatef(0, 1.0, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(cuerpopeon,0.15, 0.15, 1, 20, 20);
			glPushMatrix();
				GLUquadricObj *cabezapeon = gluNewQuadric();
				//glTranslatef(0, 1, 0);
				gluSphere(cabezapeon,0.2,10,10);
			glPopMatrix();
			gluDeleteQuadric(cuerpopeon);
		glPopMatrix();

	glPopMatrix();
}


igvPeon::~igvPeon()
{
}
