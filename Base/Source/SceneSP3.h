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

#include "Sound.h"

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
		SELECT_LEVEL,
		INSTRUCTIONS,
		SCORE,
		EXIT,
		QUIT,
	};
	int choice;

	enum LEVEL_CHOICE
	{
		ONE = 1,
		TWO,
		THREE,
		BACK
	};

	int levelchoice;
private:

	vector<Level*> levelList;
	Level* currentLevel;

	// Hero's information
	CPlayerInfo* theHero;
	
	void InitHero();
	void InitLevels();

	// Render functions
	void RenderBackground();
	void RenderHighscore();
	void RenderHero();
	void RenderGameObjects();
	void RenderEnemies();
	void RenderGUI();


	enum GAME_STATE
	{
		MAINMENU,
		PLAYING,
		LEVEL_SELECTOR,
		INSTRUCTIONS1,
		INSTRUCTIONS2,
		HIGHSCORE,
		GETTINGPLAYERNAME,
		PAUSE,
		ENDING,
		GAMEOVER,
	};
	GAME_STATE gameState;
	Highscore score;
	CRecord playerRecord;

	void UpdateInputs(double dt);

	vector<Mesh*> wallMesh, holeMesh, doorMesh, wetFloorMesh, timmingDoorMesh, blockMesh, hackMesh, healthMesh, trapMesh, arrowMesh;

	void InitGoMeshes();

	void DeleteGoMeshes();
	void UpdateActiveGO(double dt);
	HackingGame hackingGame;


	void RenderHackGame();
	Sound mysound;
	Blackout blackout;
	bool chara[32];
	string tempName;
	int currentLetter;

	bool isLevelSelect;
};

#endif