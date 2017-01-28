#include "igvTorre.h"
#include "igvPieza.h"


igvTorre::igvTorre(igvPunto3D _posicion[4], bool _comida, GLfloat _color[3]) : igvPieza(_posicion, _comida, _color)
{
}


void igvTorre::pintar(){
	GLfloat rojo[] = { 1, 0, 0, 1.0 };
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
		glScalef(1, 0.5, 1);
		glutSolidCube(0.5);
		glPushMatrix();
			glTranslatef(0,0.5,0);
			glScalef(1,2,1);
			glutSolidCube(0.45);
				glPushMatrix();
					glTranslatef(0.15,0.25,-0.15);
					glutSolidCube(0.1);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.15, 0.25, +0.15);
					glutSolidCube(0.1);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-0.15, 0.25, -0.15);
					glutSolidCube(0.1);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-0.15, 0.25, 0.15);
					glutSolidCube(0.1);
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}


igvTorre::~igvTorre()
{
}
