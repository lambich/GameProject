#pragma once
//#include "SpriteEx.h"
#include "Player.h"

class EnemyBullet : public Player
{
private:
	double tempX = 0, m_velX = 0,
		m_velY = 0,
		m_velMax = 10;


public:
	EnemyBullet(SDL_Texture* tex, double x, double y);
	~EnemyBullet();
	virtual	void Update();
	void Render();
	void MoveBullet(bool isFwd);
	void ExploreBullet(int enemyX);
	double GetBulletX() { return m_X; } //new method to check if player is attacking
	void setBulletX(double a) { m_X = a; }
};

