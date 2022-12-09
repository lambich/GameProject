#include "Player.h"
#include "GameEngine.h"
#include <algorithm> //for min/max functions

Player::Player(SDL_Texture* tex, double x, double y)
	: SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{

	spriteSrcRect = { 0,0,70,80 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };

	m_velX = 0.2f;
	m_velY = 3.5f;

	m_dRadius = 50;

	AddAnimState("Hadouken", AnimStateDefinition(0, 4, 120));
	AddAnimState("Idle", AnimStateDefinition(1, 4, 120, true));
	AddAnimState("Punch", AnimStateDefinition(2, 3, 120));
	AddAnimState("Move", AnimStateDefinition(3, 5, 120, true));

	AddAnimState("Kick", AnimStateDefinition(6, 5, 120));
	AddAnimState("Roundhouse", AnimStateDefinition(7, 5, 120));
	AddAnimState("Jump", AnimStateDefinition(8, 7, 120));
	AddAnimState("Crouch", AnimStateDefinition(9, 1, 120));

	animStates["Jump"].RegisterOnAnimCompleteCallback(
		std::bind(&Player::OnJumpAnimationComplete, this));


}

Player::~Player()
{
	/*for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = nullptr;
	}
	m_vBullets.clear();
	m_vBullets.shrink_to_fit();*/

}


void Player::Render()
{
	//for (int i = 0; i < (int)m_vBullets.size(); i++)
	//	m_vBullets[i]->Render();
	this->SpriteExAnimated::Render(); //invoke the base class's Render()

}


void Player::Update()
{
	this->UpdateBullets();
	this->UpdatePlayer();
}


void Player::MovePlayer(bool isFwd)
{
	if (isFwd)
		m_X += m_velX;
	else
		m_X -= m_velX;

	this->PlayState("Move");
}


void Player::Jump()
{
	if (m_iFrame < 3)
	{
		m_Y -= m_velY;
	}
	else if (m_iFrame > 3)
	{
		m_Y += m_velY;

		if (m_Y > preJumpYVal)
			m_Y = preJumpYVal;
	}

}

void Player::OnJumpAnimationComplete()
{
	cout << "Jump animation is completed. reset player to preJumpY val\n";
	if (m_Y > preJumpYVal)
		m_Y = preJumpYVal;

}


void Player::UpdatePlayer()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_D)) {
		MovePlayer(true);
		attackStatus = 0;
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_A)) {
		MovePlayer(false);
		attackStatus = 0;
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_SPACE))
	{
		if (this->currentState != "Jump")
			preJumpYVal = m_Y;

		attackStatus = 0;
		this->PlayState("Jump");

	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_P))
	{
		//to-do:: play punch animation
		this->PlayState("Punch");
		attackStatus = 1;

	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_R))
	{
		this->PlayState("Roundhouse");
		attackStatus = 2;
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_K))
	{
		this->PlayState("Kick");
		attackStatus = 3;

	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_H))
	{
		this->PlayState("Hadouken");
		this->SpawnBullet();
		attackStatus = 4;

	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_C))
	{
		this->PlayState("Crouch");
		attackStatus = 0;

	}
	else //play idle animation
	{
		this->PlayState("Idle");
		attackStatus = 0;
	}


	if (currentState == "Jump")
		Jump();


	spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();

}

void Player::UpdateBullets()
{
	/*if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_L)) {
		
	}
	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		m_vBullets[i]->Update();

		if (m_vBullets[i]->m_X < 0 || m_vBullets[i]->m_X >
			1024 ||
			m_vBullets[i]->m_Y < 0 || m_vBullets[i]->m_Y > 768)
		{
			delete m_vBullets[i];
			m_vBullets[i] = nullptr;
			m_vBullets.erase(m_vBullets.begin() + i);
		}
	}
	m_vBullets.shrink_to_fit();*/

}

void Player::SpawnBullet()
{
	//converting the player spaceship's angle to deltaX and deltaY 
	float dx = (float)cos((angle - 90) * M_PI / 180);
	float dy = (float)sin((angle - 90) * M_PI / 180);

	//m_vBullets.push_back(new Bullet(texture, m_X, m_Y, angle, -dy, dx));

}

int Player::GetAttackStatus() { // getter to get attack status
	return attackStatus;
}
void Player::tempUpdate()
{

	this->tempUpdatePlayerWithOutMove();
}

void Player::tempUpdatePlayerWithOutMove()
{

	this->PlayState("Idle");


	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();

}