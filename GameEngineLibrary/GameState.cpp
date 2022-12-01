#include "GameState.h"
#include "GameEngine.h"
//#include "PauseMenuPopupState.h"
void GameState::Enter()
{
	//	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);


	player = new Player(mainSpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 100);

	enemy = new Enemy(mainSpriteTex, bgDestRect.w * 0.6, bgDestRect.h - 100);

}


void GameState::Update()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		//GameEngine::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (enemy)
	{
		std::cout << "under enemy...\n";
		enemy->Update();
	}
	if (player) {
		std::cout << "under player...\n";
		player->Update();
	}

	if (player) this->CheckCollision();




}


void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();

	if (enemy) enemy->Render();

	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 

}

void GameState::CheckCollision()
{


}
