#pragma once
class igvTablero
{
private: 
	float tamano;
public:
	igvTablero(float _tamano);
	void pintar();
	float getTamano(){
		return tamano;
	};
	virtual ~igvTablero();
};

