#include "SceneSP3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

ISoundEngine * engine;

SceneSP3::SceneSP3()
	: gameState(MAINMENU)
	, highscore(0)
	, choice(NONE)
	, currentLevel(NULL)
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
	
	meshList[GEO_ATTACK_RANGE] = MeshBuilder::GenerateRing("ATTACK_RANGE", Color(0, 1, 0), 36.f, levelList[0]->AI_Manager->enemiesList[0]->GetMaxRangeToDetect(), levelList[0]->AI_Manager->enemiesList[0]->GetMaxRangeToDetect() - 1.f);
	meshList[GEO_REPEL_RANGE] = MeshBuilder::GenerateRing("REPEL_RANGE", Color(1, 0, 0), 36.f, levelList[0]->gameObjectsManager->tileSize * 0.5, levelList[0]->gameObjectsManager->tileSize * 0.5 - 1.f);

	InitSound();
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
	const int noOfLevel = 1;
	for(int i = 0; i < noOfLevel; i++)
	{
		levelList.push_back(new Level);
		levelList[i]->m_cMap = new CMap();
		levelList[i]->m_cMap->Init( 768 + 64, 1024, 12 + 1, 16, 3200 + 64, 2048, 64);
	}

	// Level 1
	levelList[0]->m_cMap->LoadMap( "Image//MapDesignLv1.csv" );
	// Level 5
	//levelList[4]->m_cMap->LoadMap( "Image//MapDesignLv5.csv" );
	// Level 6
	//levelList[5]->m_cMap->LoadMap( "Image//MapDesignLv6.csv" );
	
	for(int i = 0; i < noOfLevel; i++)
	{
		levelList[i]->background = MeshBuilder::Generate2DMesh("GEO_BACKGROUND_LEVEL1", Color(1, 1, 1), 0.0f, 0.0f, 2048, 3200);
		levelList[i]->background->textureID = LoadTGA("Image//background_level1.tga");
		levelList[i]->sideView = false;

		levelList[i]->gameObjectsManager = new GameObjectFactory;
		levelList[i]->gameObjectsManager->generateGO(levelList[i]->m_cMap);

		levelList[i]->AI_Manager = new CAIManager;
		levelList[i]->AI_Manager->generateEnemies(levelList[i]->m_cMap);

		levelList[i]->LevelMap_Nodes = new CLevelMap_Nodes;
		levelList[i]->LevelMap_Nodes->GenerateNodes(levelList[i]->m_cMap, levelList[i]->AI_Manager, levelList[i]->gameObjectsManager);

		levelList[i]->HeroStartPosNode = levelList[i]->LevelMap_Nodes->FindHeroInitialNode();
	}
}

int SceneSP3::InitSound()
{
	engine = createIrrKlangDevice();

	if (!engine)
		return 0;

	return 0;
}

