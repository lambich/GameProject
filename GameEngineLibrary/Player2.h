#pragma once
#include "SpriteEx.h"
#include <vector>
using namespace std;

class Player2 : public SpriteExAnimated
{
private:

	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;
	double preJumpYVal;

	void MovePlayer(bool isFwd);
	void UpdatePlayer();

	void Jump();

	void OnJumpAnimationComplete();
	void OnSomethingComplete(int x);
public:
	Player2(SDL_Texture* tex, double x, double y);
	~Player2();
	virtual	void Update();
	void Render();
};

