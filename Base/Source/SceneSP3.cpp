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
	InitLevels();
	InitSound();
}

void SceneSP3::InitHero()
{
	// Initialise the hero's position
	theHero = new CPlayerInfo();
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_SIDE", 32.0f, 32.0f, 21, 13, 0, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_SIDE", 32.0f, 32.0f, 21, 13, 1, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_SIDE", 32.0f, 32.0f, 21, 13, 2, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_SIDE", 32.0f, 32.0f, 21, 13, 3, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_SIDE", 32.0f, 32.0f, 21, 13, 4, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_SIDE", 32.0f, 32.0f, 21, 13, 5, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_SIDE", 32.0f, 32.0f, 21, 13, 6, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_SIDE", 32.0f, 32.0f, 21, 13, 7, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_SIDE", 32.0f, 32.0f, 21, 13, 8, 11));
	theHero->sideMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_FRONT", 32.0f, 32.0f, 21, 13, 0, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_FRONT", 32.0f, 32.0f, 21, 13, 1, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_FRONT", 32.0f, 32.0f, 21, 13, 2, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_FRONT", 32.0f, 32.0f, 21, 13, 3, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_FRONT", 32.0f, 32.0f, 21, 13, 4, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_FRONT", 32.0f, 32.0f, 21, 13, 5, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_FRONT", 32.0f, 32.0f, 21, 13, 6, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_FRONT", 32.0f, 32.0f, 21, 13, 7, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_FRONT", 32.0f, 32.0f, 21, 13, 8, 10));
	theHero->frontMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_BACK", 32.0f, 32.0f, 21, 13, 0, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_BACK", 32.0f, 32.0f, 21, 13, 1, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_BACK", 32.0f, 32.0f, 21, 13, 2, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_BACK", 32.0f, 32.0f, 21, 13, 3, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_BACK", 32.0f, 32.0f, 21, 13, 4, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_BACK", 32.0f, 32.0f, 21, 13, 5, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME6_BACK", 32.0f, 32.0f, 21, 13, 6, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME7_BACK", 32.0f, 32.0f, 21, 13, 7, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME8_BACK", 32.0f, 32.0f, 21, 13, 8, 8));
	theHero->backMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_DEATH", 32.0f, 32.0f, 21, 13, 0, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_DEATH", 32.0f, 32.0f, 21, 13, 1, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_DEATH", 32.0f, 32.0f, 21, 13, 2, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_DEATH", 32.0f, 32.0f, 21, 13, 3, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_DEATH", 32.0f, 32.0f, 21, 13, 4, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");
	theHero->deathMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_DEATH", 32.0f, 32.0f, 21, 13, 5, 20));
	theHero->deathMeshes.back()->textureID = LoadTGA("Image//hero_office.tga");

	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 0, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 1, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 2, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 3, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 4, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackFrontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_FRONT", 32.0f, 32.0f, 4, 6, 5, 2));
	theHero->attackFrontMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");

	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 0, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 1, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 2, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 3, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 4, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackBackMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_BACK", 32.0f, 32.0f, 4, 6, 5, 0));
	theHero->attackBackMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");

	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME0_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 0, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME1_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 1, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME2_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 2, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME3_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 3, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME4_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 4, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
	theHero->attackSideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_HERO_FRAME5_ATTACK_SIDE", 32.0f, 32.0f, 4, 6, 5, 3));
	theHero->attackSideMeshes.back()->textureID = LoadTGA("Image//hero_office_attack.tga");
}