void SceneSP3::UpdateInputs(double dt)
{
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
			}
		}

		if(Application::IsKeyPressed('F'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->attackingEnabled();
			}
		}

		// Check Collision of th hero before moving up
		if(Application::IsKeyPressed('W'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL 
				&& gameState == PLAYING)
			{
				this->theHero->MoveUpDown(true, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
			}
		}
		// Check Collision of th hero before moving down
		else if(Application::IsKeyPressed('S'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveUpDown(false, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
			}
		}

		// Check Collision of th hero before moving left
		else if(Application::IsKeyPressed('A'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveLeftRight(true, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
			}
		}
		// Check Collision of th hero before moving right

		else if(Application::IsKeyPressed('D'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->NIL
				&& gameState == PLAYING)
			{
				this->theHero->MoveLeftRight(false, currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
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
				hackingGame.Input(dt);
			else
			{
				switch(this->theHero->GetAnimationDirection())
				{
				case this->theHero->UP:
					{
						if(this->theHero->GetCurrentPosNode()->up->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
							hackingGame.active = true;
						
					}break;
				case this->theHero->DOWN:
					{
						if(this->theHero->GetCurrentPosNode()->down->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
							hackingGame.active = true;
						
					}break;
				case this->theHero->LEFT:
					{
						if(this->theHero->GetCurrentPosNode()->left->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
							hackingGame.active = true;
						
					}break;
				case this->theHero->RIGHT:
					{
						if(this->theHero->GetCurrentPosNode()->right->posType == this->theHero->GetCurrentPosNode()->HACK_SYS)
							hackingGame.active = true;
						
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
		// Choose play
		if(Application::IsKeyPressed(VK_UP) && upkey == false)
		{
			if(gameState == PAUSE || gameState == MAINMENU)
			{
				if(choice != PLAY)
				{
					choice = PLAY;
				}
				engine->play2D("../media/click-click-mono.wav");
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
				engine->play2D("../media/click-click-mono.wav");
			}
			else if(gameState == MAINMENU)
			{
				if(choice != EXIT)
				{
					choice = EXIT;
				}
				engine->play2D("../media/click-click-mono.wav");
			}
			downkey = true;
		}
		else if(Application::IsKeyPressed(VK_DOWN) == false && downkey == true)
		{
			downkey = false;
		}
		// Confirm choice
		else if(Application::IsKeyPressed(VK_RETURN))
		{
			if(gameState == PAUSE)
			{
				if(choice == PLAY)
				{
					gameState = PLAYING;
				}
				else if(choice == QUIT)
				{
					gameState = MAINMENU;
					this->theHero->Reset();
					this->theHero->SetCurrentState(this->theHero->NIL);
					clock.Reset();
					currentLevel->AI_Manager->Reset();
				}
				choice = NONE;
			}
			else if(gameState == MAINMENU)
			{
				if(choice == PLAY)
				{
					choice = NONE;
					gameState = PLAYING;
					currentLevel = levelList[0];
					theHero->SetPos(currentLevel->HeroStartPosNode->pos);
					theHero->SetInitialPosNode(currentLevel->HeroStartPosNode);
					theHero->SetCurrentPosNode(currentLevel->HeroStartPosNode);
					theHero->SetTargetPosNode(currentLevel->HeroStartPosNode);
				}
			}
			else if(gameState == GAMEOVER)
			{
				gameState = MAINMENU;
				this->theHero->Reset();
				clock.Reset();
				this->theHero->SetCurrentState(this->theHero->NIL);
				currentLevel->AI_Manager->Reset();
			}
		}
	}
}

void SceneSP3::RenderHighscore()
{
	// string playername;
	// cout << "Enter your name: " << endl;
	// cin >> playername;

	//RenderTextOnScreen(meshList[GEO_TEXT], );
}

void SceneSP3::Update(double dt)
{
	UpdateInputs(dt);

	if(gameState == PLAYING)
	{
		if(this->theHero->GetCurrentState() != this->theHero->DYING && this->theHero->GetCurrentState() != this->theHero->EXITING)
		{
			clock.update(dt);
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
							gameState = GAMEOVER;
							break;
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
				theHero->SetTimeElasped(0.0f);
			}
		}

		theHero->HeroUpdate(dt, currentLevel->AI_Manager, currentLevel->gameObjectsManager, currentLevel->m_cMap);

		//Enemies
		for(vector<CEnemy *>::iterator it = currentLevel->AI_Manager->enemiesList.begin(); it != currentLevel->AI_Manager->enemiesList.end(); ++it)
		{
			CEnemy *enemy = (CEnemy *)*it;
			if(enemy->active)
			{
				enemy->Update(currentLevel->gameObjectsManager->tileSize, dt, theHero->GetCurrentPosNode(), theHero->GetPos());
				if(enemy->GetHitHero())
				{
					if(!this->theHero->GetJustGotDamged() && this->theHero->GetCurrentState() != CPlayerInfo::DYING)
					{
						this->theHero->SetHealth(theHero->GetHealth() - 1);
						if(theHero->GetHealth() <= 0)
						{
							this->theHero->SetCurrentState(CPlayerInfo::DYING);
							theHero->SetAnimationCounter(0.0f);
						}
						else
						{
							this->theHero->knockBackEnabled(enemy->GetVel(), currentLevel->AI_Manager, currentLevel->gameObjectsManager->tileSize);
							this->theHero->SetJustGotDamged(true);
						}
					}
					enemy->SetHitHero(false);
					break;
				}
			}
		}
		if(hackingGame.active)
		{
			hackingGame.Update(dt);
			if(hackingGame.currentBar == hackingGame.hackingBar.size() || theHero->GetCurrentState() != theHero->NIL)
			{
				if(hackingGame.currentBar == hackingGame.hackingBar.size())
				{
					for(int i = 0; i < currentLevel->gameObjectsManager->UpdatableGoList.size(); ++i)
					{
						if(currentLevel->gameObjectsManager->UpdatableGoList[i]->type == GameObject::LOCKED_DOOR)
						{
							if(currentLevel->gameObjectsManager->UpdatableGoList[i]->type == GameObject::LOCKED_DOOR)
							{
								currentLevel->gameObjectsManager->UpdatableGoList[i]->active = true;
								break;
							}
							currentLevel->gameObjectsManager->UpdatableGoList[i]->active = true;
						}
					}
				}
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
	static bool soundplayed = false;
	glDisable(GL_DEPTH_TEST);
	switch(gameState)
	{
	
	case MAINMENU:
		{		
			Render2DMesh(meshList[GEO_MAINMENU], false);
			
			//On screen text
			RenderTextOnScreen(meshList[GEO_TEXT], "START GAME", Color(1, 1, 1), 5, 25, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "EXIT", Color(1, 1, 1), 5, 25, 10);
			if(choice == PLAY)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 15);
			}
			else if(choice == EXIT)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 10);
			}
			if(!soundplayed && gameState == MAINMENU)        // main menu sound
			{
				engine->play2D("../media/FFX Otherworld.mp3");
				soundplayed = true;
			}
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
	case GAMEOVER:
		{
			Render2DMesh(meshList[GEO_GAMEOVER], false);
			RenderHighscore();	
			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(1, 1, 1), 2.5, 13, 5);
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
			if(blackout.blackout)
			{
				if(blackout.lightSize > 1)
					Render2DMesh(meshList[GEO_BLACK_HOLE], false, blackout.lightSize, theHero->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, theHero->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
				else
					Render2DMesh(meshList[GEO_BLACK], false, 1.0f, -(currentLevel->m_cMap->GetNumOfTiles_Width() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos().x - currentLevel->m_cMap->GetTileSize() - theHero->GetMapOffset().x), -(currentLevel->m_cMap->GetNumOfTiles_Height() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos().y - currentLevel->m_cMap->GetTileSize() - theHero->GetMapOffset().y));
			}
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
	engine->stopAllSounds();
	DeleteGoMeshes();
}

/********************************************************************************
Render the Hero. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderHero()
{
	switch (this->theHero->GetCurrentState())
	{
	case this->theHero->EXITING:
		{
			Render2DMesh(theHero->backMeshes[0], false, 1.0f, theHero->GetPos().x, theHero->GetPos().y, false);
		}
		break;
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
				Render2DMesh(wallMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::HOLE:
			{
				Render2DMesh(holeMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
				break;
			}
		case  GameObject::DOOR:
			{
				Render2DMesh(doorMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
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
		case  GameObject::LOCKED_DOOR:
			{
				Render2DMesh(lockedDoorMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
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
		case GameObject::FIRE:
			{
				Render2DMesh(fireMesh[go->currentFrame], false, 1.0f, go->pos.x, go->pos.y);
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
	for(vector<CEnemy *>::iterator it = currentLevel->AI_Manager->enemiesList.begin(); it != currentLevel->AI_Manager->enemiesList.end(); ++it)
	{
		CEnemy *enemy = (CEnemy *)*it;

		if(enemy->active)
		{
			if(enemy->GetAnimationDirection() == enemy->DOWN)
			{
				Render2DMesh(meshList[GEO_ENEMY_FRONT_0 + (int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos().x, enemy->GetPos().y);
			}
			else if(enemy->GetAnimationDirection() == enemy->UP)
			{
				Render2DMesh(meshList[GEO_ENEMY_BACK_0 + (int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos().x, enemy->GetPos().y);
			}
			else
			{
				// enemy move right
				if(enemy->GetAnimationInvert() == false)
				{
					Render2DMesh(meshList[GEO_ENEMY_SIDE_0 + (int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos().x, enemy->GetPos().y);
				}
				// enemy move left
				else
				{

					Render2DMesh(meshList[GEO_ENEMY_SIDE_0 + (int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos().x, enemy->GetPos().y, true);
				}
			}
			if(enemy->GetCurrentMode() == enemy->CHASE || enemy->GetCurrentMode() == enemy->ATTACK)
			{
				Render2DMesh(meshList[GEO_ENEMY_ALERT_SIGN], false, 1.0f, enemy->GetPos().x, enemy->GetPos().y + currentLevel->gameObjectsManager->tileSize);
			}

			// Render ranges
			Render2DMesh(meshList[GEO_ATTACK_RANGE], false, 1.0f, enemy->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, enemy->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
			Render2DMesh(meshList[GEO_REPEL_RANGE], false, 1.0f, enemy->GetPos().x - currentLevel->gameObjectsManager->tileSize * 0.5, enemy->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, true);
		}
		else
		{
			Render2DMesh(meshList[GEO_ENEMY_BACK_0], false, 1.0f, enemy->GetPos().x + currentLevel->gameObjectsManager->tileSize * 0.5, enemy->GetPos().y + currentLevel->gameObjectsManager->tileSize * 0.5, false, 90.f);
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
			RenderMeshIn2D(meshList[GEO_LIVE_1], false, 1.0f, -69 + 7 * i, 69.5);
		if(theHero->GetHealth() == 2)
			RenderMeshIn2D(meshList[GEO_LIVE_2], false, 1.0f, -69 + 7 * i, 69.5);
		if(theHero->GetHealth() == 3)
			RenderMeshIn2D(meshList[GEO_LIVE_3], false, 1.0f, -69 + 7 * i, 69.5);
	}

	////////////////////////FLASHLIGHT UI BY IVAN DO NOT TOUCH//////////////////////////////////
	modelStack.PushMatrix();
	modelStack.Translate(260, 703, 0);
	modelStack.Scale(blackout.battery * 45 , 65, 0);
	if(blackout.fullyCharged)
		Render2DMesh(meshList[GEO_HACK_YELLOW_BAR], false, 1.f, 0 , 0);
	else
		Render2DMesh(meshList[GEO_HACK_RED_BAR], false, 1.f, 0 , 0);
	modelStack.PopMatrix();
	Render2DMesh(meshList[GEO_FLASHLIGHT], false, 1.f, 260 , 703);
	////////////////////////////////////////////////////////////////////////////////////////////

	std::ostringstream time;
	time.precision(3);
	time << clock.getMin() << ":" << clock.getSec();
	RenderTextOnScreen(meshList[GEO_TEXT], time.str(), Color(1,1,1), 5.f, 40.f, 55.f);


	//On screen text
	/*std::ostringstream ss;
	ss.precision(3);
	ss << "X" << theHero->GetHealth();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3, 3, 57);*/
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
	
	lockedDoorMesh.push_back(MeshBuilder::Generate2DMesh("door open", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	lockedDoorMesh.back()->textureID = LoadTGA("Image//door open.tga");
	lockedDoorMesh.push_back(MeshBuilder::Generate2DMesh("door locked", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	lockedDoorMesh.back()->textureID = LoadTGA("Image//door locked.tga");

	hackMesh.push_back(MeshBuilder::Generate2DMesh("hack", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	hackMesh.back()->textureID = LoadTGA("Image//hack station.tga");

	healthMesh.push_back(MeshBuilder::Generate2DMesh("health", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	healthMesh.back()->textureID = LoadTGA("Image//health pack.tga");

	fireMesh.push_back(MeshBuilder::Generate2DMesh("fire", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	fireMesh.back()->textureID = LoadTGA("Image//fire 0.tga");
	fireMesh.push_back(MeshBuilder::Generate2DMesh("fire", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	fireMesh.back()->textureID = LoadTGA("Image//fire 1.tga");
	fireMesh.push_back(MeshBuilder::Generate2DMesh("fire", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	fireMesh.back()->textureID = LoadTGA("Image//fire 2.tga");
	fireMesh.push_back(MeshBuilder::Generate2DMesh("fire", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	fireMesh.back()->textureID = LoadTGA("Image//fire 3.tga");
	fireMesh.push_back(MeshBuilder::Generate2DMesh("fire", Color(1, 1, 1), 0.0f, 0.0f, 64.0f, 64.0f));
	fireMesh.back()->textureID = LoadTGA("Image//fire 4.tga");

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
	for(int i = 0; i < lockedDoorMesh.size(); i++)
	{
		if(lockedDoorMesh[i])
		{
			delete lockedDoorMesh[i];
			lockedDoorMesh[i] = NULL;
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
					currentLevel->gameObjectsManager->UpdatableGoList[i]->active = true;
				else
					currentLevel->gameObjectsManager->UpdatableGoList[i]->canActivate = true;

				break;
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