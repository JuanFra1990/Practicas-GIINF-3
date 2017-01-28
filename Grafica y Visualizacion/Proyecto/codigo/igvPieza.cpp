#include "igvPieza.h"


igvPieza::igvPieza(igvPunto3D _posicion[4], bool _comida, GLfloat _color[3])
{
	posicion[0] = _posicion[0];
	posicion[1] = _posicion[1];
	posicion[2] = _posicion[2];
	posicion[3] = _posicion[3];

	comida = _comida;

	color[0] = _color[0];
	color[1] = _color[1];
	color[2] = _color[2];

}

void igvPieza::mover(igvPunto3D _movimiento){
	
}

void igvPieza::posibleMovimiento() {

}

void igvPieza::pintar(){

}

igvPieza::~igvPieza()
{
}