void SceneSP3::InitLevels()
{
	// Initialise and load the tile map
	levelList.push_back(new Level);
	levelList[0]->m_cMap = new CMap();
	levelList[0]->m_cMap->Init( 80 + 32, 1024, 25 + 1, 32, 1600 + 32, 1024);
	levelList[0]->m_cMap->LoadMap( "Image//MapDesignLv1.csv" );
	levelList[0]->background = MeshBuilder::Generate2DMesh("GEO_BACKGROUND_LEVEL1", Color(1, 1, 1), 0.0f, 0.0f, 1024.0f, 1600);
	levelList[0]->background->textureID = LoadTGA("Image//background_level1.tga");
	levelList[0]->sideView = false;

	levelList[0]->gameObjectsManager = new GameObjectFactory;
	levelList[0]->gameObjectsManager->generateGO(levelList[0]->m_cMap);

	levelList[0]->AI_Manager = new CAIManager;
	levelList[0]->AI_Manager->generateEnemies(levelList[0]->m_cMap);
	levelList[0]->AI_Manager->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME0_SIDE", 32.0f, 32.0f, 4, 4, 0, 3));
	levelList[0]->AI_Manager->sideMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME1_SIDE", 32.0f, 32.0f, 4, 4, 1, 3));
	levelList[0]->AI_Manager->sideMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME2_SIDE", 32.0f, 32.0f, 4, 4, 2, 3));
	levelList[0]->AI_Manager->sideMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->sideMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME3_SIDE", 32.0f, 32.0f, 4, 4, 3, 3));
	levelList[0]->AI_Manager->sideMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	
	levelList[0]->AI_Manager->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME0_FRONT", 32.0f, 32.0f, 4, 4, 0, 1));
	levelList[0]->AI_Manager->frontMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME1_FRONT", 32.0f, 32.0f, 4, 4, 1, 1));
	levelList[0]->AI_Manager->frontMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME2_FRONT", 32.0f, 32.0f, 4, 4, 2, 1));
	levelList[0]->AI_Manager->frontMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->frontMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME3_FRONT", 32.0f, 32.0f, 4, 4, 3, 1));
	levelList[0]->AI_Manager->frontMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	
	levelList[0]->AI_Manager->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME0_BACK", 32.0f, 32.0f, 4, 4, 0, 0));
	levelList[0]->AI_Manager->backMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME1_BACK", 32.0f, 32.0f, 4, 4, 1, 0));
	levelList[0]->AI_Manager->backMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME2_BACK", 32.0f, 32.0f, 4, 4, 2, 0));
	levelList[0]->AI_Manager->backMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	levelList[0]->AI_Manager->backMeshes.push_back(MeshBuilder::GeneratePartOfSpriteSheet2D("TILE_ENEMY_FRAME3_BACK", 32.0f, 32.0f, 4, 4, 3, 0));
	levelList[0]->AI_Manager->backMeshes.back()->textureID = LoadTGA("Image//tile_zombie.tga");
	
	levelList[0]->AI_Manager->alertSign = MeshBuilder::Generate2DMesh("GEO_ALERT", Color(1, 1, 1), 0.0f, 0.0f, 32.0f, 32.0f);
	levelList[0]->AI_Manager->alertSign->textureID = LoadTGA("Image//alert_sign.tga");

	for(int index = 0; index < levelList.size(); index++)
	{
		vector<Vector3> enemyInitialPos;
		for(int i = 0; i < levelList[index]->m_cMap->getNumOfTiles_MapHeight(); i ++)
		{
			for(int k = 0; k < levelList[index]->m_cMap->getNumOfTiles_MapWidth() + 1; k ++)
			{
				// If we have reached the right side of the Map, then do not display the extra column of tiles.
				if((k) >= levelList[index]->m_cMap->getNumOfTiles_MapWidth())
					break;
				else if (levelList[index]->m_cMap->theScreenMap[i][k] == 20)
				{
					levelList[index]->HeroStartPos.x = k * levelList[index]->m_cMap->GetTileSize();
					levelList[index]->HeroStartPos.y = (levelList[index]->m_cMap->getNumOfTiles_MapHeight() - i - 1) * levelList[index]->m_cMap->GetTileSize();
					break;
				}
			}
		}
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
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && gameState == PLAYING)
			{
				gameState = PAUSE;
			}
		}

		if(Application::IsKeyPressed('F'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING
				&& gameState == PLAYING
				&& !this->theHero->GetIsKnockingBack()
				&& !this->theHero->GetIsAttacking()
				&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y()))
			{
				Vector3 attackPos = Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y());
				if(this->theHero->GetAnimationDirection() == this->theHero->UP)
				{
					attackPos.y += currentLevel->gameObjectsManager->tileSize;
				}
				else if(this->theHero->GetAnimationDirection() == this->theHero->DOWN)
				{
					attackPos.y -= currentLevel->gameObjectsManager->tileSize;
				}
				else if(this->theHero->GetAnimationDirection() == this->theHero->RIGHT)
				{
					attackPos.x += currentLevel->gameObjectsManager->tileSize;
				}
				else if(this->theHero->GetAnimationDirection() == this->theHero->LEFT)
				{
					attackPos.x -= currentLevel->gameObjectsManager->tileSize;
				}
				this->theHero->attackingEnabled(attackPos);
			}
		}

		// Check Collision of th hero before moving up
		if(Application::IsKeyPressed('W'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING 
				&& gameState == PLAYING
				&& !this->theHero->GetIsKnockingBack()
				&& !this->theHero->GetIsAttacking()
				&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y()))
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y() + currentLevel->gameObjectsManager->tileSize));

				HeroColision(goCollidedWith, true, true, dt);
			}
		}
		// Check Collision of th hero before moving down
		else if(Application::IsKeyPressed('S'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING
				&& gameState == PLAYING
				&& !this->theHero->GetIsKnockingBack()
				&& !this->theHero->GetIsAttacking()
				&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y()))
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y() - currentLevel->gameObjectsManager->tileSize));

				HeroColision(goCollidedWith, true, false, dt);
			}
		}

		// Check Collision of th hero before moving left
		else if(Application::IsKeyPressed('A'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING
				&& gameState == PLAYING
				&& !this->theHero->GetIsKnockingBack()
				&& !this->theHero->GetIsAttacking()
				&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y()))
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x() - currentLevel->gameObjectsManager->tileSize, this->theHero->GetPos_y()));

				HeroColision(goCollidedWith, false, true, dt);
			}
		}
		// Check Collision of th hero before moving right
		
		else if(Application::IsKeyPressed('D'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING
				&& gameState == PLAYING
				&& !this->theHero->GetIsKnockingBack()
				&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y()))
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x() + currentLevel->gameObjectsManager->tileSize, this->theHero->GetPos_y()));

				HeroColision(goCollidedWith, false, false, dt);
			}
		}

		if(!Application::IsKeyPressed('W') && !Application::IsKeyPressed('A') && !Application::IsKeyPressed('S') && !Application::IsKeyPressed('D') && !Application::IsKeyPressed('F')
			&& gameState == PLAYING
			&& !this->theHero->GetIsKnockingBack()
			&& !this->theHero->GetIsAttacking()
			&& Vector3(this->theHero->GetPos_x(),this->theHero->GetPos_y()) == Vector3(this->theHero->GetTargetPos_x(),this->theHero->GetTargetPos_y())
			&& this->theHero->GetCurrentState() != this->theHero->DYING)
		{
			this->theHero->SetAnimationCounter(0.0f);
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
					this->theHero->SetCurrentState(this->theHero->PLAYING);
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
					theHero->SetPos_x(currentLevel->HeroStartPos.x);
					theHero->SetPos_y(currentLevel->HeroStartPos.y);
					theHero->SetInitialPos_x(currentLevel->HeroStartPos.x);
					theHero->SetInitialPos_y(currentLevel->HeroStartPos.y);
					theHero->SetTargetPos_x(currentLevel->HeroStartPos.x);
					theHero->SetTargetPos_y(currentLevel->HeroStartPos.y);
				}
			}
			else if(gameState == GAMEOVER)
			{
				gameState = MAINMENU;
				this->theHero->Reset();
				this->theHero->SetCurrentState(this->theHero->PLAYING);
				currentLevel->AI_Manager->Reset();
			}
		}
	}
}

