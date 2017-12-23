#pragma once

#include "Engine.h"
#include "Sprite.h"
#include "Text.h"

class TestEnvironment
	: public Component
{

public:
	TestEnvironment();
	~TestEnvironment();
	
	void Update();

private:
	
	static const int STAR_SPEED = 100;
	Text* text;
	float currRotation;

	Sprite* star1;
	Sprite* star2;
};