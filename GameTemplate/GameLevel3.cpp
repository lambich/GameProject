#include "GameLevel3.h"
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  

void GameLevel3::Enter()
{

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Levels/SF_Level_1.jpg");

	//call base class's Enter function
	GameState::Enter();

}
