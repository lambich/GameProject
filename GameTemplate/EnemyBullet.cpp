#include "EnemyBullet.h"
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  
#include <algorithm> //for min/max functions

EnemyBullet::EnemyBullet(SDL_Texture* tex, double x, double y) : Player(tex, x, y)
{
	isFlipped = true;
	spriteSrcRect = { 0,0,70,80 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
	tempX = m_X;
	m_velX = 0.2f;
	m_velY = 3.5f;

	m_dRadius = 50;

	AddAnimState("BulletStart", AnimStateDefinition(4, 2, 120, true));
	AddAnimState("BulletEnd", AnimStateDefinition(5, 4, 120, true));
}

EnemyBullet::~EnemyBullet()
{

}


void EnemyBullet::Render()
{

	this->SpriteExAnimated::Render(); //invoke the base class's Render()
}


void EnemyBullet::Update()
{
	//this->PlayState("BulletStart");
	//this->UpdateBullet();
	//this->MoveBullet(true);
}
void EnemyBullet::MoveBullet(bool isFwd)
{
	m_X -= 2;

	this->PlayState("BulletStart");



	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();
}
void EnemyBullet::ExploreBullet(int enemyX)
{
	if (m_X >= enemyX) {
		cout << "got hit!!! \n";
		this->PlayState("BulletEnd");

		this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
		this->UpdateDestRect();
	}



}