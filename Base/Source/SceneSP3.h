#ifndef SCENE_SP3_H
#define SCENE_SP3_H

#include "SceneBase.h"
#include "Level.h"
#include "Vector3.h"
#include "PlayerInfo.h"
#include "HackingGame.h"

#include "Blackout.h"
#include "Minimap.h"
#include "Highscore.h"
#include "Record.h"

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
		SCORE,
		EXIT,
		QUIT,
	};
	int choice;

private:

	vector<Level*> levelList;
	Level* currentLevel;

	// Hero's information
	CPlayerInfo* theHero;
	
	void InitHero();
	void InitLevels();
	int InitSound();

	// Render functions
	void RenderBackground();
	void RenderHighscore();
	void RenderHero();
	void RenderGameObjects();
	void RenderEnemies();
	void RenderGUI();
	void RenderMinimap();

	enum GAME_STATE
	{
		MAINMENU,
		PLAYING,
		HIGHSCORE,
		PAUSE,
		GAMEOVER,
	};
	GAME_STATE gameState;
	Highscore score;
	CRecord playerRecord;
	CMinimap* m_cMiniMap;

	void UpdateInputs(double dt);

	vector<Mesh*> wallMesh, holeMesh, doorMesh, wetFloorMesh, timmingDoorMesh, lockedDoorMesh, hackMesh, healthMesh, fireMesh, arrowMesh;
	void InitGoMeshes();
	void InitMinimap();
	void DeleteGoMeshes();
	void UpdateActiveGO(double dt);
	int menustate;
	HackingGame hackingGame;

	void RenderHackGame();

	Blackout blackout;
};

#endif