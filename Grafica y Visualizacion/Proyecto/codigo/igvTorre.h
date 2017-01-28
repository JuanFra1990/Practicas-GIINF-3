#pragma once

#include "igvPieza.h"

class igvTorre : public igvPieza
{
public:
	igvTorre(igvPunto3D _posicion[4], bool _comida, GLfloat _color[3]);
	void mover(igvPunto3D _movimiento);
	void pintar();
	virtual ~igvTorre();
};

