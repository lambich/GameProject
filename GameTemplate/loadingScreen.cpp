#include "LoadingScreen.h"
#include <iostream>
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  
#include "MainMenuState.h"
#include "GameLevel1.h"
using namespace std;

void LoadingScreen::Enter()
{
	loadingSprite = GameEngine::Instance()->LoadTexture("Img/loadingbar.png");
	cout << "Entering Loading screen...\n";
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	cout << "Entering Result..." << endl;
	
	//GameEngine::Instance()->GetAM()->ToggleMusic();

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	loadingBar = new LoadingBar(loadingSprite, bgDestRect.w * 0.6, bgDestRect.h - 170);
}

void LoadingScreen::Update()
{
	
	if (loadingBar) {
		//std::cout << "under progressBar...\n";
		loadingBar->Update();
	}

	int n = 0;
	for (int i = 0; i < 10; i++) {
		n = n + 10;
		cout << std::to_string(n) + "%\n";
		loadingBar->PlayState(std::to_string(n));
		GameEngine::Instance()->Render();
		SDL_Delay(delayTime);
	}
	

	cout << "loading completed\n";

	if (n == 100) {
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel1());
		cout << "Playing Level 1\n";
	}
		
}


void LoadingScreen::Render()
{

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 51, 51, 153, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());


	if (loadingBar) {
		//cout << "Loading Bar Render \n";
		loadingBar->Render();
	}

	ScreenState::Render();

}


void LoadingScreen::Exit()
{

	cout << "Exiting Loading screen..." << endl;

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

