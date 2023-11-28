#pragma once

#include "../GameEngineLibrary/ScreenState.h"
#include "../GameEngineLibrary/Button.h"
#include <vector>

using namespace std;

class PauseMenuPopupState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { resume, exit };

public:
	PauseMenuPopupState() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};
