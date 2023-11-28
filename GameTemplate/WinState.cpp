#include <iostream>
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  
#include "MainMenuState.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "WinState.h"

using namespace std;

// Begin PauseState
void WinState::Enter()
{
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	cout << "Entering Result..." << endl;
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 412,350,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,500,200,80 }));

}

void WinState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::play]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel2());
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}


}


void WinState::Render()
{

	//Game::Instance()->GetFSM()->GetStates().front()->Render();
	//SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 54, 203, 207, 128);

	//draw background 
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	//draw the buttons
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		m_vButtons[i]->Render();
		string result = "Player won";

		RenderFont(true, result.c_str(), 470, 250);

	}



	ScreenState::Render();

}


void WinState::Exit()
{

	cout << "Exiting Pause..." << endl;

	//resume music
	//Game::Instance()->GetAM()->ToggleMusic();

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

