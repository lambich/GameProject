#pragma once
#include "../GameEngineLibrary/ScreenState.h"
#include "../GameEngineLibrary/Button.h"
#include "Player.h"
#include "Arrow.h"
#include <vector>
#include <string>

using namespace std;
//static SDLTest_CommonState* state;
static SDL_Rect textRect, markedRect;
static SDL_Color lineColor = { 0,0,0,0 };
static SDL_Color backColor = { 255,255,255,0 };
static SDL_Color textColor = { 0,0,0,0 };
//static char text[MAX_TEXT_LENGTH], markedText[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
static int cursor = 0;
#ifdef HAVE_SDL_TTF
static TTF_Font* font;
#endif

static int min = 1;
static int max = 4;

class SetupScreen : public ScreenState
{
protected:
	
	SDL_Texture* loadingSprite;
	vector<Button*> m_vButtons;
	//vector<int> selection = { 1,2,3,4 };
	enum btn { play, exit };
	SDL_Texture* mainSpriteTex;//load and store the main sprite texture
	SDL_Texture* bgSpriteTex; //load and store background sprite tex
	SDL_Texture* InputTex;

	SDL_Surface* surface;
	SDL_Renderer* renderer;

	SDL_Rect rectangle;
	//Event handler
	SDL_Event event;

	//select player
	SDL_Texture* player1SpriteTex;
	SDL_Texture* player2SpriteTex;
	SDL_Texture* player3SpriteTex;
	SDL_Texture* player4SpriteTex;

	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;

	//Arrow to indicate selection
	SDL_Texture* arrowSpriteTex;
	Arrow* arrow;

public:
	SetupScreen() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}
	void TextBox(string t, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, int maxLength);
};