void SceneSP3::Update(double dt)
{
	UpdateInputs(dt);
	if(gameState == PLAYING)
	{
		if(this->theHero->GetCurrentState() != this->theHero->DYING)
		{
			switch (this->theHero->GetCurrentState())
			{
			case this->theHero->EXITING:
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
									theHero->SetPos_x(currentLevel->HeroStartPos.x);
									theHero->SetPos_y(currentLevel->HeroStartPos.y);
									theHero->SetInitialPos_x(currentLevel->HeroStartPos.x);
									theHero->SetInitialPos_y(currentLevel->HeroStartPos.y);
									theHero->SetTargetPos_x(currentLevel->HeroStartPos.x);
									theHero->SetTargetPos_x(currentLevel->HeroStartPos.y);
									this->theHero->SetCurrentState(this->theHero->PLAYING);
									this->theHero->SetTimeElasped( 0.f );
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
				break;
			}

			theHero->HeroUpdate(dt, currentLevel->AI_Manager, currentLevel->gameObjectsManager);

			//Enemies
			for(vector<CEnemy *>::iterator it = currentLevel->AI_Manager->enemiesList.begin(); it != currentLevel->AI_Manager->enemiesList.end(); ++it)
			{
				CEnemy *enemy = (CEnemy *)*it;
				enemy->Update(currentLevel->gameObjectsManager, dt, Vector3(theHero->GetPos_x(), theHero->GetPos_y()));
				if(enemy->GetHitHero())
				{
					this->theHero->SetHealth(theHero->GetHealth() - 1);
					if(theHero->GetHealth() == 0)
					{
						this->theHero->SetCurrentState(this->theHero->DYING);
						theHero->SetAnimationCounter(0.0f);
					}
					else
					{
						Vector3 knockBackPos = Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y());
						if(this->theHero->GetPos_x() != enemy->GetPos_x())
						{
							knockBackPos.x = this->theHero->GetPos_x() + ((Vector3(this->theHero->GetPos_x()) - Vector3(enemy->GetPos_x())).Normalized() * currentLevel->gameObjectsManager->tileSize).x;
						}
						if(this->theHero->GetPos_y() != enemy->GetPos_y())
						{
							knockBackPos.y = this->theHero->GetPos_y() + ((Vector3(0, this->theHero->GetPos_y()) - Vector3(0, enemy->GetPos_y())).Normalized() * currentLevel->gameObjectsManager->tileSize).y;
						}
						GameObject* go = currentLevel->gameObjectsManager->CheckColision(knockBackPos);
						if(!go)
							this->theHero->knockBackEnabled(knockBackPos);
						else
						{
							switch(go->type)
							{
							case GameObject::DOOR:
								{
									this->theHero->knockBackEnabled(knockBackPos);
									this->theHero->SetCurrentState(theHero->EXITING);
								}
								break;
							}
						}
					}
					enemy->SetHitHero(false);
					break;
				}
				CEnemy *enemyCollided = currentLevel->AI_Manager->CheckColisionBetweenEnemies(enemy, currentLevel->gameObjectsManager->tileSize);
				if(enemyCollided)
				{
					enemy->SetPos_x(enemy->GetPos_x() + enemy->GetPos_x() - enemyCollided->GetPos_x());
					enemy->SetPos_y(enemy->GetPos_y() + enemy->GetPos_y() - enemyCollided->GetPos_y());
				}
			}
		}
		else
		{
			// Falling animation
			if(theHero->GetTimeElasped() < 2.f)
			{
				theHero->SetTimeElasped(theHero->GetTimeElasped() + dt);
				theHero->SetAnimationCounter(theHero->GetAnimationCounter() + 20 * dt);
				if(theHero->GetAnimationCounter() > 5.0f)
					theHero->SetAnimationCounter(5.0f);
			}
			else
			{
				theHero->SetHealth(0);
				if(theHero->GetHealth() > 0)
				{
					// Reset informations
					theHero->Reset();
					this->theHero->SetCurrentState(this->theHero->PLAYING);
					currentLevel->AI_Manager->Reset();
				}
				else
				{
					// Gameover
					gameState = GAMEOVER;
				}
			}
		}
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

			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(1, 1, 1), 2.5, 13, 5);
		}
		break;
	default:
		{
			modelStack.PushMatrix();

			modelStack.Translate( currentLevel->m_cMap->GetNumOfTiles_Width() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos_x() * 2 - currentLevel->m_cMap->GetTileSize(),  currentLevel->m_cMap->GetNumOfTiles_Height() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos_y() * 2 - currentLevel->m_cMap->GetTileSize(), 0);
			modelStack.Scale(2,2,2);

			// Render the background image
			RenderBackground();

			// Render the Game Objects
			RenderGameObjects();
			// Render the zombie
			RenderEnemies();
			// Render the hero
			RenderHero();

			modelStack.PopMatrix();

			RenderGUI();
		}
		break;
	}
}

