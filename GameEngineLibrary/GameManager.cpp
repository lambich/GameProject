#include <iostream>
#include "GameManager.h"
#include "pch.h"


GameManager* GameManager::Instance()
{
	static GameManager* instance = new GameManager();
	return instance;
}