#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include "igvMallaTriangulos.h"

// Metodos constructores 

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos){
	aparA=false;
	aparB=false;
	aparD=false;
	
	num_vertices = _num_vertices;
	vertices = new float [num_vertices*3];
	 for(int i=0;i<num_vertices*3;i++) {
        vertices[i] = _vertices[i];
	}
	
	num_triangulos = _num_triangulos;
	triangulos = new unsigned int[num_triangulos*3];
	for (int i=0;i<num_triangulos*3;i++) {
        triangulos[i] = _triangulos[i];
	}

	normales = new float[num_vertices * 3];
	 for (int i = 0; i < _num_triangulos; i=i+3){
		
		GLint v0[3], v1[3], v2[3];
		v0[0]=vertices[triangulos[i]*3];
		v0[1]=vertices[triangulos[i]*3+1];
		v0[2]=vertices[triangulos[i]*3+2];

		v1[0]=vertices[triangulos[i+1]*3];
		v1[1]=vertices[triangulos[i+1]*3+1];
		v1[2]=vertices[triangulos[i+1]*3+2];

		v2[0]=vertices[triangulos[i+2]*3];
		v2[1]=vertices[triangulos[i+2]*3+1];
		v2[2]=vertices[triangulos[i+2]*3+2];

		GLfloat Qx, Qy, Qz, Px, Py, Pz;

		Qx = v1[0]-v0[0];
		Qy = v1[1]-v0[1];
		Qz = v1[2]-v0[2];
		Px = v2[0]-v0[0];
		Py = v2[1]-v0[1];
		Pz = v2[2]-v0[2];

		GLfloat normalx = Py*Qz - Pz*Qy;
		GLfloat normaly = Pz*Qx - Px*Qz;
		GLfloat normalz = Px*Qy - Py*Qx;

		normales[triangulos[i]]=normalx;
		normales[triangulos[i]+1]=normaly;
		normales[triangulos[i]+2]=normalz;

		normales[triangulos[i+1]]=normalx;
		normales[triangulos[i+1]+1]=normaly;
		normales[triangulos[i+1]+2]=normalz;

		normales[triangulos[i+2]]=normalx;
		normales[triangulos[i+2]+1]=normaly;
		normales[triangulos[i+2]+2]=normalz;
	 }

	x=y=z=0;


}




igvMallaTriangulos::~igvMallaTriangulos() {
	delete [] vertices;
	delete [] triangulos;
	delete [] normales;
}


// Metodos publicos 

void igvMallaTriangulos::visualizar(void) {
	
	/* Apartado A: visualización triángulo a triángulo*/
	if (aparA && !aparD){
		for(int i=0;i<num_triangulos*3;i+=3){
        
			glBegin(GL_TRIANGLES);
			
				glVertex3f(vertices[triangulos[i]*3],vertices[triangulos[i]*3+1],vertices[triangulos[i]*3+2]);
				glVertex3f(vertices[triangulos[i+1]*3],vertices[triangulos[i+1]*3+1],vertices[triangulos[i+1]*3+2]);
				glVertex3f(vertices[triangulos[i+2]*3],vertices[triangulos[i+2]*3+1],vertices[triangulos[i+2]*3+2]);

			glEnd(); 
		}
	}
	/* Apartado B: Visualización con array de vértices y en apartado D añadir array de normales */
	if (aparB && !aparD) {

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,vertices);
		glDrawElements(GL_TRIANGLES,num_triangulos*3,GL_UNSIGNED_INT,triangulos);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	if (aparD && aparB) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glNormalPointer(GL_FLOAT, 0, normales);
		glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	if (aparD && aparA){
		for (int i = 0; i<num_triangulos * 3; i += 3){

			glBegin(GL_TRIANGLES);
			glNormal3f(normales[triangulos[i]],normales[triangulos[i]+1],normales[triangulos[i]+2]);
			glVertex3f(vertices[triangulos[i] * 3], vertices[triangulos[i] * 3 + 1], vertices[triangulos[i] * 3 + 2]);
			glNormal3f(normales[triangulos[i+1]],normales[triangulos[i+1]+1],normales[triangulos[i+1]+2]);
			glVertex3f(vertices[triangulos[i + 1] * 3], vertices[triangulos[i + 1] * 3 + 1], vertices[triangulos[i + 1] * 3 + 2]);
			glNormal3f(normales[triangulos[i+2]],normales[triangulos[i+2]+1],normales[triangulos[i+2]+2]);
			glVertex3f(vertices[triangulos[i + 2] * 3], vertices[triangulos[i + 2] * 3 + 1], vertices[triangulos[i + 2] * 3 + 2]);

			glEnd();
		}
	}
}

