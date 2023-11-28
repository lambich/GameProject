#pragma once

#include "../GameEngineLibrary/SpriteEx.h"
//#include "Bullet.h"
#include <vector>
using namespace std;


class Player : public SpriteExAnimated
{
private:
	//vector<Bullet*> m_vBullets;
	void UpdateBullets();
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;
	double preJumpYVal;
	int attackStatus = 0; // 0 means not attack and >0 is attack
							// this is later use for enemy defense

	void MovePlayer(bool isFwd);
	void UpdatePlayer();
	void tempUpdatePlayerWithOutMove();

	void Jump();

	void OnJumpAnimationComplete();
	//void OnSomethingComplete(int x);
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	virtual void tempUpdate();
	virtual	void Update();
	void Render();

	//	void SetIdle();
	int GetAttackStatus(); //new method to check if player is attacking

	void SpawnBullet();

	//vector<Bullet*>& GetBullets()
	//{
	//	return m_vBullets;
	//}
};