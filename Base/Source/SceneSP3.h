#ifndef SCENE_SP3_H
#define SCENE_SP3_H

#include "SceneBase.h"
#include "Level.h"
#include "Vector3.h"
#include "PlayerInfo.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

class SceneSP3 : public SceneBase
{
public:
	SceneSP3();
	~SceneSP3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	enum CHOICE
	{
		NONE,
		PLAY,
		QUIT,
		EXIT,
	};
	CHOICE choice;

	int soundinit();
private:

	vector<Level*> levelList;
	Level* currentLevel;

	// Hero's information
	CPlayerInfo* theHero;

	// Render functions
	void RenderBackground();
	void RenderHero();
	void RenderGameObjects();
	void RenderEnemies();
	void RenderGUI();

	enum GAME_STATE
	{
		MAINMENU,
		PLAYING,
		PAUSE,
		GAMEOVER,
	};
	GAME_STATE gameState;
	int highscore;

	void UpdateInputs(double dt);
	void HeroColision(GameObject* goCollidedWith, bool updown, bool upORleft, double dt);
};

#endif