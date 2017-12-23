#pragma once

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "resource.h"

class PeggleKevenBell
	:public Component
{
public:
	PeggleKevenBell();
	~PeggleKevenBell();
	void Update();


private:
	static const int SPEED = 200;
	int MoveDir = 1;
	int ballcount;
	bool Is_Started;
	D3DXVECTOR3 position;
	Sprite* panier;
	Sprite* background;
	/*Sprite* HUDl;*/
	Sprite* Rotator;
	Sprite* Canon;
	Sprite* Highscoreleft;
	Sprite* Highscoreright;
	std::vector <Sprite*> balls;
	Sprite* myball;
	D3DXVECTOR3 direction;
};