#pragma once
#include "Player.h"

class Enemy : public Player
{
private:
	double m_velX = 0,
		m_velY = 0;
	int attackStatus = 0; // 0 means not attack and >0 is attack
							// this is later use for enemy defense
public:
	Enemy(SDL_Texture* tex, double x, double y);

	//Over-ride the base player class's Update functionality
	void Update() override;
	void MoveEnemy(bool isFwd); // to move enemy
	int GetAttackStatus() { return attackStatus; } //new method to check if player is attacking
	void setAttackStatus(int a) { attackStatus = a; }
};
