#pragma once

#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include "LoadingBar.h"

using namespace std;

class LoadingScreen : public ScreenState
{
protected:
	SDL_Texture* loadingSprite;
	vector<Button*> m_vButtons;
	enum btn { play, exit };
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex

	LoadingBar* loadingBar;

	int delayTime = 100;
public:
	LoadingScreen() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}
};

