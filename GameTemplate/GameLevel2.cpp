#include "GameLevel2.h"
#include "GameEngine.h"

void GameLevel2::Enter()
{

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Levels/SF_Level_2.jpg");

	//call base class's Enter function
	GameState::Enter();

}

