#pragma once
#include "../GameEngineLibrary/ScreenState.h"
#include "../GameEngineLibrary/Button.h"
#include <vector>
#include <iostream>
using namespace std;

class LossState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { play, exit };

public:
	LossState() {}

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}

};
