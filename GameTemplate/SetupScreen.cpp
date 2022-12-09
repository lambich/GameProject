#include "SetupScreen.h"
#include <iostream>
#include "GameEngine.h"
#include "MainMenuState.h"
#include "GameLevel1.h"
#include "LoadingScreen.h"
using namespace std;

void SetupScreen::Enter()
{
	player1SpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite1.png");
	player2SpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
	player3SpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite3.png");
	player4SpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite4.png");

	arrowSpriteTex = GameEngine::Instance()->LoadTexture("Img/arrow.png");

	loadingSprite = GameEngine::Instance()->LoadTexture("Img/loadingbar.png");
	cout << "Entering Setup screen...\n";
	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);
	cout << "Entering Result..." << endl;
	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 412,500,200,80 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 412,650,200,80 }));

	//GameEngine::Instance()->GetAM()->ToggleMusic();

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	//display player
	player1 = new Player(player1SpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 600);
	player2 = new Player(player2SpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 500);
	player3 = new Player(player3SpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 400);
	player4 = new Player(player4SpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 300);

	arrow = new Arrow(arrowSpriteTex, bgDestRect.w * 0.3 + 100, bgDestRect.h - 410);

}

void SetupScreen::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::play]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new LoadingScreen());
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		GameEngine::Instance()->QuitGame();
	}

	

	if (player1) {
		//std::cout << "under player...\n";
		player1->tempUpdate();
	}
	if (player2) {
		//std::cout << "under player...\n";
		player2->tempUpdate();
	}
	if (player3) {
		//std::cout << "under player...\n";
		player3->tempUpdate();
	}
	if (player4) {
		//std::cout << "under player...\n";
		player4->tempUpdate();
	}

	if (arrow) {
		arrow->Update();
	}

	textRect.x = 500;
	textRect.y = 100;
	textRect.w = 300;
	textRect.h = 50;

}


void SetupScreen::Render()
{

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 51, 51, 153, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	
	if (player1) player1->Render();
	if (player2) player2->Render();
	if (player3) player3->Render();
	if (player4) player4->Render();

	if (arrow) arrow->Render();
	
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 0xFF };

	//The current input text.
	std::string inputText1 = "Some Text";
	TextBox(inputText1, m_pFont, textColor, GameEngine::Instance()->GetRenderer(), 20);

	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &textRect);



	ScreenState::Render();
}


void SetupScreen::Exit()
{

	cout << "Exiting Setup screen..." << endl;

	//resume music
	//GameEngine::Instance()->GetAM()->ToggleMusic();

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}

void SetupScreen::TextBox(string t, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, int maxLength)
{
	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	char CharArray[2000]; // Create a char array
	strcpy_s(CharArray, t.c_str()); // Convert the string into a char array for the surface function.

	surface = TTF_RenderText_Blended_Wrapped(font, CharArray, color, maxLength); // Make into a surface.
	InputTex = SDL_CreateTextureFromSurface(renderer, surface); // Turn the surface into a texture.
	TTF_SizeText(font, CharArray, &bgDestRect.w, &bgDestRect.h); // Size the texture so it renders the text correctly.
}