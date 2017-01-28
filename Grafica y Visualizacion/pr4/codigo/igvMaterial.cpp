#include "igvMaterial.h"

// Metodos constructores 

igvMaterial::igvMaterial () {
	
}

igvMaterial::~igvMaterial () {

}

igvMaterial::igvMaterial (const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {
	GLfloat _cambiental[] = { Ka[0], Ka[1], Ka[2] };
	GLfloat _cdifuso[] = { Kd[0], Kd[1], Kd[2] };
	GLfloat _cespecular[] = { Ks[0], Ks[1], Ks[2] };
	GLfloat _emision[] = { 0, 0, 0 };
// APARTADO C
// Aplicar los valores de los atributos del objeto igvMaterial:
// - coeficiente de reflexión de la luz ambiental
	glMaterialfv(GL_FRONT, GL_AMBIENT, _cambiental);
// - coeficiente de reflexión difuso
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _cdifuso);
// - coeficiente de reflesión especular
	glMaterialfv(GL_FRONT,GL_SPECULAR,_cespecular);
// - exponente de Phong
	glMaterialf(GL_FRONT,GL_SHININESS,Ns);

// establecer como color de emisión (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
	glMaterialfv(GL_FRONT,GL_EMISSION,_emision);



}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

void igvMaterial::setDifuse(igvColor _dif){
	Kd = _dif;
}

void igvMaterial::setEspecule(igvColor _esp){
	Ks = _esp;
};
void igvMaterial::setPhong(double _Ns){
	Ns = _Ns;
}


