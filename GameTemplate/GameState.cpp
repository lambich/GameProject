#include "GameState.h"
#include "../GameEngineLibrary/GameEngine.h"
#include "../GameEngineLibrary/Button.h"  
#include "../GameEngineLibrary/GameManager.h"  
#include "PauseMenuPopupState.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "GameLevel3.h"
#include "GameLevel4.h"
#include "WinState.h"
#include "LossState.h"
#include "EnterLevel2Screen.h"
#include "EnterLevel3Screen.h"
#include "EnterLevel4Screen.h"
#include <random>

int roundNum = 1;// round number
int level = 1;// level number
int pw = 0; // player's win(s) in each round;
int ew = 0; // enemy's         //

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
	
	bullet = new Bullet(mainSpriteTex, player->GetX(), bgDestRect.h - 100);
	
	enemy = new Enemy(badSpriteTex, bgDestRect.w * 0.6, bgDestRect.h - 100);

	enemyBullet = new EnemyBullet(badSpriteTex, enemy->GetX(), bgDestRect.h - 100);

	//Audio for theme music
	music = new AudioManager();
	music->LoadMusicGlobal("Aud/game.mp3", "Game");
	music->PlayMusicGlobal("Game");
}


void GameState::Update()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		GameEngine::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
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

	if (bullet) {
		//bullet->setBulletX(player->GetX());
	}

	if (player) this->CheckCollision();

	if (roundNum >= 3)
	{
		if (pw >= 3 && level == 1)
		{
			GameEngine::Instance()->GetFSM()->PushState(new EnterLevel2Screen());
			roundNum = 1;
			pw = 0;
			ew = 0;
			level++;
		}if (pw >= 3 && level == 2)
		{
			GameEngine::Instance()->GetFSM()->PushState(new EnterLevel3Screen());
			roundNum = 1;
			pw = 0;
			ew = 0;
			level++;
		}if (pw >= 3 && level == 3)
		{
			GameEngine::Instance()->GetFSM()->PushState(new EnterLevel4Screen());
			roundNum = 1;
			pw = 0;
			ew = 0;
			level++;
		}
		if (pw >= 3 && level == 4) {
			GameEngine::Instance()->GetFSM()->PushState(new WinState());
		}
		if (ew >= 3) {
			GameEngine::Instance()->GetFSM()->PushState(new LossState());
		}
	}
	//change level
	if (level == 3)
	{
		if (pH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel1());
			return;
		}
		if (eH <= 0)// reset round
		{
			roundNum++;
			ew++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel1());
			return;
		}
	}
	if (level == 2)
	{
		if (pH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel2());
			return;
		}
		if (eH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel2());
			return;
		}
	}
	if (level == 3)
	{
		if (pH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel3());
			return;
		}
		if (eH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel3());
			return;
		}
	}
	if (level == 4)
	{
		if (pH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel4());
			return;
		}
		if (eH <= 0)// reset round
		{
			roundNum++;
			pw++;
			GameManager::Instance()->restorePlayersStatus();// reset both players status
			GameEngine::Instance()->GetFSM()->PushState(new GameLevel4());
			return;
		}
	}

}


void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();

	if (enemy) enemy->Render();

	
	//bullet->ExploreBullet(enemy->GetX());
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_H))
	{
		hit = true;
		cout << "Bullet fired \n";
	}
	if (bullet && hit == true)
	{
		bullet->ExploreBullet(enemy->GetX());
		bullet->Render();
		bullet->MoveBullet(true);
	}
	if (bullet->GetX() >= enemy->GetX()) 
	{
		cout << "Enemy Got Hit !!! \n";
		GameManager::Instance()->EnemyGotHit(15);
		pH = GameManager::Instance()->GetEnemyHealth();
		bullet->setBulletX(player->GetX());

		//bullet->PlayState("BulletEnd");
		hit = false;		
		//bullet->UpdateBullet();
		//didHit = true;
	}

	if (level == 1)
	{
		//Enemy Bullet
		if (player->GetX() <= enemy->GetX() && inDistancePlayerEnemy == false)// && hitPlayer == false
		{
			if (randomNumber() > 7) {
				hitPlayer = true;
			}
		}
		if (hitPlayer == true && enemy->GetX() - 90 <= enemyBullet->GetX())
		{
			cout << "Enemy play Hadouken \n";
			enemy->PlayState("Hadouken");
		}
		if (enemyBullet && hitPlayer == true)
		{
			enemyBullet->Render();
			enemyBullet->MoveBullet(true);

			//enemy->PlayState("Hadouken");
		}
		
		if (enemyBullet && hitPlayer == true && GameEngine::Instance()->KeyDown(SDL_SCANCODE_SPACE))
		{
			passPlayer = true;
		}
		if (enemyBullet && hitPlayer == true && passPlayer == true && enemyBullet->GetX() <= 0)
		{
			enemyBullet->setBulletX(enemy->GetX());
			passPlayer = false;
			hitPlayer = false; // notice
		}
		if (bullet->GetX() <= player->GetX() - 500)
		{
			//enemyBullet->setBulletX(enemy->GetX());
		}
		if (enemyBullet->GetX() <= player->GetX() && passPlayer == false)
		{
			cout << "Got Hit !!!\n";
			enemyBullet->setBulletX(enemy->GetX());
			enemyBullet->Render();
			enemyBullet->MoveBullet(true);
			hitPlayer = false;

			GameManager::Instance()->PlayerGotHit(15);
			eH = GameManager::Instance()->GetPlayerHealth();
		}
		if (passPlayer == false || enemyBullet->GetX() <= 0) {
			//enemy->PlayState("Hadouken");
		}
	}
	
	string c = "Player Health: " + to_string(eH) + " - Enemy's Health: " + to_string(pH);
	RenderFont(true, c.c_str(), 30, 25);

	string c1 = "Round Number: " + to_string(roundNum) + " - Level: " + to_string(level);
	RenderFont(true, c1.c_str(), 30, 65);
	string c2 = "Player: " + to_string(pw) + " vs Enemy: " + to_string(ew);
	RenderFont(true, c2.c_str(), 30, 105);

	ScreenState::Render();


}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 

}

