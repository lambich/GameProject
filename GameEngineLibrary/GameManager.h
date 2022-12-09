#pragma once
class GameManager
{
private:
	int pHealth = 100;
	int eHealth = 100;

public:
	static GameManager* Instance();
	void PlayerGotHit(int h) { pHealth = pHealth - h; }
	int GetPlayerHealth() {
		return pHealth;
	}
	void EnemyGotHit(int h) { eHealth = eHealth - h; }
	int GetEnemyHealth() {
		return eHealth;
	}
	void restorePlayersStatus() {
		eHealth = 100;
		pHealth = 100;
	}
};