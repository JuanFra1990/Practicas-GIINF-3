#include <cstdlib>
#include "math.h""

#include "igvInterfaz.h"
#include <iostream>

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_ancho_ventana,_alto_ventana);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_titulo.c_str());

	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // establece el color de fondo de la ventana

}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // tecla de escape para SALIR
      exit(1);
	case 101:
		interfaz.SetEjes();
    break;
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  glViewport(0,0,(GLsizei) w,(GLsizei) h);

  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

  // establece el tipo de proyeccion a utilizar
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-1,1,-1,1,-1,200);

  // se define la camara de vision
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void igvInterfaz::set_glutDisplayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
  glPushMatrix(); // guarda la matriz de modelado

	// Apartado A: pintar los ejes

   
  if (!interfaz.getEjes()){
		glBegin(GL_LINES);

		 glColor3f(1,0,0);
		 glVertex3d(100,0,0);
		 glVertex3d(-100,0,0);


		 glColor3f(0,1,0);
		 glVertex3d(0,100,0);
		 glVertex3d(0,-100,0);

		  glColor3f(0,0,1);
		 glVertex3d(0,0,100);
		 glVertex3d(0,0,-100);

		 glEnd();
  };

 // Apartado B: visualizar primitiva cubo en modo alambre
 
 glColor3f(0,0,0);
 glutWireCube(1);
 

	// apartado D: cubo hecho con líneas
 
 glColor3f(1,1,0);
 glBegin(GL_LINES);

	//Cara 1 (Frontal)
	glVertex3d(-0.375,0.375,0.375);
	glVertex3d(0.375,0.375,0.375);
	
	glVertex3d(-0.375,0.375,0.375);
	glVertex3d(-0.375,-0.375,0.375);

	glVertex3d(-0.375,-0.375,0.375);
	glVertex3d(0.375,-0.375,0.375);

	glVertex3d(0.375,-0.375,0.375);
	glVertex3d(0.375,0.375,0.375);
	
	//Cara 2 (Lateral)

	glVertex3d(0.375,0.375,0.375);
	glVertex3d(0.375,0.375,-0.375);

	glVertex3d(0.375,-0.375,0.375);
	glVertex3d(0.375,-0.375,-0.375);

	glVertex3d(0.375,0.375,-0.375);
	glVertex3d(0.375,-0.375,-0.375);

	//Cara 3 (Trasera)

	glVertex3d(0.375,0.375,-0.375);
	glVertex3d(-0.375,0.375,-0.375);

	glVertex3d(0.375,-0.375,-0.375);
	glVertex3d(-0.375,-0.375,-0.375);

	glVertex3d(-0.375,0.375,-0.375);
	glVertex3d(-0.375,-0.375,-0.375);

	//Cara 4 (Lateral Izq)

	glVertex3d(-0.375,0.375,-0.375);
	glVertex3d(-0.375,0.375,0.375);

	glVertex3d(-0.375,-0.375,-0.375);
	glVertex3d(-0.375,-0.375,0.375);

glEnd();
	// apartado E: cubo hecho con triángulos
glBegin(GL_TRIANGLES);

	//Cara Frontal
	glColor3f(1,0,0);
	glVertex3d(0.25,0.25,0.25);
	glVertex3d(-0.25,-0.25,0.25);
	glVertex3d(-0.25,0.25,0.25);

	glColor3f(1,1,0);
	glVertex3d(0.25,0.25,0.25);
	glVertex3d(-0.25,-0.25,0.25);
	glVertex3d(0.25,-0.25,0.25);
	
	//Cara Lateral

	glColor3f(0.5,0.5,0);
	glVertex3d(0.25,0.25,0.25);
	glVertex3d(0.25,-0.25,0.25);
	glVertex3d(0.25,0.25,-0.25);

	glColor3f(0,0.5,0.5);
	glVertex3d(0.25,0.25,-0.25);
	glVertex3d(0.25,-0.25,0.25);
	glVertex3d(0.25,-0.25,-0.25);

	//Cara Superior
	
	glColor3f(0.5,0.25,0.25);
	glVertex3d(0.25,0.25,-0.25);
	glVertex3d(-0.25,0.25,0.25);
	glVertex3d(-0.25,0.25,-0.25);

	glColor3f(0.25,0.5,0.25);
	glVertex3d(-0.25,0.25,0.25);
	glVertex3d(0.25,0.25,-0.25);
	glVertex3d(0.25,0.25,0.25);
	


glEnd();




	// apartado F: círculo hecho con triángulos
GLdouble numerotriangulos = 25;
GLdouble angulo = 360 / numerotriangulos;
GLdouble radianes = angulo * 0.0174533;
GLdouble tmp1 = 0.5;
GLdouble tmp2 = 0;
GLdouble x = cos(radianes)*0.5;
GLdouble y = sin(radianes)*0.5;

for (int i = 1; i<=numerotriangulos+1; i++){
	glBegin(GL_TRIANGLES);

		glColor3f(i*0.001,i*0.034,i*0.005);
		glVertex3d(0, 0, 0.5);
		glVertex3d(tmp1, tmp2, 0.5);
		glVertex3d(x, y, 0.5);
	
	glEnd();

		tmp1 = x;
		tmp2 = y;

		y = sin(i*radianes)*0.5;
		x = cos(i*radianes)*0.5;
}






  glPopMatrix (); // restaura la matriz de modelado
  glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
