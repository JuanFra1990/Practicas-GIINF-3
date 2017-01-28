#include <cstdlib>
#include <stdio.h>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
                             // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz () {
	seguir = false;
	interfaz.camara.v = inicial;
//// Apartado D: inicializaci�n de los atributos para realizar la selecci�n mediante lista de impactos
	modo = IGV_VISUALIZAR;
	objeto_seleccionado = -1;
	boton_retenido = false;
}

igvInterfaz::~igvInterfaz () {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
//// Apartado B: establecer los par�metros de la c�mara en funci�n de la escena concreta que se est� modelando
	interfaz.camara.set(IGV_PARALELA, igvPunto3D(6.0,4.0,8),igvPunto3D(0,0,0),igvPunto3D(0,1.0,0),
		                                -1*5, 1*5, -1*5, 1*5, -1*3, 200);
}

void igvInterfaz::configura_entorno(int argc, char** argv,
			                              int _ancho_ventana, int _alto_ventana,
			                              int _pos_X, int _pos_Y,
													          string _titulo){
	// inicializaci�n de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicializaci�n de la ventana de visualizaci�n
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
	switch (key) {
////// Apartado B: incluir aqu� el cambio de la c�mara para mostrar las vistas planta, perfil, alzado o perspectiva
	case 'v':
		if (interfaz.camara.v == inicial)
		{
			interfaz.camara.set(igvPunto3D(0, 5, 0), igvPunto3D(0, 0, 0), igvPunto3D(1, 0, 0));
			interfaz.camara.v = planta;
		}
		else if (interfaz.camara.v == planta)
		{
			interfaz.camara.set(igvPunto3D(5, 0, 0), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0));
			interfaz.camara.v = perfil;
		}
		else if (interfaz.camara.v == perfil)
		{
			interfaz.camara.set(igvPunto3D(0, 0, 5), igvPunto3D(0, 0, 0), igvPunto3D(0, 1, 0));
			interfaz.camara.v = alzado;
		}
		else if (interfaz.camara.v == alzado)
		{
			interfaz.camara.set(igvPunto3D(6.0, 4.0, 8), igvPunto3D(0, 0, 0), igvPunto3D(0, 1.0, 0));
			interfaz.camara.v = inicial;
		}
		interfaz.camara.aplicar();
		break;

////// Apartado C: incluir aqu� la modificaci�n de los grados de libertad del modelo pulsando las teclas correspondientes
		case 'b':
			interfaz.escena.rotarBase(10);
		break;
		case 'B':
			interfaz.escena.rotarBase(-10);
			break;
		case 'I':
			interfaz.escena.rotarBrazoizqx(10);
			interfaz.escena.rotarBrazoizqz(10);
		break;
		case 'K':
			interfaz.escena.rotarBrazoizqx(-10);
			interfaz.escena.rotarBrazoizqz(-10);
			break;
		case 'i':
			interfaz.escena.rotarBrazoizqinfx(10);
			interfaz.escena.rotarBrazoizqinfz(10);
		break;
		case 'k':
			interfaz.escena.rotarBrazoizqinfx(-10);
			interfaz.escena.rotarBrazoizqinfz(-10);
			break;

		case 'd':
			interfaz.escena.rotarBrazoderx(10);
			interfaz.escena.rotarBrazoderz(10);
		break;
		case 'l':
			interfaz.escena.rotarBrazoderx(-10);
			interfaz.escena.rotarBrazoderz(-10);
			break;
		case 'D':
			interfaz.escena.rotarBrazodersupx(10);
			interfaz.escena.rotarBrazodersupz(10);
		break;
		case 'L':
			interfaz.escena.rotarBrazodersupx(-10);
			interfaz.escena.rotarBrazodersupz(-10);
			break;
		case 'q':
			interfaz.escena.rotarPelo1Brazoizq(10);
			break;
		case 'Q':
			interfaz.escena.rotarPelo1Brazoizq(-10);
			break;
		case 'w':
			interfaz.escena.rotarPelo1Brazoizqinf(10);
			break;
		case 'W':
			interfaz.escena.rotarPelo1Brazoizqinf(-10);
			break;
		case 'o':
			interfaz.escena.rotarPelo1Brazoder(10);
			break;
		case 'O':
			interfaz.escena.rotarPelo1Brazoder(-10);
			break;
		case 'p':
			interfaz.escena.rotarPelo1Brazodersup(10);
			break;
		case 'P':
			interfaz.escena.rotarPelo1Brazodersup(-10);
			break;

		case 'a': // activa/desactiva la animaci�n de la escena
      // Apartado F: incluir aqu� la activaci�n de la animaci�n
			interfaz.set_animacion(interfaz.get_animacion() ? false : true);
		break;
		case 'e': // activa/desactiva la visualizacion de los ejes
			interfaz.escena.set_ejes(interfaz.escena.get_ejes()?false:true);
	  break;
    case 27: // tecla de escape para SALIR
      exit(1);
    break;
  }
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
  // dimensiona el viewport al nuevo ancho y alto de la ventana
  // guardamos valores nuevos de la ventana de visualizacion
  interfaz.set_ancho_ventana(w);
  interfaz.set_alto_ventana(h);

	// establece los par�metros de la c�mara y de la proyecci�n
	interfaz.camara.aplicar();
}

