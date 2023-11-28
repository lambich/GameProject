#include "GameLevel4.h"
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  

void GameLevel4::Enter()
{

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Levels/SF_Level_2.jpg");

	//call base class's Enter function
	GameState::Enter();

}

