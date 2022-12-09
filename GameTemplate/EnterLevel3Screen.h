#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
using namespace std;

class EnterLevel3Screen : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { play, exit };

public:
	EnterLevel3Screen() {}

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}

};