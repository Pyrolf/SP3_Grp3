#include "SceneSP3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

static bool soundingplay = false;

SceneSP3::SceneSP3()
	: gameState(MAINMENU)
	, choice(NONE)
	, currentLevel(NULL)
	, tempName("     ")
	, currentLetter(0)
	,isLevelSelect(false)
	,levelchoice(ONE)
{
}

SceneSP3::~SceneSP3()
{
}

void SceneSP3::Init()
{
	SceneBase::Init();
	InitHero();
	InitGoMeshes();
	InitLevels();
	mysound.soundInit();
	// Normal zombie
	meshList[GEO_NORMAL_ZOMBIE_ATTACK_RANGE] = MeshBuilder::GenerateHalfRing("NORMAL_ATTACK_RANGE", Color(0, 1, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 2, levelList[0]->gameObjectsManager->tileSize * 2 - 1.f);
	meshList[GEO_NORMAL_ZOMBIE_REPEL_RANGE] = MeshBuilder::GenerateRing("NORMAL_REPEL_RANGE", Color(1, 0, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 0.5, levelList[0]->gameObjectsManager->tileSize * 0.5 - 1.f);
	// Smart zombie
	meshList[GEO_SMART_ZOMBIE_ATTACK_RANGE] = MeshBuilder::GenerateHalfRing("SMART_ATTACK_RANGE", Color(0, 1, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 3, levelList[0]->gameObjectsManager->tileSize * 3 - 1.f);
	meshList[GEO_SMART_ZOMBIE_REPEL_RANGE] = MeshBuilder::GenerateRing("SMART_REPEL_RANGE", Color(1, 0, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 0.5, levelList[0]->gameObjectsManager->tileSize * 0.5 - 1.f);
	// Tank zombie
	meshList[GEO_TANK_ZOMBIE_ATTACK_RANGE] = MeshBuilder::GenerateRing("TANK_ATTACK_RANGE", Color(0, 1, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 4, levelList[0]->gameObjectsManager->tileSize * 4 - 1.f);
	meshList[GEO_TANK_ZOMBIE_REPEL_RANGE] = MeshBuilder::GenerateRing("TANK_REPEL_RANGE", Color(1, 0, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 0.5, levelList[0]->gameObjectsManager->tileSize * 0.5 - 1.f);
	// Hunter zombie
	meshList[GEO_HUNTER_ZOMBIE_ATTACK_RANGE] = MeshBuilder::GenerateRing("HUNTER_ATTACK_RANGE", Color(0, 1, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 3, levelList[0]->gameObjectsManager->tileSize * 3 - 1.f);
	meshList[GEO_HUNTER_ZOMBIE_REPEL_RANGE] = MeshBuilder::GenerateRing("HUNTER_REPEL_RANGE", Color(1, 0, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 0.5, levelList[0]->gameObjectsManager->tileSize * 0.5 - 1.f);
	
	score.ReadFromTextFile();
		
	for(int i = 0; i < 32; ++i)
	{
		chara[i] = false;
	}
	
	hackingGame.Init(Vector3(270, 335, 0), Vector3(753, 365, 0));
	
}

void SceneSP3::InitHero()
{
	// Initialise the hero's position
	theHero = new CPlayerInfo();
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_SIDE", 64.0f, 64.0f, 21, 13, 0, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_SIDE", 64.0f, 64.0f, 21, 13, 1, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_SIDE", 64.0f, 64.0f, 21, 13, 2, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_SIDE", 64.0f, 64.0f, 21, 13, 3, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_SIDE", 64.0f, 64.0f, 21, 13, 4, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_SIDE", 64.0f, 64.0f, 21, 13, 5, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_SIDE", 64.0f, 64.0f, 21, 13, 6, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_SIDE", 64.0f, 64.0f, 21, 13, 7, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_SIDE", 64.0f, 64.0f, 21, 13, 8, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_FRONT", 64.0f, 64.0f, 21, 13, 0, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_FRONT", 64.0f, 64.0f, 21, 13, 1, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_FRONT", 64.0f, 64.0f, 21, 13, 2, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_FRONT", 64.0f, 64.0f, 21, 13, 3, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_FRONT", 64.0f, 64.0f, 21, 13, 4, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_FRONT", 64.0f, 64.0f, 21, 13, 5, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_FRONT", 64.0f, 64.0f, 21, 13, 6, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_FRONT", 64.0f, 64.0f, 21, 13, 7, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_FRONT", 64.0f, 64.0f, 21, 13, 8, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_BACK", 64.0f, 64.0f, 21, 13, 0, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_BACK", 64.0f, 64.0f, 21, 13, 1, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_BACK", 64.0f, 64.0f, 21, 13, 2, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_BACK", 64.0f, 64.0f, 21, 13, 3, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_BACK", 64.0f, 64.0f, 21, 13, 4, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_BACK", 64.0f, 64.0f, 21, 13, 5, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_BACK", 64.0f, 64.0f, 21, 13, 6, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_BACK", 64.0f, 64.0f, 21, 13, 7, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_BACK", 64.0f, 64.0f, 21, 13, 8, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_DEATH", 64.0f, 64.0f, 21, 13, 0, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_DEATH", 64.0f, 64.0f, 21, 13, 1, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_DEATH", 64.0f, 64.0f, 21, 13, 2, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_DEATH", 64.0f, 64.0f, 21, 13, 3, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_DEATH", 64.0f, 64.0f, 21, 13, 4, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_DEATH", 64.0f, 64.0f, 21, 13, 5, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 0, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 1, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 2, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 3, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 4, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_FRONT", 64.0f, 64.0f, 4, 6, 5, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");

	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 0, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 1, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 2, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 3, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 4, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_BACK", 64.0f, 64.0f, 4, 6, 5, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");

	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 0, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 1, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 2, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 3, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 4, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_SIDE", 64.0f, 64.0f, 4, 6, 5, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
}


void SceneSP3::InitLevels()
{
	// Initialise and load the tile map
	const int noOfLevel = 4;
	for(int i = 0; i < noOfLevel; i++)
	{
		levelList.push_back(new Level);
		levelList[i]->m_cMap = new CMap();
		levelList[i]->m_cMap->Init( 768 + 64, 1024, 12 + 1, 16, 3200 + 64, 3200, 64);
	}

	// Level 0
	levelList[0]->m_cMap->LoadMap( "Image//level0_house.csv" );
	levelList[0]->background = MeshBuilder::Generate2DMesh("HOUSE_LEVEL", Color(1, 1, 1), 0.0f, 0.0f, 3200, 3200);
	levelList[0]->background->textureID = LoadTGA("Image//house_level0.tga");

	// Level Darren
	levelList[1]->m_cMap->LoadMap( "Image//map1levelDar.csv" );
	levelList[1]->background = MeshBuilder::Generate2DMesh("GEO_LEVL1", Color(1, 1, 1), 0.0f, 0.0f, 3200, 3200);
	levelList[1]->background->textureID = LoadTGA("Image//map1level.tga");

	// Level 2
	levelList[2]->m_cMap->LoadMap( "Image//MapDesignLv2.csv" );
	levelList[2]->background = MeshBuilder::Generate2DMesh("GEO_BACKGROUND_LEVEL2", Color(1, 1, 1), 0.0f, 0.0f, 3200, 3200);
	levelList[2]->background->textureID = LoadTGA("Image//level2_background.tga");

	// Level 3
	levelList[3]->m_cMap->LoadMap( "Image//MapDesignLv3.csv" );
	levelList[3]->background = MeshBuilder::Generate2DMesh("GEO_BACKGROUND_LEVEL3", Color(1, 1, 1), 0.0f, 0.0f, 3200, 3200);
	levelList[3]->background->textureID = LoadTGA("Image//level3_background.tga");

	

	for(int i = 0; i < noOfLevel; i++)
	{
		levelList[i]->sideView = false;

		levelList[i]->gameObjectsManager = new GameObjectFactory;
		levelList[i]->gameObjectsManager->generateGO(levelList[i]->m_cMap);

		levelList[i]->AI_Manager = new CAIManager;

		levelList[i]->LevelMap_Nodes = new CLevelMap_Nodes;
		levelList[i]->LevelMap_Nodes->GenerateNodes(levelList[i]->m_cMap, levelList[i]->AI_Manager, levelList[i]->gameObjectsManager);

		levelList[i]->HeroStartPosNode = levelList[i]->LevelMap_Nodes->FindHeroInitialNode();
	}
}

void SceneSP3::UpdateInputs(double dt)
{
	static bool backsp = false;

	for(int i = 0; i < 32 ; ++i)
	{
		if(Application::IsKeyPressed('A' + i) && !chara[i])
		{
			chara[i] = true;

			if(gameState == GETTINGPLAYERNAME && currentLetter < 5)
			{
				tempName[currentLetter] = 'A' + i;
				currentLetter++;
			}
		}
		else if(!Application::IsKeyPressed('A' + i) && chara[i])
		{				
			chara[i] = false;
		}
	}

	if(Application::IsKeyPressed(VK_BACK) && !backsp)
	{
		backsp = true;
		if(gameState == GETTINGPLAYERNAME && currentLetter > 0)
		{
			tempName[currentLetter - 1] = NULL;
			currentLetter--;
		}
	}
	else if(!Application::IsKeyPressed(VK_BACK) && backsp)
	{				
		backsp = false;
	}

	static bool upkey = false;
	static bool downkey = false;

	// For gameplay
	{
		// Check Collision of th hero before moving up
		if(Application::IsKeyPressed('P'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL && gameState == PLAYING)
			{
				gameState = PAUSE;
				mysound.engine->setAllSoundsPaused(true);
				mysound.engine2->setAllSoundsPaused(true);
			}
		}

		if(Application::IsKeyPressed('F'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->attackingEnabled();
				mysound.playSound(Sound::PLAYER_ATTACK);
			}
		}

		// Check Collision of th hero before moving up
		if(Application::IsKeyPressed('W'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL 
				&& gameState == PLAYING)
			{
				this->theHero->MoveUpDown(true, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize, mysound);
			}
		}
		// Check Collision of th hero before moving down
		else if(Application::IsKeyPressed('S'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveUpDown(false, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize, mysound);
			}
		}

		// Check Collision of th hero before moving left
		else if(Application::IsKeyPressed('A'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveLeftRight(true, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize, mysound);
			}
		}
		// Check Collision of th hero before moving right

		else if(Application::IsKeyPressed('D'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveLeftRight(false, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize, mysound);
			}
		}

		// if not pressing anything and moving
		if(!Application::IsKeyPressed('W') && !Application::IsKeyPressed('A') && !Application::IsKeyPressed('S') && !Application::IsKeyPressed('D') && !Application::IsKeyPressed('F')
			&& gameState == PLAYING
			&& this->theHero->GetCurrentState() == this->theHero->NIL)
		{
			this->theHero->SetAnimationCounter(0.0f);
		}

		static bool spaceDown = false;
		if(Application::IsKeyPressed(VK_SPACE) && spaceDown == false && gameState == PLAYING)
		{
			if(hackingGame.active)
				if(hackingGame.Input(dt))
				{
					mysound.playSound(Sound::HACK_SUCCESS);
				}
				else
				{
					mysound.playSound(Sound::HACK_FAILURE);
				}
			else
			{
				switch(this->theHero->GetAnimationDirection())
				{
				case this->theHero->UP:
					{
						if(this->theHero->GetCurrentPosNode()->up->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
						{
							ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(this->theHero->GetCurrentPosNode()->up->gameObject);
							hackingGame.id = temp->id;
							hackingGame.active = true;
						}
						
					}break;
				case this->theHero->DOWN:
					{
						if(this->theHero->GetCurrentPosNode()->down->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
						{
							ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(this->theHero->GetCurrentPosNode()->down->gameObject);
							hackingGame.id = temp->id;
							hackingGame.active = true;
						}
						
					}break;
				case this->theHero->LEFT:
					{
						if(this->theHero->GetCurrentPosNode()->left->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
						{
							ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(this->theHero->GetCurrentPosNode()->left->gameObject);
							hackingGame.id = temp->id;
							hackingGame.active = true;
						}
						
					}break;
				case this->theHero->RIGHT:
					{
						if(this->theHero->GetCurrentPosNode()->right->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
						{
							ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(this->theHero->GetCurrentPosNode()->right->gameObject);
							hackingGame.id = temp->id;
							hackingGame.active = true;
						}
						
					}break;
				}
			}
			spaceDown = true;
		}
		else if(!Application::IsKeyPressed(VK_SPACE) && spaceDown == true)
		{
			spaceDown = false;
		}

		if(Application::IsKeyPressed(VK_LMENU) && blackout.fullyCharged)
		{
			blackout.lightOn = true;
		}
		else
		{
			blackout.lightOn = false;
		}
	}
	// Others
	{
		static bool IsKeyPressedReturn = false;
		// Choose play
		if(Application::IsKeyPressed(VK_UP) && upkey == false)
		{
			if(gameState == PAUSE)
			{
				if(choice != PLAY)
				{
					choice = PLAY;
				}
				mysound.playSound(Sound::MENUCHOICE);
				
			}
			if(gameState == MAINMENU)
			{
				switch(choice)
				{
				case NONE:
					choice = PLAY;
					break;
				case PLAY:
					choice = EXIT;
					break;
				default:
					choice -= 1;					
					break;
				}
				mysound.playSound(Sound::MENUCHOICE);
			}
			else if(gameState == LEVEL_SELECTOR)
			{
				switch(levelchoice)
				{
				case ONE:
					levelchoice = BACK;
					break;
				default:
					levelchoice -= 1;					
					break;
				}
				mysound.playSound(Sound::MENUCHOICE);
			}
			upkey = true;

		}
		else if(Application::IsKeyPressed(VK_UP) == false && upkey == true)
		{
			upkey = false;
		}
		// Choose exit
		else if(Application::IsKeyPressed(VK_DOWN) && downkey == false)
		{
			if(gameState == PAUSE)
			{
				if(choice != QUIT)
				{
					choice = QUIT;
				}
				mysound.playSound(Sound::MENUCHOICE);
				
			}
			else if(gameState == MAINMENU)
			{
				switch(choice)
				{
				case EXIT:
					choice = PLAY;
					break;
				default:
					choice += 1;
					break;
				}
				mysound.playSound(Sound::MENUCHOICE);
			}
			else if(gameState == LEVEL_SELECTOR)
			{
				switch(levelchoice)
				{
				case BACK:
					levelchoice = ONE;
					break;
				default:
					levelchoice += 1;					
					break;
				}
				mysound.playSound(Sound::MENUCHOICE);
			}
			downkey = true;
		}
		else if(Application::IsKeyPressed(VK_DOWN) == false && downkey == true)
		{
			downkey = false;
		}
		// Confirm choice
		else if(Application::IsKeyPressed(VK_RETURN) && !IsKeyPressedReturn)
		{
			if(gameState == PAUSE)
			{
				if(choice == PLAY)
				{
					gameState = PLAYING;
					mysound.engine->setAllSoundsPaused(false);
					mysound.engine2->setAllSoundsPaused(false);
				}
				else if(choice == QUIT)
				{
					gameState = MAINMENU;
					this->theHero->Reset();
					this->theHero->SetCurrentState(this->theHero->NIL);
					playerRecord.reset();
					currentLevel->AI_Manager->Reset();
					currentLevel->gameObjectsManager->ResetUGO();
					blackout.Reset();

					isLevelSelect = false;
					mysound.engine->stopAllSounds();
					mysound.engine2->stopAllSounds();
					soundingplay = false;
				}
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == MAINMENU)
			{
				if(choice == PLAY)
				{
					gameState = PLAYING;
					currentLevel = levelList[0];
					theHero->SetPos(currentLevel->HeroStartPosNode->pos);
					theHero->SetInitialPosNode(currentLevel->HeroStartPosNode);
					theHero->SetCurrentPosNode(currentLevel->HeroStartPosNode);
					theHero->SetTargetPosNode(currentLevel->HeroStartPosNode);
				}
				else if(choice == SELECT_LEVEL)
				{
					gameState = LEVEL_SELECTOR;
				}
				else if(choice == INSTRUCTIONS)
				{
					gameState = INSTRUCTIONS1;
				}
				else if(choice == SCORE)
				{
					gameState = HIGHSCORE;
				}
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == LEVEL_SELECTOR)
			{
				if(levelchoice != BACK)
				{
					gameState = PLAYING;
					currentLevel = levelList[levelchoice];
					theHero->SetPos(currentLevel->HeroStartPosNode->pos);
					theHero->SetInitialPosNode(currentLevel->HeroStartPosNode);
					theHero->SetCurrentPosNode(currentLevel->HeroStartPosNode);
					theHero->SetTargetPosNode(currentLevel->HeroStartPosNode);

					isLevelSelect = true;
				}
				else
				{
					gameState = MAINMENU;
				}
				levelchoice = ONE;
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == INSTRUCTIONS1)
			{
				gameState = INSTRUCTIONS2;
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == INSTRUCTIONS2)
			{
				gameState = MAINMENU;
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == HIGHSCORE)
			{
				gameState = MAINMENU;
				mysound.playSound(Sound::MENU_ENTER);
			}
			else if(gameState == GAMEOVER)
			{
				if(theHero->GetCurrentState() != CPlayerInfo::DYING 
					&& score.HighscoreCheck(playerRecord)
					&& !isLevelSelect)
				{
					if(playerRecord.getName().size() == 0)
					{
						gameState = GETTINGPLAYERNAME;
					}
					else
					{
						//store record
						score.storeNewRecord(playerRecord);

						gameState = MAINMENU;
						playerRecord.reset();

					}
				}
				else
				{
					gameState = MAINMENU;
					playerRecord.reset();
					isLevelSelect = false;
				}


				this->theHero->Reset();
				this->theHero->SetCurrentState(this->theHero->NIL);
				currentLevel->AI_Manager->Reset();
				currentLevel->gameObjectsManager->ResetUGO();
				blackout.Reset();
			}
			else if(gameState == GETTINGPLAYERNAME && currentLetter > 0)
			{
				string tempd = "      ";
				for(int i = 1; i < 6; ++i)
				{
					if(tempName[i - 1] != NULL)
					{
						tempd[i] = tempName[i - 1];
					}
					else 
						break;
				}
				playerRecord.setName(tempd);
				//store record
				score.storeNewRecord(playerRecord);

				playerRecord.getTiming().Reset();
				gameState = MAINMENU;
			}
			choice = NONE;
			IsKeyPressedReturn = true;
		}
		else if(!Application::IsKeyPressed(VK_RETURN) && IsKeyPressedReturn)
			IsKeyPressedReturn = false;
	}
}


void SceneSP3::RenderHighscore()
{
	Render2DMesh(meshList[GEO_HIGHSCORE], false);
	for(int i = 0; i < 5; ++i)
	{
		int temp = i;
		std::ostringstream scoring;
		scoring << temp + 1 << "." << score.record[i].getName() << " " << score.record[i].getTiming().getMin() << ":" << score.record[i].getTiming().getSec();
		RenderTextOnScreen(meshList[GEO_TEXT], scoring.str(), Color(1, 1, 1), 5, 5, 40 - i * 5);
	}

}

void SceneSP3::Update(double dt)
{
	if(gameState == ENDING)
	{
		theHero->SetPos_y(theHero->GetPos().y - 400 * dt);
		if(theHero->GetPos().y < -300)
		{
			gameState = GAMEOVER;
			mysound.engine2->stopAllSounds();
		}
	}
	else
	{
		UpdateInputs(dt);
	}

	if(gameState == PLAYING)
	{
		if(!soundingplay)        // main menu sound
		{
			mysound.playSound(Sound::GAMEPLAYING);
			soundingplay = true;
		}	
		if(this->theHero->GetCurrentState() != this->theHero->DYING && this->theHero->GetCurrentState() != this->theHero->EXITING)
		{
			playerRecord.update(dt);
		}
		
		// Exiting
		if(this->theHero->GetCurrentState() == this->theHero->EXITING)
		{
			if(this->theHero->GetTimeElasped() >= 1.f)
			{
				currentLevel->AI_Manager->Reset();
				for(int index = 0; index < levelList.size(); index++)
				{
					if(currentLevel == levelList[index])
					{
						if(index + 1 < levelList.size())
						{
							currentLevel = levelList[index + 1];
							this->theHero->SetPos(currentLevel->HeroStartPosNode->pos);
							this->theHero->SetInitialPosNode(currentLevel->HeroStartPosNode);
							this->theHero->SetCurrentPosNode(currentLevel->HeroStartPosNode);
							this->theHero->SetTargetPosNode(currentLevel->HeroStartPosNode);
							this->theHero->SetCurrentState(this->theHero->NIL);
							this->theHero->SetTimeElasped( 0.f );
							this->theHero->SetAnimationDirection(CPlayerInfo::DOWN);
							break;
						}
						else
						{
							mysound.engine2->stopAllSounds();
							soundingplay = false;
							theHero->SetPos_x(512 - 32);
							theHero->SetPos_y(768);
							gameState = ENDING;
							mysound.playSound(Sound::FALLINGENDING);
							return;
						}
					}
				}
			}
			else
				this->theHero->SetTimeElasped( this->theHero->GetTimeElasped() + dt );
		}
		// Dying
		else if(theHero->GetCurrentState() == CPlayerInfo::DYING)
		{
			if(theHero->GetTimeElasped() >= 2.f)
			{
				// Gameover
				gameState = GAMEOVER;
				mysound.engine2->stopAllSounds();
				soundingplay = false;
				theHero->SetTimeElasped(0.0f);
			}
		}

		theHero->HeroUpdate(dt, currentLevel->AI_Manager, currentLevel->gameObjectsManager, currentLevel->m_cMap, mysound);

		//Enemies
		for(vector<CZombie *>::iterator it = currentLevel->AI_Manager->zombieList.begin(); it != currentLevel->AI_Manager->zombieList.end(); ++it)
		{
			CZombie *zombie = (CZombie *)*it;
			if(zombie->active)
			{
				zombie->Update(currentLevel->gameObjectsManager->tileSize, dt, theHero->GetCurrentPosNode(), theHero->GetPos());
				if(zombie->GetHitHero())
				{
					if(!this->theHero->GetJustGotDamged() && this->theHero->GetCurrentState() != CPlayerInfo::DYING)
					{
						this->theHero->SetHealth(theHero->GetHealth() - 1);
						if(theHero->GetHealth() <= 0)
						{
							this->theHero->SetCurrentState(CPlayerInfo::DYING);
							theHero->SetAnimationCounter(0.0f);
							mysound.playSound(Sound::PLAYER_DYING);
						}
						else
						{
							this->theHero->knockBackEnabled(zombie->GetVel(), currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
							this->theHero->SetJustGotDamged(true);
							mysound.playSound(Sound::PLAYER_DAMAGED);
						}
					}
					zombie->SetHitHero(false);
					break;
				}
			}
		}
		if(hackingGame.active)
		{
			mysound.engine2->setAllSoundsPaused(true);
			hackingGame.Update(dt);
			if(hackingGame.currentBar == hackingGame.hackingBar.size() || theHero->GetCurrentState() != theHero->NIL)
			{
				if(hackingGame.currentBar == hackingGame.hackingBar.size())
				{
					for(int i = 0; i < currentLevel->gameObjectsManager->UpdatableGoList.size(); ++i)
					{
						if(currentLevel->gameObjectsManager->UpdatableGoList[i]->type == GameObject::BLOCK && currentLevel->gameObjectsManager->UpdatableGoList[i]->id == hackingGame.id)
						{
							currentLevel->gameObjectsManager->UpdatableGoList[i]->active = false;
						}
					}
					mysound.playSound(Sound::DOOR_OPEN);
				}
				mysound.engine2->setAllSoundsPaused(false);
				hackingGame.active = false;
				hackingGame.Reset();
			}
		}
		UpdateActiveGO(dt);
		blackout.Update(dt);
	}
}

void SceneSP3::RenderBackground()
{
	// Render the crosshair
	Render2DMesh(currentLevel->background, false);
}
void SceneSP3::Render()
{
	SceneBase::Render();
	glDisable(GL_DEPTH_TEST);
	switch(gameState)
	{
	
	case MAINMENU:
		{		
			Render2DMesh(meshList[GEO_MAINMENU], false);
			
			//On screen text
			RenderTextOnScreen(meshList[GEO_TEXT], "START GAME", Color(1, 1, 1), 5, 15, 25);
			RenderTextOnScreen(meshList[GEO_TEXT], "SELECT LEVEL", Color(1, 1, 1), 5, 15, 20);
			RenderTextOnScreen(meshList[GEO_TEXT], "INSTRUCTIONS", Color(1, 1, 1), 5, 15, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "HIGHSCORE", Color(1, 1, 1), 5, 15, 10);
			RenderTextOnScreen(meshList[GEO_TEXT], "EXIT", Color(1, 1, 1), 5, 15, 5);
			if(choice == PLAY)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 10, 25);
			}
			else if(choice == SELECT_LEVEL)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 10, 20);
			}
			else if(choice == INSTRUCTIONS)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 10, 15);
			}
			else if(choice == SCORE)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 10, 10);
			}
			else if(choice == EXIT)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 10, 5);
			}
		}
		break;
	case INSTRUCTIONS1:
		{		
			Render2DMesh(meshList[GEO_INSTRUCTIONS1], false);
		}
		break;
	case INSTRUCTIONS2:
		{		
			Render2DMesh(meshList[GEO_INSTRUCTIONS2], false);
		}
		break;
	case LEVEL_SELECTOR:
		{		
			Render2DMesh(meshList[GEO_MAINMENU], false);
			
			//On screen text
			RenderTextOnScreen(meshList[GEO_TEXT], "CITY", Color(1, 1, 1), 5, 25, 25);
			RenderTextOnScreen(meshList[GEO_TEXT], "FOREST", Color(1, 1, 1), 5, 25, 20);
			RenderTextOnScreen(meshList[GEO_TEXT], "MOUNTANT", Color(1, 1, 1), 5, 25, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "BACK", Color(1, 1, 1), 5, 25, 10);
			if(levelchoice == ONE)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 25);
			}
			else if(levelchoice == TWO)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 20);
			}
			else if(levelchoice == THREE)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 15);
			}
			else if(levelchoice == BACK)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 10);
			}
		}
		break;
	case HIGHSCORE:
		{
			RenderHighscore();	
			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(1, 1, 1), 2.5, 13, 5);
		}		
		break;
	case GETTINGPLAYERNAME:
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter your name:", Color(1, 1, 1), 3, 5, 30);
			RenderTextOnScreen(meshList[GEO_TEXT], tempName, Color(1,1,1), 2.5, 10, 20);
		}
		break;
	case PAUSE:
		{
			Render2DMesh(meshList[GEO_PAUSE], false);

			//On screen text
			RenderTextOnScreen(meshList[GEO_TEXT], "1.CONTINUE", Color(1, 1, 1), 5, 25, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "2.QUIT", Color(1, 1, 1), 5, 25, 10);
			if(choice == PLAY)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 15);
				
			}
			else if(choice == QUIT)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 10);
			}
		}
		break;
	case ENDING:
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "DARREN", Color(1, 1, 1), 2, 45, theHero->GetPos().y / 12.8 + 20);
			RenderTextOnScreen(meshList[GEO_TEXT], "IVAN", Color(1, 1, 1), 2, 45, theHero->GetPos().y / 12.8 + 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "GREGORY(LEADER)", Color(1, 1, 1), 2, 45, theHero->GetPos().y / 12.8 + 10);

			RenderTextOnScreen(meshList[GEO_TEXT], "CREDITS:", Color(1, 1, 1), 2.5, 15, theHero->GetPos().y / 12.8 + 10);

			Render2DMesh(theHero->backMeshes[0], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y, false, theHero->GetPos().y);
		}
		break;
	case GAMEOVER:
		{
			Render2DMesh(meshList[GEO_GAMEOVER], false);

			std::ostringstream gamoev;
			gamoev << playerRecord.getTiming().getMin() << ":" << playerRecord.getTiming().getSec();
			RenderTextOnScreen(meshList[GEO_TEXT], gamoev.str(), Color(0, 0, 0), 5.f, 20.f, 15.f);
		
			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(0, 0, 0), 2.5, 13, 10);
		}
		break;

	default:
		{		
			modelStack.PushMatrix();

			modelStack.Translate( currentLevel->m_cMap->GetNumOfTiles_Width() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos().x - currentLevel->m_cMap->GetTileSize() - theHero->GetMapOffset().x,
				currentLevel->m_cMap->GetNumOfTiles_Height() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos().y - currentLevel->m_cMap->GetTileSize() - theHero->GetMapOffset().y, 0);

			// Render the background image
			RenderBackground();
			// Render the Game Objects
			RenderGameObjects();
			// Render the zombie
			RenderEnemies();
			// Render the hero
			if(this->theHero->GetRenderHero())
			{
				RenderHero();
			}
			
			if(currentLevel != levelList[0])
				Render2DMesh(meshList[GEO_BLACK_HOLE], false, blackout.lightSize, theHero->GetPos().x + currentLevel->gameObjectsManager->tileSize * 0.5 - Application::getWindowWidth() * blackout.lightSize, theHero->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5 - Application::getWindowWidth() * blackout.lightSize);

			modelStack.PopMatrix();
			if(hackingGame.active)
			{
				RenderHackGame();
			}

			RenderGUI();
		}
		break;
	}
}