void GameState::CheckCollision()
{
	if (player->GetX() >= (enemy->GetX() - 50)) // this if condition check if 
	{											// player is within enemy position +and -50
		inDistancePlayerEnemy = true;
		int i = 5;// random number to determine which attack enemy uses
		for (int j = 0; j < 2000; j++) {
			i = rand() % 4;
		}
		if (i == 0) {
			enemy->PlayState("Punch");
			enemy->setAttackStatus(1);
		}
		else if (i == 1) {

			enemy->PlayState("Kick");
			enemy->setAttackStatus(2);

		}
		else if (i == 2) {

			enemy->PlayState("Roundhouse");
			enemy->setAttackStatus(3);


		}
		else if (i == 3) {
			for (int x = 0; x < 500; x++) {
				enemy->PlayState("Idle");
			}
			enemy->PlayState("Hadouken");
			enemy->setAttackStatus(4);

		}
	}
	if (player->GetAttackStatus() > 0) {// condition for enemy defense
		if (player->GetX() >= (enemy->GetX() - 30) && player->GetX() <= enemy->GetX() + 15)
		{// when player is attacking 
			int i = rand() % 2;// random generate a number to determine if enemy should crouch or not
			if (i == 0) {// when i=0 means enemy is defensing
				enemy->PlayState("Crouch");
				enemy->setAttackStatus(0);
			}
			else {
				if (player->GetAttackStatus() == 1)
				{
					if (i == 1) {// since i=1, enemy is not defensing so they will get hit by player and reduce health
						GameManager::Instance()->EnemyGotHit(5);
						pH = GameManager::Instance()->GetEnemyHealth();
						//cout << GameManager::Instance()->GetEnemyHealth();
					}
				}
				else if (player->GetAttackStatus() == 2) {
					if (i == 1) {
						GameManager::Instance()->EnemyGotHit(10);
						pH = GameManager::Instance()->GetEnemyHealth();
					}

				}
				else if (player->GetAttackStatus() == 3) {
					if (i == 1) {

						GameManager::Instance()->EnemyGotHit(15);
						pH = GameManager::Instance()->GetEnemyHealth();
					}

				}
			}
		}
	}
	if (enemy->GetAttackStatus() > 0) {// condition for enemy attack
		if (enemy->GetX() <= (player->GetX() + 20) && enemy->GetX() >= enemy->GetX() - 10)
		{// when enemy is attacking 

			if (enemy->GetAttackStatus() == 1)
			{
				GameManager::Instance()->PlayerGotHit(5);
				GameManager::Instance()->PlayerGotHit(0);
				eH = GameManager::Instance()->GetPlayerHealth();
			}
			else if (enemy->GetAttackStatus() == 2) {
				GameManager::Instance()->PlayerGotHit(10);
				GameManager::Instance()->PlayerGotHit(0);
				eH = GameManager::Instance()->GetPlayerHealth();
			}
			else if (enemy->GetAttackStatus() == 3) {
				GameManager::Instance()->PlayerGotHit(15);
				GameManager::Instance()->PlayerGotHit(0);
				eH = GameManager::Instance()->GetPlayerHealth();
			}
			else if (enemy->GetAttackStatus() == 4) {
				GameManager::Instance()->PlayerGotHit(30);
				GameManager::Instance()->PlayerGotHit(0);
				eH = GameManager::Instance()->GetPlayerHealth();
			}

		}
	}

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

int GameState::randomNumber()
{
	srand((unsigned)time(0));
	int result = 1 + (rand() % 10);
	return result;
}
