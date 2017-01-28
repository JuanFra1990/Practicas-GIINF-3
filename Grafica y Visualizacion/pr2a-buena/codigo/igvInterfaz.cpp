#include <cstdlib>

#include "igvInterfaz.h"

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

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
  glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'e': // activa/desactiva la visualizacion de los ejes
			interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	  break;
	case '1': //Activa el A1
			interfaz.escena.set_opcionA1(interfaz.escena.get_opcionA1() ? false : true);
		break;
	case '2': //Activa el A2
			interfaz.escena.set_opcionA2(interfaz.escena.get_opcionA2() ? false : true);
		break;
	case '3': //Activa el B1
			interfaz.escena.set_opcionB1(interfaz.escena.get_opcionB1() ? false : true);
		break;
	case '4': //Activa el B2
			interfaz.escena.set_opcionB2(interfaz.escena.get_opcionB2() ? false : true);
		break;
	case '5': //Activa el C
			interfaz.escena.set_opcionC(interfaz.escena.get_opcionC() ? false : true);
		break;
    case 27: // tecla de escape para SALIR
      exit(1);
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

  glOrtho(-1*5,1*5,-1*5,1*5,-1*5,200);

  // se define la camara de vision
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	
	gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // vista en perspectiva
	//gluLookAt(1.5,0,0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // vista en planta desde el eje X positivo
}

void igvInterfaz::set_glutDisplayFunc() {
  interfaz.escena.visualizar();
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
