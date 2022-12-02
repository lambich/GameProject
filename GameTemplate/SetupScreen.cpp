#include "SetupScreen.h"
#include <iostream>
#include "GameEngine.h"
#include "MainMenuState.h"
#include "GameLevel1.h"
using namespace std;

void SetupScreen::Enter()
{
	loadingSprite = GameEngine::Instance()->LoadTexture("Img/loadingbar.png");
	cout << "Entering Setup screen...\n";
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	cout << "Entering Result..." << endl;
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 412,350,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,500,200,80 }));
	
	//GameEngine::Instance()->GetAM()->ToggleMusic();

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	loadingBar = new LoadingBar(loadingSprite, bgDestRect.w * 0.6, bgDestRect.h - 170);
}

void SetupScreen::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::play]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		GameEngine::Instance()->QuitGame();
	}
	if (loadingBar) {
		//std::cout << "under progressBar...\n";
		loadingBar->Update();
	}

	int n = 0;

	cout << "10%\n";
	loadingBar->PlayState("10");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "20%\n";		
	loadingBar->PlayState("20");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "30%\n";
	loadingBar->PlayState("30");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "40%\n";
	loadingBar->PlayState("40");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "50%\n";
	loadingBar->PlayState("50");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "60%\n";
	loadingBar->PlayState("60");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "70%\n";
	loadingBar->PlayState("70");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "80%\n";
	loadingBar->PlayState("80");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "90%\n";
	loadingBar->PlayState("90");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "100%\n";
	loadingBar->PlayState("100");
	GameEngine::Instance()->Render();
	n = n + 10;
	SDL_Delay(1000);

	cout << "loading completed\n";
	if (n == 100) {
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}
		
}


void SetupScreen::Render()
{

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 51, 51, 153, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	/*for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();*/


	if (loadingBar) {
		//cout << "Loading Bar Render \n";
		loadingBar->Render();
	}

	ScreenState::Render();

}


void SetupScreen::Exit()
{

	cout << "Exiting Setup screen..." << endl;

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

