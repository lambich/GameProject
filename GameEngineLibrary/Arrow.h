#pragma once

#include "SpriteEx.h"
#include <vector>
using namespace std;

class Arrow : public SpriteExAnimated
{
private:
	int selection = 1;
	void UpdateArrow();
public:

	Arrow(SDL_Texture* tex, double x, double y);
	~Arrow();
	int returnSelection() { return selection; }
	//void onProgressBarComplete();
	void Update();
	void Render();
};

