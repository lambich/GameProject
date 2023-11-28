#include "LoadingBar.h"
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  

LoadingBar::LoadingBar(SDL_Texture* tex, double x, double y) : SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{
	//spriteSrcRect = { 0,0,1000,31 };
	spriteSrcRect = { 0,0,1000,31 };
	spriteDestRect = { (int)(m_X - 300),(int)(m_Y - 200),500,20 };//70 80

	//currentValue = (float)this->GetMaxValue();

	AddAnimState("10", AnimStateDefinition(0, 1, 120));
	AddAnimState("20", AnimStateDefinition(2, 1, 120));
	AddAnimState("30", AnimStateDefinition(4, 1, 120));
	AddAnimState("40", AnimStateDefinition(6, 1, 120));
	AddAnimState("50", AnimStateDefinition(8, 1, 120));
	AddAnimState("60", AnimStateDefinition(10, 1, 120));
	AddAnimState("70", AnimStateDefinition(12, 1, 120));
	AddAnimState("80", AnimStateDefinition(14, 1, 120));
	AddAnimState("90", AnimStateDefinition(16, 1, 120));
	AddAnimState("100", AnimStateDefinition(18, 1, 120));

}
LoadingBar::~LoadingBar()
{

}
void LoadingBar::Update()
{
	//this->UpdateBar();
}
void LoadingBar::Render()
{
	this->SpriteExAnimated::Render(); //invoke the base class's Render()

}