void SceneSP3::Exit()
{
	delete theHero;
	engine->stopAllSounds();
}

/********************************************************************************
Render the Hero. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderHero()
{
	switch (this->theHero->GetCurrentState())
	{
	case this->theHero->PLAYING:
		{
			if(theHero->GetIsAttacking())
			{
				if(theHero->GetAnimationDirection() == theHero->DOWN)
				{
					Render2DMesh(theHero->attackFrontMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
				}
				else if(theHero->GetAnimationDirection() == theHero->UP)
				{
					Render2DMesh(theHero->attackBackMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
				}
				else
				{
					// Hero move right
					if(theHero->GetAnimationInvert() == false)
					{
						Render2DMesh(theHero->attackSideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
					}
					// Hero move left
					else
					{
						Render2DMesh(theHero->attackSideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
					}
				}
			}
			else
			{
				if(theHero->GetAnimationDirection() == theHero->DOWN)
				{
					Render2DMesh(theHero->frontMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
				}
				else if(theHero->GetAnimationDirection() == theHero->UP)
				{
					Render2DMesh(theHero->backMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
				}
				else
				{
					// Hero move right
					if(theHero->GetAnimationInvert() == false)
					{
						Render2DMesh(theHero->sideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
					}
					// Hero move left
					else
					{
						Render2DMesh(theHero->sideMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
					}
				}
			}
		}
		break;
	case this->theHero->EXITING:
		{
			Render2DMesh(theHero->backMeshes[0], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), false);
		}
		break;
	case this->theHero->DYING:
		{
			Render2DMesh(theHero->deathMeshes[(int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), false);
		}
		break;
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
		if(go->type == GameObject::WALL)
		{
			Render2DMesh(meshList[GEO_TILEGROUND], false, 1.0f, go->pos.x, go->pos.y);
		}
		else if(go->type == GameObject::DOOR)
		{
			Render2DMesh(meshList[GEO_DOOR], false, 1.0f, go->pos.x, go->pos.y);
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

		if(enemy->GetAnimationDirection() == enemy->DOWN)
		{
			Render2DMesh(currentLevel->AI_Manager->frontMeshes[(int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos_x(), enemy->GetPos_y());
		}
		else if(enemy->GetAnimationDirection() == enemy->UP)
		{
			Render2DMesh(currentLevel->AI_Manager->backMeshes[(int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos_x(), enemy->GetPos_y());
		}
		else
		{
			// enemy move right
			if(enemy->GetAnimationInvert() == false)
			{
				Render2DMesh(currentLevel->AI_Manager->sideMeshes[(int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos_x(), enemy->GetPos_y());
			}
			// enemy move left
			else
			{

				Render2DMesh(currentLevel->AI_Manager->sideMeshes[(int)enemy->GetAnimationCounter()], false, 1.0f, enemy->GetPos_x(), enemy->GetPos_y(), true);
			}
		}
		if(enemy->GetJustAlerted())
		{
			Render2DMesh(currentLevel->AI_Manager->alertSign, false, 1.0f, enemy->GetPos_x(), enemy->GetPos_y() + currentLevel->gameObjectsManager->tileSize);
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
	
	//On screen text
	/*std::ostringstream ss;
	ss.precision(3);
	ss << "X" << theHero->GetHealth();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3, 3, 57);*/
}

