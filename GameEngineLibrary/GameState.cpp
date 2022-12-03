#include "GameState.h"
#include "GameEngine.h"
//#include "PauseMenuPopupState.h"
void GameState::Enter()
{
	//	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	if (GameEngine::Instance()->getPlayerSelection() == 1)
	{
		mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite1.png");
	}
	else if (GameEngine::Instance()->getPlayerSelection() == 2)
	{
		mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
	}
	else if (GameEngine::Instance()->getPlayerSelection() == 3)
	{
		mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite3.png");
	}
	else if (GameEngine::Instance()->getPlayerSelection() == 4)
	{
		mainSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite4.png");
	}
	enemySelection = randomEnemy(GameEngine::Instance()->getPlayerSelection());
	if (enemySelection == 1)
	{
		badSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite1.png");
	}
	else if (enemySelection == 2)
	{
		badSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
	}
	else if (enemySelection == 3)
	{
		badSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite3.png");
	}
	else if (enemySelection == 4)
	{
		badSpriteTex = GameEngine::Instance()->LoadTexture("Img/Players/PlayerKenSprite4.png");
	}

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);


	player = new Player(mainSpriteTex, bgDestRect.w * 0.3, bgDestRect.h - 100);

	enemy = new Enemy(badSpriteTex, bgDestRect.w * 0.6, bgDestRect.h - 100);

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
		//std::cout << "under enemy...\n";
		enemy->Update();
	}
	if (player) {
		//std::cout << "under player...\n";
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
int GameState::randomEnemy(int selection)
{
	srand((unsigned)time(0));
	int result = selection;
	while (result == selection)
	{
		result = 1 + (rand() % 4);
	}

	return result;

}