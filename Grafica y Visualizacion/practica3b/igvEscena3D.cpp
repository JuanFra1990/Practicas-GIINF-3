#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

int const base = 1;
int const brazoizq = 2;
int const brazoizqinf = 3;
int const brazoder = 4;
int const brazodersup = 5;

int const pelo1braizq = 6;
int const pelo1braizqinf = 7;
int const pelo1brader = 8;
int const pelo1bradersup = 9;

GLfloat const amarillo[] = { 1, 1, 0 };
GLfloat const azul[] = {0,0,1};



// Metodos constructores 

igvEscena3D::igvEscena3D () {
	ejes = true;

// Apartado B: inicializar los atributos para el control de los grados de libertad del modelo 
	
	base = 0;

	braderechox = 90;
	braderechoz = 0;
	pelo1braderecho = 0;

	braderechosupx = 90;
	braderechosupz = 0;
	pelo1braderechosup = 0;

	braizquierdox = 90;
	braizquierdoz = 0;
	pelo1braizquierdo = 0;


	braizquierdoinfx = 90;
	braizquierdoinfz = 0;
	pelo1braizquierdoinf = 0;

// Apartado D: inicializar el atributo/s que indica/n el objeto seleccionado para pintarlo de otro color

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

//Metodos para dibujar elementos de nuestra figura
void igvEscena3D::dibuja_base(){
	//Esta es fija
	GLUquadricObj *baseq = gluNewQuadric();
	gluQuadricDrawStyle(baseq, GLU_FILL);
	glPushMatrix();
		if (objeto_seleccionado == 1) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
		else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
		//Escalamos para conseguir la primitiva Base
		glScalef(5, 0.25, 5);
		glTranslatef(0, -1, 0);
		glRotatef(90, 1, 0, 0);
		glRotatef(base, 0, 0, 1);
		gluCylinder(baseq, 0.25, 0.25, 4, 20, 20);
	gluDeleteQuadric(baseq);
	glPopMatrix();
}

void igvEscena3D::dibuja_brazoizq(){
	GLUquadricObj *brazoizqq = gluNewQuadric();
	gluQuadricDrawStyle(brazoizqq, GLU_FILL);
	glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	glPushMatrix();
		if (objeto_seleccionado == 2) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
		else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
		glTranslatef(-0.75, -1, 0.5);
		glRotatef(braizquierdox, 1, 0, 0);
		glRotatef(braizquierdoz, 0, 0, 1);
		gluCylinder(brazoizqq, 0.2, 0.2, 2, 20, 20);
		gluDeleteQuadric(brazoizqq);
	
}

void igvEscena3D::dibuja_pelo1_brazoizq(){
	glPushMatrix();
	glTranslatef(0,0,+2);
		if (objeto_seleccionado == 6) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
		else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
		glRotatef(pelo1braizquierdo, 0, 0, 1);
		glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
	
}

void igvEscena3D::dibuja_brazoizqinf(){
	GLUquadricObj *brazoizq = gluNewQuadric();
	gluQuadricDrawStyle(brazoizq, GLU_FILL);
	glPushMatrix();
	if (objeto_seleccionado == 3) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(-0.75, -1, -0.5);
	glRotatef(braizquierdoinfx, 1, 0, 0);
	glRotatef(braizquierdoinfz, 0, 0, 1);
	gluCylinder(brazoizq, 0.2, 0.2, 2, 20, 20);
	
	gluDeleteQuadric(brazoizq);
}

void igvEscena3D::dibuja_pelo1_brazoizqinf(){
	glPushMatrix();
	if (objeto_seleccionado == 7) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(0, 0, +2);
	glRotatef(pelo1braizquierdoinf, 0, 0, 1);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
}




void igvEscena3D::dibuja_brazoder(){
	GLUquadricObj *brazoder = gluNewQuadric();
	gluQuadricDrawStyle(brazoder, GLU_FILL);
	glPushMatrix();
	if (objeto_seleccionado == 4) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(0.75, -1 , -0.5);
	glRotatef(braderechox, 1, 0, 0);
	glRotatef(braderechoz, 0, 0, 1);
	gluCylinder(brazoder, 0.2, 0.2, 2, 20, 20);

	gluDeleteQuadric(brazoder);
}

void igvEscena3D::dibuja_pelo1_brazoder(){
	
	glPushMatrix();
	if (objeto_seleccionado == 8) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(0,0,2);
	glRotatef(pelo1braderecho, 0, 0, 1);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
}


void igvEscena3D::dibuja_brazodersup(){
	GLUquadricObj *brazoder = gluNewQuadric();
	gluQuadricDrawStyle(brazoder, GLU_FILL);
	glPushMatrix();
	if (objeto_seleccionado == 5) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(0.75, -1, 0.5);
	glRotatef(braderechosupx, 1, 0, 0);
	glRotatef(braderechosupz, 0, 0, 1);
	gluCylinder(brazoder, 0.2, 0.2, 2, 20, 20);

	gluDeleteQuadric(brazoder);
}




void igvEscena3D::dibuja_pelo1_brazodersup(){
	glPushMatrix();
	if (objeto_seleccionado == 9) glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
	else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glTranslatef(0,0,2);
	glRotatef(pelo1braderechosup, 0, 0, 1);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
}

void igvEscena3D::dibuja_figura(){
	glInitNames();
		glPushName(base);
			if (objeto_seleccionado == 1)	glMaterialfv(GL_FRONT, GL_EMISSION, amarillo);
			else glMaterialfv(GL_FRONT, GL_EMISSION, azul);
			dibuja_base();
		glPopName();
		glPushName(brazoizq);
			dibuja_brazoizq();
		glPopName();
		glPushName(pelo1braizq);
			dibuja_pelo1_brazoizq();
		glPopName();
		glPushName(brazoder);
			dibuja_brazoder();
		glPopName();
		glPushName(pelo1brader);
			dibuja_pelo1_brazoder();
		glPopName();
		glPushName(brazoizqinf);
			dibuja_brazoizqinf();
		glPopName();
		glPushName(pelo1braizqinf);
			dibuja_pelo1_brazoizqinf();
		glPopName();
		glPushName(brazodersup);
			dibuja_brazodersup();
		glPopName();
		glPushName(pelo1bradersup);
			dibuja_pelo1_brazodersup();
		glPopName();
}

//Metodos para rotar nuestros objetos
void igvEscena3D::rotarBase(float valor){
	if (valor<0){
		if (base >= -360) {
			base -= valor;
		}
	}
	else {
		if (base <= 360){
			base += valor;
		}
	}
}

void igvEscena3D::rotarBrazoizqx(float valor){
	if (valor<0){
			if (braizquierdox >= 60) {
				braizquierdox += valor;
			}
	}
	else {
		if (braizquierdox <= 100){
				braizquierdox += valor;
			}
	}
}

void igvEscena3D::rotarBrazoizqz(float valor){
	if (valor<0){
			if (braizquierdoz >= -30) {
				braizquierdoz += valor;
			}
	}
	else {
			if (braizquierdoz <= 30){
				braizquierdoz += valor;
			}
	}
}

void igvEscena3D::rotarBrazoizqinfx(float valor){
	if (valor<0){
			if (braizquierdoinfx >= 60) {
				braizquierdoinfx += valor;
			}
	}
	else {
		if (braizquierdoinfx <= 100){
				braizquierdoinfx += valor;
		}
	}
}

void igvEscena3D::rotarBrazoizqinfz(float valor){
	if (valor<0){
			if (braizquierdoinfz >= -30) {
				braizquierdoinfz += valor;
			}
	}
	else {
			if (braizquierdoinfz <= 30){
				braizquierdoinfz += valor;
			}
	}
}

void igvEscena3D::rotarBrazoderx(float valor){
	if (valor<0){
			if (braderechox >= 60) {
				braderechox += valor;
			}
	}
	else {
		if (braderechox <= 100){
				braderechox += valor;
			}
	}
}

void igvEscena3D::rotarBrazoderz(float valor){
	if (valor<0){
		if (braderechoz >= -30) {
			braderechoz += valor;
		}
	}
	else {
		if (braderechoz <= 30){
			braderechoz += valor;
		}
	}
}

void igvEscena3D::rotarBrazodersupx(float valor){
	if (valor<0){

		if (braderechosupx >= 60) {
			braderechosupx += valor;
		}
	}
	else {
		if (braderechosupx <= 100){
				braderechosupx += valor;
		}
	}
}

void igvEscena3D::rotarBrazodersupz(float valor){
	if (valor<0){
		if (braderechosupz >= -30) {
			braderechosupz += valor;
		}
	}
	else {
		if (braderechosupz <= 30){
			braderechosupz += valor;
		}
	}
}

void igvEscena3D::rotarPelo1Brazoder(float valor){
	if (valor<0){
		if (pelo1braderecho >= -360) {
			pelo1braderecho += valor;
		}
	}
	else {
		if (pelo1braderecho <= 360){
			pelo1braderecho += valor;
		}
	}
}

void igvEscena3D::rotarPelo1Brazodersup(float valor){
	if (valor<0){
		if (pelo1braderechosup >= -360) {
			pelo1braderechosup += valor;
		}
	}
	else {
		if (pelo1braderechosup <= 360){
			pelo1braderechosup += valor;
		}
	}
}

void igvEscena3D::rotarPelo1Brazoizq(float valor){
	if (valor<0){
		if (pelo1braizquierdo >= -360) {
			pelo1braizquierdo += valor;
		}
	}
	else {
		if (pelo1braizquierdo <= 360){
			pelo1braizquierdo += valor;
		}
	}
}

void igvEscena3D::rotarPelo1Brazoizqinf(float valor){
	if (valor<0){
		if (pelo1braizquierdoinf >= -360) {
			pelo1braizquierdoinf += valor;
		}
	}
	else {
		if (pelo1braizquierdoinf <= 360){
			pelo1braizquierdoinf += valor;
		}
	}
}


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4]={5.0,5.0,5.0,1}; // luz puntual  
	glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	  if (ejes) pintar_ejes();

		//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena

///// Apartado B: aquí hay que añadir la visualización del árbol del modelo utilizando la pila de matrices de OpenGL
/////             se recomienda crear una método auxiliar que encapsule todo el código para la visualización
/////             del modelo, dejando aquí sólo la llamada a ese método. En el apartado D hay que añadir los nombres
/////		          a las partes móviles del objeto mediante la pila de nombres y el control del objeto seleccionado 
/////							para colorearlo en amarillo

	  dibuja_figura();

	glPopMatrix (); // restaura la matriz de modelado
}

