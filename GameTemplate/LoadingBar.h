#pragma once
#include "SDL.h"
#include "../GameEngineLibrary/SpriteEx.h"

class LoadingBar : public SpriteExAnimated
{
private:

	void UpdateBar();
public:

	LoadingBar(SDL_Texture* tex, double x, double y);
	~LoadingBar();
	//void onProgressBarComplete();
	void Update();
	void Render();
};

