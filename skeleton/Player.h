#pragma once
#include "SolidoRigido.h"
class Player
{
public:
	Player() {};
	Player(SolidoRigido* solido);
	~Player(){
		delete solido;
	}
	SolidoRigido* getPlayer() const { return solido; };
	void update();
private:
	SolidoRigido* solido;
};