/********************************************************************************
Do colision check and response when the hero move
********************************************************************************/
void SceneSP3::HeroColision(GameObject* goCollidedWith, bool updown, bool upORleft, double dt)
{
	if(goCollidedWith)
	{
		switch (goCollidedWith->type)
		{
		case GameObject::WALL:
			break;
		case GameObject::DOOR:
			{
				this->theHero->SetPos_x(goCollidedWith->pos.x);
				this->theHero->SetPos_y(goCollidedWith->pos.y);
				this->theHero->SetCurrentState( this->theHero->EXITING );
			}
			break;
		default :
			if(updown == true && upORleft == true)
				this->theHero->MoveUpDown( true, dt, currentLevel->m_cMap);
			else if(updown == true && upORleft == false)
				this->theHero->MoveUpDown( false, dt, currentLevel->m_cMap);
			else if(updown == false && upORleft == true)
				this->theHero->MoveLeftRight( true, dt, currentLevel->m_cMap);
			else
				this->theHero->MoveLeftRight( false, dt, currentLevel->m_cMap);
			break;
		}
	}
	else
	{
		if(updown == true && upORleft == true)
				this->theHero->MoveUpDown( true, dt, currentLevel->m_cMap);
			else if(updown == true && upORleft == false)
				this->theHero->MoveUpDown( false, dt, currentLevel->m_cMap);
			else if(updown == false && upORleft == true)
				this->theHero->MoveLeftRight( true, dt, currentLevel->m_cMap);
			else
				this->theHero->MoveLeftRight( false, dt, currentLevel->m_cMap);
	}
}