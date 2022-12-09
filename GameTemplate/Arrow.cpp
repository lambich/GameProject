#include "Arrow.h"
#include "GameEngine.h"

Arrow::Arrow(SDL_Texture* tex, double x, double y) : SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{
	//spriteSrcRect = { 0,0,1000,31 };
	spriteSrcRect = { 0,0,2400,2400 };
	spriteDestRect = { (int)(m_X - 20),(int)(m_Y - 200),40,40 };//70 80

	//currentValue = (float)this->GetMaxValue();

	AddAnimState("arrow", AnimStateDefinition(0, 1, 120));

}
Arrow::~Arrow()
{

}
void Arrow::Update()
{
	this->UpdateArrow();

	if (selection == 1) {
		m_Y = 110;
	}
	else if (selection == 2) {
		m_Y = 210;
	}
	else if (selection == 3) {
		m_Y = 310;
	}
	else if (selection == 4) {
		m_Y = 410;
	}
}
void Arrow::Render()
{
	this->SpriteExAnimated::Render(); //invoke the base class's Render()

}

void Arrow::UpdateArrow()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_S))
	{
		selection += 1;
		if (selection > 4)
			selection = 4;
		SDL_Delay(100);
		GameEngine::Instance()->setPlayerSelection(selection);
		cout << "Your choice: " + std::to_string(GameEngine::Instance()->getPlayerSelection()) + "\n";
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		selection -= 1;
		if (selection < 1)
			selection = 1;
		SDL_Delay(100);
		GameEngine::Instance()->setPlayerSelection(selection);
		cout << "Your choice: " + std::to_string(GameEngine::Instance()->getPlayerSelection()) + "\n";
	}

	this->spriteSrcRect.x = spriteSrcRect.w * m_iFrame;
	this->UpdateDestRect();
}
