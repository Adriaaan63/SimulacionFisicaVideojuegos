#pragma once
#include "SolidoRigido.h"
class Player
{
public:
	Player() {};
	Player(SolidoRigido* solido);
	~Player(){}
	SolidoRigido* getPlayer() const { return solido; };
	void update();
private:
	SolidoRigido* solido;
};

