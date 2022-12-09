#pragma once
#include "Player.h"
#include "SDL_mixer.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "ScreenState.h"
#include "GameManager.h"
#include "AudioManager.h"

#include <iostream>
using namespace std;

class GameState : public ScreenState
{
protected:
	int pH = 100;//player's health
	int eH = 100;//enemy's health
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* badSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex

	AudioManager* music; //Audio theme

	SpriteEx* bg;

	Player* player;
	Enemy* enemy;
	Bullet* bullet;
	EnemyBullet* enemyBullet;

	int enemySelection;
	//int pH = GameManager::Instance()->GetEnemyHealth();
	//int eH = GameManager::Instance()->GetPlayerHealth();

	//int playerApproachEnemy = 0;
	int counter = 0; //counter for how long player is not coming near enemy

	bool hit = false;
	bool hitPlayer = false;
	bool didHit = false;

	bool passPlayer = false;
	bool hadouken = false;
	bool inDistancePlayerEnemy = false;
public:
	GameState() {}
	void Update();
	void Render();
	virtual void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}
	int randomEnemy(int selection);
	int randomNumber();
	void CheckCollision();
	void ChechPlayerMovement();
	void PlayerGotHit(int h) { pH = pH - h; }
	int GetPlayerHealth() {
		return pH;
	}
	void EnemyGotHit(int h) { eH = eH - h; }
	int GetEnemyHealth() {
		return eH;
	}
	void restorePlayersStatus() {
		eH = 100;
		pH = 100;
	}
};