void SceneSP3::Exit()
{
	delete theHero;
	mysound.exiting();
	DeleteGoMeshes();
}

/********************************************************************************
Render the Hero. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderHero()
{
	switch (this->theHero->GetCurrentState())
	{
	case this->theHero->DYING:
		{
			if(this->theHero->GetCurrentPosNode()->posType == this->theHero->GetCurrentPosNode()->HOLE)
			{
				modelStack.PushMatrix();
				modelStack.Translate(theHero->GetPos().x,theHero->GetPos().y,0);
				modelStack.Translate(32,17,0);	
				modelStack.Scale(theHero->GetDropScale(), theHero->GetDropScale(), 1);
				modelStack.Translate(-32,-32,0);
				if(theHero->GetDropScale() > 0.3)
					Render2DMesh(theHero->deathMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, 0, 0, false);
				modelStack.PopMatrix();
			}
			else
				Render2DMesh(theHero->deathMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y, false);
		}
		break;
	case this->theHero->ATTACKING:
		{
			if(theHero->GetAnimationDirection() == theHero->DOWN)
			{
				Render2DMesh(theHero->attackFrontMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
			}
			else if(theHero->GetAnimationDirection() == theHero->UP)
			{
				Render2DMesh(theHero->attackBackMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
			}
			else
			{
				// Hero move right
				if(theHero->GetAnimationInvert() == false)
				{
					Render2DMesh(theHero->attackSideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
				}
				// Hero move left
				else
				{
					Render2DMesh(theHero->attackSideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y, true);
				}
			}
		}
		break;
	default:
		{
			if(theHero->GetAnimationDirection() == theHero->DOWN)
			{
				Render2DMesh(theHero->frontMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
			}
			else if(theHero->GetAnimationDirection() == theHero->UP)
			{
				Render2DMesh(theHero->backMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
			}
			else
			{
				// Hero move right
				if(theHero->GetAnimationInvert() == false)
				{
					Render2DMesh(theHero->sideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y);
				}
				// Hero move left
				else
				{
					Render2DMesh(theHero->sideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y, true);
				}
			}
		}
	}
}

/********************************************************************************
Render the Game  Objects. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderGameObjects()
{
	for(vector<GameObject *>::iterator it = currentLevel->gameObjectsManager->GoList.begin(); it != currentLevel->gameObjectsManager->GoList.end(); ++it)
	{
		GameObject* go = (GameObject*)*it;
		switch(go->type)
		{
		case GameObject::WALL:
			{
				//Render2DMesh(wallMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::HOLE:
			{
				Render2DMesh(holeMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::DOOR:
			{
				//Render2DMesh(doorMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::WET_FLOOR:
			{
				Render2DMesh(wetFloorMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::TIMING_DOOR:
			{
				Render2DMesh(timmingDoorMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::BLOCK:
			{
				ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(go);
				if(temp->active == true)
					Render2DMesh(blockMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::HACK_SYS:
			{
				Render2DMesh(hackMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case GameObject::HEALTH_PACK:
			{
				ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(go);
				if(temp->active == true)
					Render2DMesh(healthMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case GameObject::TRAP:
			{
				Render2DMesh(trapMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case GameObject::MOVE_UP:
			{
				Render2DMesh(arrowMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case GameObject::MOVE_DOWN:
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x + currentLevel->m_cMap->GetTileSize()*0.5, go->pos.y + currentLevel->m_cMap->GetTileSize()*0.5, 0);
				modelStack.Rotate(180, 0, 0, 1);
				modelStack.Translate(-currentLevel->m_cMap->GetTileSize()*0.5, -currentLevel->m_cMap->GetTileSize()*0.5, 0);
				Render2DMesh(arrowMesh[go->currentFrame], false, 1.0f);
				modelStack.PopMatrix();
				break;
			}
		case GameObject::MOVE_LEFT:
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x + currentLevel->m_cMap->GetTileSize()*0.5, go->pos.y + currentLevel->m_cMap->GetTileSize()*0.5, 0);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Translate(-currentLevel->m_cMap->GetTileSize()*0.5, -currentLevel->m_cMap->GetTileSize()*0.5, 0);
				Render2DMesh(arrowMesh[go->currentFrame], false, 1.0f);
				modelStack.PopMatrix();
				break;
			}
		case GameObject::MOVE_RIGHT:
			{
				modelStack.PushMatrix();
				modelStack.Translate(go->pos.x + currentLevel->m_cMap->GetTileSize()*0.5, go->pos.y + currentLevel->m_cMap->GetTileSize()*0.5, 0);
				modelStack.Rotate(270, 0, 0, 1);
				modelStack.Translate(-currentLevel->m_cMap->GetTileSize()*0.5, -currentLevel->m_cMap->GetTileSize()*0.5, 0);
				Render2DMesh(arrowMesh[go->currentFrame], false, 1.0f);
				modelStack.PopMatrix();
				break;
			}
		}
	}
}

/********************************************************************************
Render the Enemies. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderEnemies()
{
	// Render the enemies
	for(vector<CZombie *>::iterator it = currentLevel->AI_Manager->zombieList.begin(); it != currentLevel->AI_Manager->zombieList.end(); ++it)
	{
		CZombie *zombie = (CZombie *)*it;

		if(zombie->active)
		{
			if(zombie->GetAnimationDirection() == zombie->DOWN)
			{
				switch(zombie->zombie_type)
				{
				case CZombie::NORMAL:
					Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_FRONT_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::SMART:
					Render2DMesh(meshList[GEO_SMART_ZOMBIE_FRONT_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::TANK:
					Render2DMesh(meshList[GEO_TANK_ZOMBIE_FRONT_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::HUNTER:
					Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_FRONT_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				}
			}
			else if(zombie->GetAnimationDirection() == zombie->UP)
			{
				switch(zombie->zombie_type)
				{
				case CZombie::NORMAL:
					Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_BACK_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::SMART:
					Render2DMesh(meshList[GEO_SMART_ZOMBIE_BACK_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::TANK:
					Render2DMesh(meshList[GEO_TANK_ZOMBIE_BACK_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				case CZombie::HUNTER:
					Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_BACK_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
					break;
				}
			}
			else
			{
				// zombie move right
				if(zombie->GetAnimationInvert() == false)
				{
					switch(zombie->zombie_type)
					{
					case CZombie::NORMAL:
						Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
						break;
					case CZombie::SMART:
						Render2DMesh(meshList[GEO_SMART_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
						break;
					case CZombie::TANK:
						Render2DMesh(meshList[GEO_TANK_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
						break;
					case CZombie::HUNTER:
						Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y);
						break;
					}
				}
				// zombie move left
				else
				{
					switch(zombie->zombie_type)
					{
					case CZombie::NORMAL:
						Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, true);
						break;
					case CZombie::SMART:
						Render2DMesh(meshList[GEO_SMART_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, true);
						break;
					case CZombie::TANK:
						Render2DMesh(meshList[GEO_TANK_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, true);
						break;
					case CZombie::HUNTER:
						Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_SIDE_0 + (int)zombie->GetAnimationCounter()], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, true);
						break;
					}
				}
			}
			if(zombie->GetCurrentMode() == zombie->CHASE || zombie->GetCurrentMode() == zombie->ATTACK)
			{
				Render2DMesh(meshList[GEO_ZOMBIE_ALERT_SIGN], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize);
			}

			// Render ranges
			switch(zombie->zombie_type)
			{
			case CZombie::NORMAL:
				{
					modelStack.PushMatrix();
					
					modelStack.Translate(zombie->GetPos().x + currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, 0);
					modelStack.Rotate(180, 0, 1, 0);

					if(zombie->GetAnimationDirection() == CZombie::DOWN)
					{
						modelStack.Rotate(180, 0, 0, 1);
					}
					else if(zombie->GetAnimationDirection() == CZombie::LEFT)
					{
						modelStack.Rotate(-90, 0, 0, 1);
					}
					else if(zombie->GetAnimationDirection() == CZombie::RIGHT)
					{
						modelStack.Rotate(90, 0, 0, 1);
					}

					Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_ATTACK_RANGE], false, 1.0f, 0, 0);

					modelStack.PopMatrix();

					Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_REPEL_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
				}
				break;
			case CZombie::SMART:
				{
					modelStack.PushMatrix();
					
					modelStack.Translate(zombie->GetPos().x + currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, 0);
					modelStack.Rotate(180, 0, 1, 0);

					if(zombie->GetAnimationDirection() == CZombie::DOWN)
					{
						modelStack.Rotate(180, 0, 0, 1);
					}
					else if(zombie->GetAnimationDirection() == CZombie::LEFT)
					{
						modelStack.Rotate(-90, 0, 0, 1);
					}
					else if(zombie->GetAnimationDirection() == CZombie::RIGHT)
					{
						modelStack.Rotate(90, 0, 0, 1);
					}

					Render2DMesh(meshList[GEO_SMART_ZOMBIE_ATTACK_RANGE], false, 1.0f, 0,0);
					
					modelStack.PopMatrix();

					Render2DMesh(meshList[GEO_SMART_ZOMBIE_REPEL_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
				}break;
			case CZombie::TANK:
				{
					Render2DMesh(meshList[GEO_TANK_ZOMBIE_ATTACK_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
					Render2DMesh(meshList[GEO_TANK_ZOMBIE_REPEL_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
				}
				break;
			case CZombie::HUNTER:
				{
					Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_ATTACK_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
					Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_REPEL_RANGE], false, 1.0f, zombie->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, zombie->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
				}
				break;
			}
		}
		// Death
		else
		{
			switch(zombie->zombie_type)
			{
			case CZombie::NORMAL:
				Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_BACK_0], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, false, 90.f);
				break;
			case CZombie::SMART:
				Render2DMesh(meshList[GEO_SMART_ZOMBIE_BACK_0], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, false, 90.f);
				break;
			case CZombie::TANK:
				Render2DMesh(meshList[GEO_TANK_ZOMBIE_BACK_0], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, false, 90.f);
				break;
			case CZombie::HUNTER:
				Render2DMesh(meshList[GEO_HUNTER_ZOMBIE_BACK_0], false, 1.0f, zombie->GetPos().x, zombie->GetPos().y, false, 90.f);
				break;
			}
		}
	}
}

/********************************************************************************
Render the Enemies. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderGUI()
{
	RenderMeshIn2D(meshList[GEO_HEALTH_BAR], false, 2.f, -75 , 63);

	for(int i = 0; i < theHero->GetHealth(); ++i)
	{
		if(theHero->GetHealth() == 1)
			RenderMeshIn2D(meshList[GEO_LIVE_1], false, 1.0f, -58 + 5 * i, 72);
		if(theHero->GetHealth() == 2)
			RenderMeshIn2D(meshList[GEO_LIVE_2], false, 1.0f, -58 + 5 * i, 72);
		if(theHero->GetHealth() == 3)
			RenderMeshIn2D(meshList[GEO_LIVE_3], false, 1.0f, -58 + 5 * i, 72);
	}

	////////////////////////FLASHLIGHT UI BY IVAN DO NOT TOUCH//////////////////////////////////
	modelStack.PushMatrix();
	modelStack.Translate(268, 725, 0);
	modelStack.Scale(blackout.battery * 17.1 , 20, 0);
	if(blackout.fullyCharged)
		Render2DMesh(meshList[GEO_HACK_YELLOW_BAR], false, 1.f, 0 , 0);
	else
		Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.f, 0 , 0);
	modelStack.PopMatrix();
	Render2DMesh(meshList[GEO_FLASHLIGHT], false, 1.f, 260 , 650);
	////////////////////////////////////////////////////////////////////////////////////////////

	std::ostringstream time;
	time.precision(3);
	time << playerRecord.getTiming().getMin() << ":" << playerRecord.getTiming().getSec();
	RenderTextOnScreen(meshList[GEO_TEXT], time.str(), Color(1,1,1), 5.f, 40.f, 55.f);

	if(theHero->GetCurrentPosNode()->up->posType == CPosNode::BLOCK
		&& dynamic_cast<ActiveGameObject*>(theHero->GetCurrentPosNode()->up->gameObject)->active
		||theHero->GetCurrentPosNode()->down->posType == CPosNode::BLOCK
		&& dynamic_cast<ActiveGameObject*>(theHero->GetCurrentPosNode()->down->gameObject)->active
		||theHero->GetCurrentPosNode()->left->posType == CPosNode::BLOCK
		&& dynamic_cast<ActiveGameObject*>(theHero->GetCurrentPosNode()->left->gameObject)->active
		||theHero->GetCurrentPosNode()->right->posType == CPosNode::BLOCK
		&& dynamic_cast<ActiveGameObject*>(theHero->GetCurrentPosNode()->right->gameObject)->active)
	{
		modelStack.PushMatrix();
		modelStack.Translate(70, 200, 0);
		modelStack.Scale(890 , 95, 0);
		Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Find a hacking terminal", Color(1,1,1), 3.f, 7.f, 20.f);
		RenderTextOnScreen(meshList[GEO_TEXT], "to open this", Color(1,1,1), 3.f, 23.f, 16.f);
	}

	if(!hackingGame.active)
	{
		switch(this->theHero->GetAnimationDirection())
		{
		case this->theHero->UP:
			{
				if(this->theHero->GetCurrentPosNode()->up->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
				{
					modelStack.PushMatrix();
					modelStack.Translate(140, 250, 0);
					modelStack.Scale(755 , 45, 0);
					Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
					RenderTextOnScreen(meshList[GEO_TEXT], "Press space to hack", Color(1,1,1), 3.f, 13.f, 20.f);
				}
			}break;
		case this->theHero->DOWN:
			{
				if(this->theHero->GetCurrentPosNode()->down->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
				{
					modelStack.PushMatrix();
					modelStack.Translate(140, 250, 0);
					modelStack.Scale(755 , 45, 0);
					Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
					RenderTextOnScreen(meshList[GEO_TEXT], "Press space to hack", Color(1,1,1), 3.f, 13.f, 20.f);
				}
			}break;
		case this->theHero->LEFT:
			{
				if(this->theHero->GetCurrentPosNode()->left->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
				{
					modelStack.PushMatrix();
					modelStack.Translate(140, 250, 0);
					modelStack.Scale(755 , 45, 0);
					Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
					RenderTextOnScreen(meshList[GEO_TEXT], "Press space to hack", Color(1,1,1), 3.f, 13.f, 20.f);
				}
			}break;
		case this->theHero->RIGHT:
			{
				if(this->theHero->GetCurrentPosNode()->right->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
				{
					modelStack.PushMatrix();
					modelStack.Translate(140, 250, 0);
					modelStack.Scale(755 , 45, 0);
					Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
					RenderTextOnScreen(meshList[GEO_TEXT], "Press space to hack", Color(1,1,1), 3.f, 13.f, 20.f);
				}
			}break;
		}
	}
}

void SceneSP3::InitGoMeshes()
{
	wallMesh.push_back(MeshBuilder::Generate2DMesh("GEO_TILEGROUND", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	wallMesh.back()->textureID = LoadTGA("Image//tile1_ground.tga");

	holeMesh.push_back(MeshBuilder::Generate2DMesh("hole", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	holeMesh.back()->textureID = LoadTGA("Image//hole.tga");

	doorMesh.push_back(MeshBuilder::Generate2DMesh("door open", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	doorMesh.back()->textureID = LoadTGA("Image//door open.tga");

	wetFloorMesh.push_back(MeshBuilder::Generate2DMesh("water 0", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	wetFloorMesh.back()->textureID = LoadTGA("Image//water 0.tga");
	wetFloorMesh.push_back(MeshBuilder::Generate2DMesh("water 1", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	wetFloorMesh.back()->textureID = LoadTGA("Image//water 1.tga");
	wetFloorMesh.push_back(MeshBuilder::Generate2DMesh("water 2", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	wetFloorMesh.back()->textureID = LoadTGA("Image//water 2.tga");

	timmingDoorMesh.push_back(MeshBuilder::Generate2DMesh("door open", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	timmingDoorMesh.back()->textureID = LoadTGA("Image//door open.tga");
	timmingDoorMesh.push_back(MeshBuilder::Generate2DMesh("door closed", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	timmingDoorMesh.back()->textureID = LoadTGA("Image//door closed.tga");
	
	blockMesh.push_back(MeshBuilder::Generate2DMesh("block", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	blockMesh.back()->textureID = LoadTGA("Image//block.tga");

	hackMesh.push_back(MeshBuilder::Generate2DMesh("hack", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	hackMesh.back()->textureID = LoadTGA("Image//hack station.tga");

	healthMesh.push_back(MeshBuilder::Generate2DMesh("health", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	healthMesh.back()->textureID = LoadTGA("Image//health pack.tga");

	trapMesh.push_back(MeshBuilder::Generate2DMesh("trap", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	trapMesh.back()->textureID = LoadTGA("Image//trap 0.tga");
	trapMesh.push_back(MeshBuilder::Generate2DMesh("trap", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	trapMesh.back()->textureID = LoadTGA("Image//trap 1.tga");
	trapMesh.push_back(MeshBuilder::Generate2DMesh("trap", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	trapMesh.back()->textureID = LoadTGA("Image//trap 2.tga");
	trapMesh.push_back(MeshBuilder::Generate2DMesh("trap", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	trapMesh.back()->textureID = LoadTGA("Image//trap 3.tga");
	trapMesh.push_back(MeshBuilder::Generate2DMesh("trap", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	trapMesh.back()->textureID = LoadTGA("Image//trap 4.tga");/**/

	arrowMesh.push_back(MeshBuilder::Generate2DMesh("arrow", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	arrowMesh.back()->textureID = LoadTGA("Image//arrow arrow.tga");
}

void SceneSP3::DeleteGoMeshes()
{
	for(int i = 0; i < wallMesh.size(); i++)
	{
		if(wallMesh[i])
		{
			delete wallMesh[i];
			wallMesh[i] = NULL;
		}
	}
	for(int i = 0; i < holeMesh.size(); i++)
	{
		if(holeMesh[i])
		{
			delete holeMesh[i];
			holeMesh[i] = NULL;
		}
	}
	for(int i = 0; i < healthMesh.size(); i++)
	{
		if(healthMesh[i])
		{
			delete healthMesh[i];
			healthMesh[i] = NULL;
		}
	}
	for(int i = 0; i < doorMesh.size(); i++)
	{
		if(doorMesh[i])
		{
			delete doorMesh[i];
			doorMesh[i] = NULL;
		}
	}
	for(int i = 0; i < wetFloorMesh.size(); i++)
	{
		if(wetFloorMesh[i])
		{
			delete wetFloorMesh[i];
			wetFloorMesh[i] = NULL;
		}
	}
	for(int i = 0; i < timmingDoorMesh.size(); i++)
	{
		if(timmingDoorMesh[i])
		{
			delete timmingDoorMesh[i];
			timmingDoorMesh[i] = NULL;
		}
	}
	for(int i = 0; i < blockMesh.size(); i++)
	{
		if(blockMesh[i])
		{
			delete blockMesh[i];
			blockMesh[i] = NULL;
		}
	}
	for(int i = 0; i < hackMesh.size(); i++)
	{
		if(hackMesh[i])
		{
			delete hackMesh[i];
			hackMesh[i] = NULL;
		}
	}
}

void SceneSP3::UpdateActiveGO(double dt)
{
	for(int i = 0; i < currentLevel->gameObjectsManager->UpdatableGoList.size(); ++i)
	{
		switch(currentLevel->gameObjectsManager->UpdatableGoList[i]->type)
		{
		case GameObject::WET_FLOOR:
			{
				if(currentLevel->gameObjectsManager->UpdatableGoList[i]->CheckColision(theHero->GetPos(), currentLevel->gameObjectsManager->tileSize))
				{
					if(currentLevel->gameObjectsManager->UpdatableGoList[i]->soundPlayed == false)
					{
						mysound.playSound(Sound::WATER_SPLASH);
						currentLevel->gameObjectsManager->UpdatableGoList[i]->soundPlayed = true;
					}
					currentLevel->gameObjectsManager->UpdatableGoList[i]->active = true;
				}
				else
				{
					currentLevel->gameObjectsManager->UpdatableGoList[i]->soundPlayed = false;
					currentLevel->gameObjectsManager->UpdatableGoList[i]->canActivate = true;
				}
				break;
			}
		case GameObject::TRAP:
			{
				if(currentLevel->gameObjectsManager->UpdatableGoList[i]->CheckColision(theHero->GetPos(), currentLevel->gameObjectsManager->tileSize))
				{
					if(currentLevel->gameObjectsManager->UpdatableGoList[i]->soundPlayed == false && !theHero->GetJustGotDamged() == true)
					{
						mysound.playSound(Sound::TRAP);
						if(theHero->GetHealth()-1 <= 0)
							mysound.playSound(Sound::PLAYER_DYING);
						else
							mysound.playSound(Sound::PLAYER_DAMAGED);
						currentLevel->gameObjectsManager->UpdatableGoList[i]->soundPlayed = true;
					}
				}
			}
		}
		currentLevel->gameObjectsManager->UpdatableGoList[i]->update(dt);
	}
}

void SceneSP3::RenderHackGame()
{
	Render2DMesh(meshList[GEO_HACK_WINDOW], false, 1.0f, 112, 100);

	modelStack.PushMatrix();
    modelStack.Translate(hackingGame.bottomLeftPos.x,hackingGame.bottomLeftPos.y, 0);
	modelStack.Scale(hackingGame.topRightPos.x - hackingGame.bottomLeftPos.x, hackingGame.topRightPos.y - hackingGame.bottomLeftPos.y, 1);
	Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.0f, 0, 0);
	modelStack.PopMatrix();

	for(int i = 0; i < 8; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(hackingGame.hackingBar[i]->bottomPos.x - 15,hackingGame.hackingBar[i]->topPos.y, 0);
		if(i == hackingGame.currentBar)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-2,-1.7, 0);
			modelStack.Scale(34, 94, 1);
			Render2DMesh(meshList[GEO_HACK_YELLOW_BAR], false, 1.0f, 0, 0);
			modelStack.PopMatrix();
		}
		modelStack.Scale(30, 90, 1);
		Render2DMesh(meshList[GEO_HACK_WHITE_BAR], false, 1.0f, 0, 0);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(hackingGame.hackingBar[i]->bottomPos.x - 15,hackingGame.hackingBar[i]->bottomPos.y - 90, 0);
		if(i == hackingGame.currentBar)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-2,-1.7, 0);
			modelStack.Scale(34, 94, 1);
			Render2DMesh(meshList[GEO_HACK_YELLOW_BAR], false, 1.0f, 0, 0);
			modelStack.PopMatrix();
		}
		modelStack.Scale(30, 90, 1);
		Render2DMesh(meshList[GEO_HACK_WHITE_BAR], false, 1.0f, 0, 0);
		modelStack.PopMatrix();
	}

}