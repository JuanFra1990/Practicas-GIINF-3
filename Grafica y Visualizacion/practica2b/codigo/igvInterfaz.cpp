#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {
	contador = 0;
	perspective = false;
}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	// crear cámaras
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(3.0,2.0,4),igvPunto3D(0,0,0),igvPunto3D(0,1.0,0),
		                                -1*3, 1*3, -1*3, 1*3, -1*3, 200);
}

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

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {

	/* IMPORTANTE: en la implementación de este método hay que cambiar convenientemente el estado 
	   de los objetos de la aplicación, pero no hacer llamadas directas a funciones de OpenGL */
	switch (key) {
    case 'p': // cambia el tipo de proyección de paralela a perspectiva y viceversa
		if (!interfaz.get_perspective()){
			interfaz.camara.set(IGV_PERSPECTIVA, igvPunto3D(3,2,4),igvPunto3D(0,0,0),igvPunto3D(0,1,0),
			50, 1, 0.5, 100);
			interfaz.camara.aplicar();
			interfaz.set_perspective(true);
		} else {
			interfaz.camara.set(IGV_PARALELA, igvPunto3D(3.0, 2.0, 4), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
				-1 * 3, 1 * 3, -1 * 3, 1 * 3, -1 * 3, 200);
			interfaz.camara.aplicar();
			interfaz.set_perspective(false);
		}
		break;

    case 'v': // cambia la posición de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
		if (interfaz.get_contador() == 0){
		//Alzado
			interfaz.camara.set(igvPunto3D(3, 0, 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0));
			interfaz.camara.aplicar();
			interfaz.set_contador();
		}
		else if (interfaz.get_contador() == 1){
		//Perfil
			interfaz.camara.set(igvPunto3D(0, 0, 2), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0));
			interfaz.camara.aplicar();
			interfaz.set_contador();
		}
		else if (interfaz.get_contador() == 2) {
			//Planta
			interfaz.camara.set(igvPunto3D(0, 2, 0), igvPunto3D(0, 0, 0), igvPunto3D(1, 0, 0));
			interfaz.camara.aplicar();
			interfaz.set_contador();
		}
		else {
			interfaz.camara.set(IGV_PARALELA, igvPunto3D(3.0, 2.0, 4), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0),
				-1 * 3, 1 * 3, -1 * 3, 1 * 3, -1 * 3, 200);
			interfaz.camara.aplicar();
			interfaz.set_contador_0();
		}
		break;
    case '+': // zoom in
			interfaz.camara.zoom(-5);
			interfaz.camara.aplicar();
		break;
    case '-': // zoom out
			interfaz.camara.zoom(5);
			interfaz.camara.aplicar();
		break;
    case 'c': // incrementar la distancia del plano cercano
		interfaz.camara.setPlano(0.9);
		interfaz.camara.aplicar();
	  break;
    case 'C': // decrementar la distancia del plano cercano
		interfaz.camara.setPlano(-0.9);
		interfaz.camara.aplicar();
	  break;
    case '9': // cambiar a formato 16:9 con deformación
		interfaz.camara.set_panoramico(interfaz.camara.get_panoramico() ? false : true);
		
	  break;
		case 'e': // activa/desactiva la visualizacion de los ejes
			interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	  break;
    case 27: // tecla de escape para SALIR
      exit(1);
    break;
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision y redibuja la escena
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer
	if (interfaz.camara.get_panoramico()){
		glViewport(0, (interfaz.alto_ventana - interfaz.ancho_ventana*(9.0 / 16.0)) / 2, interfaz.ancho_ventana, interfaz.ancho_ventana*(9.0 / 16.0));
		//visualiza la escena
		interfaz.escena.visualizar();
	}
	else {
		glViewport(0, 0, interfaz.ancho_ventana, interfaz.alto_ventana);
		//visualiza la escena
		interfaz.escena.visualizar();
	}

	// refresca la ventana
	glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo

	
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