void igvInterfaz::set_glutDisplayFunc() {
	GLuint lista_impactos[1024]; // array con la lista de impactos cuando se visualiza en modo selecci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	// se establece el viewport
	glViewport(0, 0, interfaz.get_ancho_ventana(), interfaz.get_alto_ventana());

	// Apartado D: antes de aplicar las transformaciones de c�mara y proyecci�n hay comprobar el modo,
	if (interfaz.modo == IGV_SELECCIONAR) {
	  // Apartado D: si se est� seleccionando se pasa a modo selecci�n de OpenGL y se pasan los par�metros de selecci�n a la c�mara
    interfaz.inicia_seleccion(1024,lista_impactos);
	}

	// aplica las transformaciones en funci�n de los par�metros de la c�mara y del modo (visualizaci�n o selecci�n)
	interfaz.camara.aplicar();

	// visualiza la escena
	interfaz.escena.visualizar();

	if (interfaz.modo == IGV_SELECCIONAR) {
		// Apartado D: salir del modo seleccion y procesar la lista de impactos
		interfaz.finaliza_seleccion(1024,lista_impactos); 
	}	else {
		// refresca la ventana
		glutSwapBuffers();
	}
}

void igvInterfaz::set_glutMouseFunc(GLint boton,GLint estado,GLint x,GLint y) {

// Apartado D: comprobar que se ha pulsado el bot�n izquierdo 
	if (boton == 0) {

		// Apartado D: guardar que el boton se ha presionado o se ha soltado, si se ha pulsado hay que
		// pasar a modo IGV_SELECCIONAR
		if (estado == GLUT_DOWN){
			interfaz.boton_retenido = true;
			interfaz.modo = IGV_SELECCIONAR;

			// Apartado D: guardar el pixel pulsado
			interfaz.cursorX = x;
			interfaz.cursorY = y;
		}
		else {
			interfaz.boton_retenido = false;
		}

		// Apartado D: renovar el contenido de la ventana de vision 
		glutPostRedisplay();
		if (estado == GLUT_UP){
			interfaz.boton_retenido = false;
		}
	}
}

void igvInterfaz::set_glutMotionFunc(GLint x,GLint y) {
	int movimientoX=0, movimientoY=0;
// Apartado E: si el bot�n est� retenido y hay alg�n objeto seleccionado,
// comprobar el objeto seleccionado y la posici�n del rat�n y actualizar
// convenientemente el grado de libertad del objeto correspondiente 
	if (interfaz.boton_retenido){
		movimientoX = x - interfaz.cursorX;
		movimientoY = y - interfaz.cursorY;
	}
	switch (interfaz.objeto_seleccionado) {
	case 1:
		interfaz.escena.rotarBase(movimientoX);
		break;
	case 2:
		interfaz.escena.rotarBrazoizqx(movimientoX);
		interfaz.escena.rotarBrazoizqz(-movimientoY);
		break;
	case 3:
		interfaz.escena.rotarBrazoizqinfx(movimientoX);
		interfaz.escena.rotarBrazoizqinfz(-movimientoY);
		break;
	case 4:
		interfaz.escena.rotarBrazoderx(movimientoX);
		interfaz.escena.rotarBrazoderz(-movimientoY);
		break;
	case 5:
		interfaz.escena.rotarBrazodersupx(movimientoX);
		interfaz.escena.rotarBrazodersupz(-movimientoY);
		break;
	case 6:
		interfaz.escena.rotarPelo1Brazoizq(movimientoX);
		break;
	case 7:
		interfaz.escena.rotarPelo1Brazoizqinf(movimientoX);
		break;
	case 8:
		interfaz.escena.rotarPelo1Brazoder(movimientoX);
		break;
	case 9:
		interfaz.escena.rotarPelo1Brazodersup(movimientoX);
		break;
	}

// Apartado E: guardar la nueva posici�n del rat�n 
	interfaz.cursorX = x;
	interfaz.cursorY = y;

// Apartado E: renovar el contenido de la ventana de vision 
	glutPostRedisplay();
}

