#pragma once
#include "igvPunto3D.h"
class igvPieza
{
private:
	igvPunto3D posicion[4];
	bool comida;
	GLfloat color[3];
public:
	igvPieza(igvPunto3D _posicion[4], bool _comida, GLfloat _color[3]);
	void mover(igvPunto3D _movimiento);
	void posibleMovimiento();
	void pintar();
	bool getComida(){
		return comida;
	};
	void setComida(bool _comida){
		comida = _comida;
	}
	virtual ~igvPieza();
};

