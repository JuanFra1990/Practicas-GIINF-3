#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

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


void pintar_quad(float div_x, float div_z) {
	float ini_x = 0.0;
	float ini_z = 0.0;
	float tam_x = 5.0;
	float tam_z = 5.0;

	float divisionX = tam_x / div_x;
	float divisionZ = tam_z / div_z;
	
	glEnable(GL_TEXTURE_2D);
	igvTextura *mapa = new igvTextura("mapa.bmp");
	
	float altura = 0;
	altura = 1.0 / tam_x /2;
	float ancho = 0;
	ancho = 1.0 / tam_z /2;
	
	float contmapx = 0;
	float contmapz = 0;

	
	
	for (float i = 0.0; i <= tam_x; i += divisionX){

		for (float j = 0.0; j <= tam_z; j += divisionZ){
			glNormal3f(0, 1, 0);
			glBegin(GL_QUADS);
			
			glTexCoord2f(contmapx,contmapz);
			glVertex3f(i, 0.0, j);

			glTexCoord2f(contmapx, contmapz+altura);
			glVertex3f(i, 0.0, j + divisionZ);
			
			glTexCoord2f(contmapx+ancho, contmapz + altura);
			glVertex3f(i + divisionX, 0.0, j + divisionZ);

			glTexCoord2f(contmapx + ancho, contmapz);
			glVertex3f(i + divisionX, 0.0, j);

			glEnd();
			contmapz = contmapz + altura;
		}
		contmapx = contmapx + ancho;
	}
	
	

	/* SIN MALLA DE QUADS*/
	/*
	glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(ini_x, 0.0, ini_z);

			glTexCoord2f(0,1);
			glVertex3f(ini_x, 0.0, ini_z + tam_z);

			glTexCoord2f(1, 1);
			glVertex3f(ini_x + tam_x, 0.0, ini_z + tam_z);
			
			glTexCoord2f(1, 0);
			glVertex3f(ini_x + tam_x, 0.0, ini_z);
		glEnd();
		*/
		mapa->aplicar();

		glDisable(GL_TEXTURE_2D);
	
	
}


void igvEscena3D::visualizar(void) {
	//glShadeModel(GL_FLAT);
	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

		// se pintan los ejes
	  if (ejes) pintar_ejes();

		// luces se aplican antes de las transformaciones a la escena para que permanezcan fijas

		// APARTADO B: Define y aplica la luz puntual especificada en el guión de prácticas
	  
		  igvPunto3D posPuntual(1.0, 1.0, 1.0);
		  igvColor ambientalPuntual(0.0, 0.0, 0.0, 1.0);
		  igvColor difusoPuntual(1.0, 1.0, 1.0, 1.0);
		  igvColor especularPuntual(1.0, 1.0, 1.0, 1.0);

		  igvFuenteLuz luzPuntual(GL_LIGHT0, posPuntual, ambientalPuntual, difusoPuntual, especularPuntual, 1.0, 0.0, 0.0);
		 

		// APARTADO F: Define y aplica la luz tipo foco especificada en el guión de prácticas
		  igvPunto3D posF(3.0, 1.0, 1.0);
		  igvPunto3D direccion_F(0, -1, 0);
		  igvColor ambientalF(0.0, 0.0, 0.0, 1.0);
		  igvColor difusoF(1.0, 1.0, 1.0, 1.0);
		  igvColor especularF(1.0, 1.0, 1.0, 1.0);

		  igvFuenteLuz luzFocal(GL_LIGHT1, posF, ambientalF, difusoF, especularF, 1.0, 0.0, 0.0, direccion_F, 30, 10);
		

		  if (POSFOCX == 0.0) POSFOCX = 3.0;
		  if (POSFOCY == 0.0) POSFOCY = 1.0;
		  
		  /*Movimiento del FOCO*/
		  if (getAB()){
			  POSFOCY = POSFOCY - 0.2;
			  igvPunto3D PosicionFoco (POSFOCX, POSFOCY, luzFocal.getPosicion()[2]);
			  luzFocal.setPosicion(PosicionFoco);
			  setAB(false);
		  }
		  if (getAR()){
			  POSFOCY = POSFOCY + 0.2;
			  igvPunto3D PosicionFoco(POSFOCX, POSFOCY, luzFocal.getPosicion()[2]);
			  luzFocal.setPosicion(PosicionFoco);
			  setAR(false);
		  }
		  if (getIZQ()){
			  POSFOCX = POSFOCX - 0.2;
			  igvPunto3D PosicionFoco(POSFOCX, POSFOCY, luzFocal.getPosicion()[2]);
			  luzFocal.setPosicion(PosicionFoco);
			  setIZQ(false);
		  }
		  if (getDER()){
			  POSFOCX = POSFOCX + 0.2;
			  igvPunto3D PosicionFoco(POSFOCX, POSFOCY, luzFocal.getPosicion()[2]);
			  luzFocal.setPosicion(PosicionFoco);
			  setDER(false);
		  }

		/* Apartado D: definir y aplicar las propiedades de material indicadas en el guión de prácticas */
			igvColor Amb(0.15, 0.0, 0.0);
			igvColor Dif(0.5,0.0,0.0);
			igvColor Esp(0.5, 0.0, 0.0);
			float Ph = 120;
			igvMaterial material(Amb, Dif, Esp, Ph);

			if (RESP == 0.0) RESP = 0.15;
			if (RDIF == 0.0) RDIF = 0.5;
			if (PHONG == 0.0) PHONG = 120;

		/* Apartado E: sustituir los valores correspondientes a la componente R del coeficiende difuso, 
		               la componente R del coeficiente especular y el exponente de Phong, por el valor
							del atributo correspondiente de la clase igvEscena */
		  if (getd()){
			  RDIF = RDIF + 0.1;
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  setd(false);
		  }

		  if (getD()){
			  RDIF = RDIF - 0.1;
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  setD(false);
		  }

		  if (gets()){
			  RESP = RESP + 0.1;
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  sets(false);
		  }

		  if (getS()){
			  RESP = RESP - 0.1;
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  setS(false);
		  }

		  
		  if (getp()){
			  PHONG = PHONG + 10;
			  material.setPhong(PHONG);
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  setp(false);
		  }

		  if (getP()){
			  PHONG = PHONG - 10;
			  material.setPhong(PHONG);
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  setP(false);
		  }
		  else {
			  material.setPhong(PHONG);
			  igvColor esp(RESP, Dif[1], Dif[2], Dif[3]);
			  material.setEspecule(esp);
			  igvColor dif(RDIF, Dif[1], Dif[2], Dif[3]);
			  material.setDifuse(dif);
			  igvPunto3D PosicionFoco(POSFOCX, POSFOCY, luzFocal.getPosicion()[2]);
			  luzFocal.setPosicion(PosicionFoco);
		  
		  }
		  
		  
		  
		/* Apartado G: Añade aquí la creación del objeto textura y su aplicación */


		//pintar_quad(1, 1);

		  luzPuntual.aplicar();
		  material.aplicar();
		  luzFocal.aplicar();
		  pintar_quad(14,9);


	glPopMatrix (); // restaura la matriz de modelado
}
