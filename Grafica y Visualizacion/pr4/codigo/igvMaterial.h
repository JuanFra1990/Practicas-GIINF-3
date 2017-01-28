#ifndef __IGVMATERIAL
#define __IGVMATERIAL

#include <GL/glut.h>

#include "igvColor.h"

class igvMaterial {

	protected:
		// atributos
		igvColor Ka; // coeficiente reflexión luz ambiental
		igvColor Kd; // coeficiente reflexión difuso
		igvColor Ks; // coeficiente reflexión especular
		double   Ns; // exponente de Phong
		
		// Metodos

	public:
		// Constructores por defecto y destructor
		igvMaterial();
		~igvMaterial();

		// Otros constructores
		igvMaterial(const igvMaterial& p);	//de copia
		igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns);

		// Metodos
		void aplicar(void);

		void set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns);


		double getDifuse(){ return Kd[0];	}
		void setDifuse(igvColor _dif);

		double getEspecule() { return Ks[0]; };
		void setEspecule(igvColor _esp);

		double getPhong() { return Ns; };
		void setPhong(double _Ns);

};

#endif

