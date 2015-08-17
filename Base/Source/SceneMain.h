#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "SceneBase.h"
#include "Level.h"
#include "Vector2.h"
#include "PlayerInfo.h"

// Goodies and Goodies Factory
#include "GoodiesFactory.h"
#include "Coin.h"
#include "Health.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	~SceneMain();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderBackground();
	
	enum CHOICE
	{
		NONE,
		PLAY,
		QUIT,
		EXIT,
	};
	CHOICE choice;
private:

	Level* levelList[2];
	Level* currentLevel;

	// Handle to the tilemaps
	void RenderTileMap();
	// Hero's information
	CPlayerInfo* theHero;

	// Codes for Scrolling
	int tileOffset_x, tileOffset_y;

	// Codes for Parallax Scrolling
	void RenderRearTileMap();
	int rearWallOffset_x, rearWallOffset_y;
	int rearWallTileOffset_x, rearWallTileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;

	// Goodies and Goodies Factory
	CGoodiesFactory theGoodiesFactory;
	void RenderGoodies(void);

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
};

#endif