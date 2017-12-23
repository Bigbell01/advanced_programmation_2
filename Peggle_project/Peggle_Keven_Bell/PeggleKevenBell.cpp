#include "stdafx.h"
#include "PeggleKevenBell.h"
#include"iostream"

PeggleKevenBell::PeggleKevenBell()
{
	ballcount = 5;
	direction = D3DXVECTOR3(0.01, 0.01, 0);
	background = new Sprite(L"Sprite_pegle/background_pegle.jpg");
	panier = new Sprite(L"Sprite_pegle/peggle_panier.png");
	/*HUDl = new Sprite(L"Sprite_pegle/HUD_ballshit.png");*/
	Rotator = new Sprite(L"Sprite_pegle/peggle_cannon_rotator.png");
	Canon = new Sprite(L"Sprite_pegle/peggle_cannon.png");
	myball = new Sprite(L"Sprite_pegle/ball1.png");
	Highscoreleft = new Sprite(L"Sprite_pegle/HUD_highscore.png");
	Highscoreright = new Sprite(L"Sprite_pegle/HUD_highscore_right.png");
	Highscoreleft->GetTransform()->SetPosition(-560, -320, 0);
	Highscoreright->GetTransform()->SetPosition(560, -320, 0);
	panier->GetTransform()->SetPosition(0, 320, 0);
	Rotator->GetTransform()->SetPosition(0, -320, 0);
	Canon->GetTransform()->SetPosition(0, -287, 0);
	myball->GetTransform()->SetPosition(0, -277, 0);
	/*HUDl->GetTransform()->SetPosition(-585, 70, 0);*/
	background->GetTransform()->SetPosition(0, 170, 0);
	position = myball->GetTransform()->GetPosition();
	for (int i = 0; i < ballcount; i++)
	{
		balls.push_back(new Sprite(L"Sprite_pegle/ball6.png"));
		balls[i]->GetTransform()->SetPosition((i * 150) - 200, 0, 0);

	}

	int MoveDir = -1;
	bool Is_Started = false;

}
PeggleKevenBell::~PeggleKevenBell()
{
	delete background;
	delete panier;
	delete Rotator;
	delete Canon;
	delete Highscoreleft;
	delete Highscoreright;
	delete myball;

}

void PeggleKevenBell::Update()
{
	myball->GetTransform()->SetPosition(position+ D3DXVECTOR3(0, direction.y*SPEED, 0) * gGameTimer->GetDeltaTime());

	

	for (int i = 0; i < ballcount; i++)
	{
		if (myball->GetIsCollidingWithOtherCircle(balls[i]))
		{
			direction.y = -direction.y;
			/*direction.x = -direction.x;*/
		}
		else
		{
			if (position.x > 625 | position.x < -625)
			{
				direction.x = -direction.x;
			}
			if (position.y > 325 | position.y < -325)
			{
				direction.y = -direction.y;
			}

		}
			position.y += direction.y;
			position.x += direction.x;

	}


	if (panier->GetTransform()->GetPosition().x >= 555)
	{
		MoveDir = -1;


	}
	if (panier->GetTransform()->GetPosition().x <= -555)
	{
		MoveDir = 1;
	}

	panier->GetTransform()->SetPosition(panier->GetTransform()->GetPosition() + D3DXVECTOR3(MoveDir*SPEED, 0, 0) * gGameTimer->GetDeltaTime());


}