void igvInterfaz::set_glutIdleFunc() {
	GLfloat angulo = 90;
	// Apartado F: incluir el c�digo para animar el modelo de la manera m�s realista posible
	if (interfaz.get_animacion()){
		if (!interfaz.seguir){
			interfaz.escena.rotarBrazoizqx(10);
			interfaz.escena.rotarBrazoizqinfx(10);
			interfaz.escena.rotarBrazoderx(-10);
			interfaz.escena.rotarBrazodersupx(-10);
			if (!interfaz.seguir){
				interfaz.seguir = true;
			}
		}
		if (interfaz.seguir){
			interfaz.escena.rotarBrazoizqx(-20);
			interfaz.escena.rotarBrazoizqinfx(-20);
			interfaz.escena.rotarBrazoderx(10);
			interfaz.escena.rotarBrazodersupx(10);
			if (interfaz.seguir){
				interfaz.seguir = false;
			}
		}
		glutPostRedisplay();
	}
}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);

  glutMouseFunc(set_glutMouseFunc); 
  glutMotionFunc(set_glutMotionFunc); 
	glutIdleFunc(set_glutIdleFunc);
}

void igvInterfaz::inicia_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {
	// Apartado D: establecer d�nde se van a almacenar los impactos
	glSelectBuffer(TAMANO_LISTA_IMPACTOS, lista_impactos);

  // Apartado D: pasar a modo de seleccion de OpenGL
	glRenderMode(GL_SELECT);

	// Apartado D: establecer la camara en modo seleccion con los par�metros necesarios para realizar la selecci�n
	// para el alto y el ancho de la ventana de selecci�n probar diferentes tama�os y comprobar la amplitud de la selecci�n
	interfaz.camara.establecerSeleccion(1, 1, cursorX, cursorY);
}

int procesar_impactos(int numero_impactos,GLuint *lista_impactos) {
/* Apartado D: esta funci�n debe devolver el c�digo del objeto seleccionado, que no tiene porque coincidir con el nombre
   asignado con la pila de nombres, y si se han utilizado nombres jer�rquicos hay que tener en cuenta que
	 esta funci�n s�lo devolver un �nico c�digo */

	// Apartado D: recorrer la lista de impactos con numero_impactos impactos,
	// guardar el m�s pr�ximo al observador (minima Z)
	// para empezar, considerar que la m�nima Z tiene un valor de 0xffffffff (el tope del tipo GLuint)

	GLuint zm = 0xffffffff;
	GLuint nombres = 0;
	int recorre = 0;
	int aux = 0;
	for (int i = 0; i<numero_impactos; i++){
		aux = lista_impactos[recorre];
		if (lista_impactos[recorre + 1]<zm){
			zm = lista_impactos[recorre + 1];
			nombres = lista_impactos[recorre + 3];
		}
		recorre = recorre + 3 + aux;
	}

	// Apartado D: a partir de la informaci�n del impacto con la m�nima Z, devolver el c�digo del objeto que le
	// corresponde: como la escena no se almacena en ninguna estructura de datos, para devolver el objeto seleccionado
	// utilizar aqu� directamente los nombres asignados a los objetos de la escena
	if (nombres>0){ return nombres; }

	return(-1);
}

void igvInterfaz::finaliza_seleccion(int TAMANO_LISTA_IMPACTOS, GLuint *lista_impactos) {

	// Apartado D: volver a modo visualizacion OpenGL y obtener el n�mero de impactos  
	int num_impactos = glRenderMode(GL_RENDER);

	// Apartado D: si hay impactos pasar a procesarlos con la funcion int procesar_impactos(numero_impactos,lista_impactos);
	// obteniendo el objeto seleccionado, si lo hay
	if (num_impactos>0){
		objeto_seleccionado = procesar_impactos(num_impactos, lista_impactos);
	}
	else{
		objeto_seleccionado = 0;
	}
	escena.objetoseleccionado(objeto_seleccionado);

	// Apartado D: seleccion terminada, pasar a visualizaci�n normal
	interfaz.modo = IGV_VISUALIZAR;

	// Apartado D: establecer la camara en modo visualizaci�n
	interfaz.camara.establecerVisualizacion();
}
