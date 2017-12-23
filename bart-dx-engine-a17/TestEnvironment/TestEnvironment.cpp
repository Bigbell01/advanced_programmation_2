#include "stdafx.h"
#include "TestEnvironment.h"

TestEnvironment::TestEnvironment()
	: currRotation(0.f)
{
	star1 = new Sprite(L"Retro-Star-icon.png");
	star1->GetTransform()->SetPosition(D3DXVECTOR3(-200, 5, 0));

	star2 = new Sprite(L"Retro-Star-icon.png");
	star2->GetTransform()->SetPosition(D3DXVECTOR3(200, 5, 0));
	text = new Text(L"HELLO WORLD !", L"calibri",255,255,255,255);
}

TestEnvironment::~TestEnvironment()
{
	delete star1;
	star1 = nullptr;
	delete star1;
	star2 = nullptr;
	delete text;
	text = nullptr;
}


void TestEnvironment::Update()
{
	currRotation += gGameTimer->GetDeltaTime();

	D3DXVECTOR3 direction = D3DXVECTOR3(
		gInput->keyDown(DIK_RIGHT) ? 1 : 0 + gInput->keyDown(DIK_LEFT) ? -1 : 0,
		0, 0
	);

	star1->GetTransform()->SetPosition(
		star1->GetTransform()->GetPosition() +
		direction * STAR_SPEED * gGameTimer->GetDeltaTime());

	D3DXVECTOR3 size = star2->GetTransform()->GetSize();
	D3DXVECTOR3 center = D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0);

	star2->GetTransform()->SetCenter(center);
	star2->GetTransform()->SetRotation(0, 0, currRotation);
}


