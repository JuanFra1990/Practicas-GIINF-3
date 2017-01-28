#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <GL/glut.h>

#include "igvFuenteLuz.h"
#include "igvMallaTriangulos.h"

class igvEscena3D {
	protected:
		// Atributos

		bool ejes;

	public:
		// atributos públicos
		igvMallaTriangulos *malla; // malla de triángulos asociada a la escena
		//Necesario para el apartado E
		bool dpulsado;
		bool DPulsado;
		bool spulsado;
		bool SPulsado;
		bool pPulsado;
		bool PPulsado;
		bool arribaPulsado;
		bool abajoPulsado;
		bool izqPulsado;
		bool derPulsado;
		double RDIF;
		double RESP;
		double PHONG;
		double POSFOCX;
		double POSFOCY;
		// Constructores por defecto y destructor
		igvEscena3D();
		~igvEscena3D();

		// Metodos estáticos

		// Métodos
		// método con las llamadas OpenGL para visualizar la escena
    void visualizar();

		bool get_ejes() {return ejes;};
		void set_ejes(bool _ejes){ejes = _ejes;};
		bool getd() {return dpulsado;};
		void setd(bool _dpulsado) {dpulsado=_dpulsado;};
		bool getD() {return DPulsado;};
		void setD(bool _DPulsado) {DPulsado=_DPulsado;};
		bool gets() { return spulsado; };
		void sets(bool _spulsado) { spulsado = _spulsado; };
		bool getS() { return SPulsado; };
		void setS(bool _SPulsado) { SPulsado = _SPulsado; };
		bool getp() { return pPulsado; };
		void setp(bool _pPulsado) { pPulsado = _pPulsado; };
		bool getP() { return PPulsado; };
		void setP(bool _PPulsado) { PPulsado = _PPulsado; };
		bool getAR() { return arribaPulsado; };
		void setAR(bool _ArribaPulsado) { arribaPulsado = _ArribaPulsado; };
		bool getAB() { return abajoPulsado; };
		void setAB(bool _abajoPulsado) { abajoPulsado = _abajoPulsado; };
		bool getIZQ() { return izqPulsado; };
		void setIZQ(bool _izqPulsado) { izqPulsado = _izqPulsado; };
		bool getDER() { return derPulsado; };
		void setDER(bool _derPulsado) { derPulsado = _derPulsado; };
};

#endif
