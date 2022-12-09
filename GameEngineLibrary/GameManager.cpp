#include <iostream>
#include "GameManager.h"

GameManager* GameManager::Instance()
{
	static GameManager* instance = new GameManager();
	return instance;
}