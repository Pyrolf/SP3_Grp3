//#include "SceneMain.h"
//#include "GL\glew.h"
//
//#include "shader.hpp"
//#include "MeshBuilder.h"
//#include "Application.h"
//#include "Utility.h"
//#include "LoadTGA.h"
//#include <sstream>
//#include "Strategy_Kill.h"
//#include "Strategy_Safe.h"
//
//SceneMain::SceneMain()
//	: tileOffset_x(0)
//	, tileOffset_y(0)
//	, rearWallOffset_x(0)
//	, rearWallOffset_y(0)
//	, rearWallTileOffset_x(0)
//	, rearWallTileOffset_y(0)
//	, rearWallFineOffset_x(0)
//	, rearWallFineOffset_y(0)
//	, gameState(MAINMENU)
//	, highscore(0)
//	, choice(NONE)
//	, currentLevel(NULL)
//{
//	for(int index = 0; index < 2; index++)
//	{
//		levelList[index] = NULL;
//	}
//}
//
//SceneMain::~SceneMain()
//{
//	for(int index = 0; index < 2; index++)
//	{
//		//delete theGoodiesList;
//		for(int i = 0; i < levelList[index]->theGoodiesList.size(); i++)
//		{
//			if(levelList[index]->theGoodiesList[i])
//			{
//				delete levelList[index]->theGoodiesList[i];
//				levelList[index]->theGoodiesList[i] = NULL;
//			}
//			delete levelList[index]->theGoodiesList[i];
//		}
//
//		for(int i = 0; i < levelList[index]->theEnemy.size(); i++)
//		{
//			if(levelList[index]->theEnemy[i])
//			{
//				delete levelList[index]->theEnemy[i];
//				levelList[index]->theEnemy[i] = NULL;
//			}
//		}
//
//		if (levelList[index]->m_cMap)
//		{
//			delete levelList[index]->m_cMap;
//			levelList[index]->m_cMap = NULL;
//		}
//		if (levelList[index]->m_cRearMap)
//		{
//			delete levelList[index]->m_cRearMap;
//			levelList[index]->m_cRearMap = NULL;
//		}
//	}
//}
//
//void SceneMain::Init()
//{
//	SceneBase::Init();
//	
//
//	for(int index = 0; index < 2; index++)
//	{
//		levelList[index] = new Level;
//	}
//
//	// Initialise and load the tile map
//	levelList[0]->m_cMap = new CMap();
//	levelList[0]->m_cMap->Init( 832, 1024, 26, 32, 832, 1024);
//	levelList[0]->m_cMap->LoadMap( "Image//MapDesignLv1.csv" );
//	levelList[0]->background = meshList[GEO_GROUND_BACKGROUND];
//	levelList[0]->sideView = false;
//
//	levelList[1]->m_cMap = new CMap();
//	levelList[1]->m_cMap->Init( 832, 1024, 26, 32, 2400, 2880);
//	levelList[1]->m_cMap->LoadMap( "Image//MapDesignLv2.csv" );
//	levelList[1]->background = meshList[GEO_ICECAVE_BACKGROUND];
//	levelList[1]->sideView = true;
//
//	meshList[GEO_NORMAL_ZOMBIE_ATTACK_RANGE] = MeshBuilder::GenerateRing("ATTACK_RANGE", Color(0, 1, 0), 36.f, 4 * levelList[0]->m_cMap->GetTileSize(), 4 * levelList[0]->m_cMap->GetTileSize() - 1.f);
//	meshList[GEO_NORMAL_ZOMBIE_REPEL_RANGE] = MeshBuilder::GenerateRing("REPEL_RANGE", Color(1, 0, 0), 36.f, 1 * levelList[0]->m_cMap->GetTileSize(), 1 * levelList[0]->m_cMap->GetTileSize() - 1.f);
//
//	// Initialise and load the REAR tile map
//	levelList[1]->m_cRearMap = new CMap();
//	levelList[1]->m_cRearMap->Init( 832, 1024, 26, 32, 2400, 2880);
//	levelList[1]->m_cRearMap->LoadMap( "Image//MapDesign_RearLv2.csv" );
//
//	// Initialise the hero's position
//	theHero = new CPlayerInfo();
//
//	for(int index = 0; index < 2; index++)
//	{
//	vector<Vector3> enemyInitialPos;
//	vector<Vector3> enemyFinalPos;
//	vector<Vector3> coinPos;
//	vector<Vector3> HealthPos;
//	int m = 0;
//	int j = 0;
//	for(int i = 0; i < levelList[index]->m_cMap->getNumOfTiles_MapHeight(); i ++)
//	{
//		for(int k = 0; k < levelList[index]->m_cMap->getNumOfTiles_MapWidth() + 1; k ++)
//		{
//			m = tileOffset_x + k;
//			j = i + tileOffset_y;
//			// If we have reached the right side of the Map, then do not display the extra column of tiles.
//			if((tileOffset_x+k) >= levelList[index]->m_cMap->getNumOfTiles_MapWidth())
//				break;
//			if (levelList[index]->m_cMap->theScreenMap[i][m] == 10)
//			{
//				enemyInitialPos.push_back(Vector3(k, 25 - i));
//			}
//			else if (levelList[index]->m_cMap->theScreenMap[i][m] == 11)
//			{
//				enemyFinalPos.push_back(Vector3(k, 25 - i));
//			}
//			else if (levelList[index]->m_cMap->theScreenMap[i][m] == 4)
//			{
//				coinPos.push_back(Vector3(k, 25 - i));
//			}
//			else if (levelList[index]->m_cMap->theScreenMap[i][m] == 5)
//			{
//				HealthPos.push_back(Vector3(k, 25 - i));
//			}
//			else if (levelList[index]->m_cMap->theScreenMap[i][m] == 20)
//			{
//				levelList[index]->HeroStartPos.x = k * levelList[index]->m_cMap->GetTileSize();
//				levelList[index]->HeroStartPos.y = (25 - i) * levelList[index]->m_cMap->GetTileSize();
//			}
//		}
//	}
//
//	// Enemys
//	if(enemyInitialPos.size() != 0)
//	{
//		for(int i = 0; i < enemyInitialPos.size(); i++)
//		{
//			// Set the strategy for the enemy
//			levelList[index]->theEnemy.push_back(new CEnemy);
//			levelList[index]->theEnemy[i]->ChangeStrategy(NULL, false);
//			levelList[index]->theEnemy[i]->SetPos_x(enemyInitialPos[i].x  * levelList[index]->m_cMap->GetTileSize(), true, enemyFinalPos[i].x  * levelList[index]->m_cMap->GetTileSize());
//			levelList[index]->theEnemy[i]->SetPos_y(enemyInitialPos[i].y  * levelList[index]->m_cMap->GetTileSize(), true, enemyFinalPos[i].y  * levelList[index]->m_cMap->GetTileSize());
//			levelList[index]->theEnemy[i]->ChangeStrategy(new CStrategy_Safe());
//			levelList[index]->theEnemy[i]->SetCurrentStrategy(levelList[index]->theEnemy[i]->SAFE);
//			levelList[index]->theEnemy[i]->SetDestination(levelList[index]->theEnemy[i]->GetInitialPos_x(), levelList[index]->theEnemy[i]->GetInitialPos_y());
//			levelList[index]->theEnemy[i]->SetAnimationCounter(0.f);
//			levelList[index]->theEnemy[i]->SetAnimationInvert(false);
//		}
//	}
//
//	// Coins
//	if(coinPos.size() != 0)
//	{
//		for(int i = 0; i < coinPos.size(); i++)
//		{
//			levelList[index]->theGoodiesList.push_back(new CGoodies);
//			levelList[index]->theGoodiesList[i] = theGoodiesFactory.Create(COIN);
//			levelList[index]->theGoodiesList[i]->SetPos(coinPos[i].x * levelList[index]->m_cMap->GetTileSize(), coinPos[i].y *levelList[index]-> m_cMap->GetTileSize());
//			levelList[index]->theGoodiesList[i]->SetMesh(MeshBuilder::Generate2DMesh("GEO_TILE_COIN", Color(1, 1, 1), 0.f, 0.f, 32.f, 32.f));
//			levelList[index]->theGoodiesList[i]->SetTextureID(LoadTGA("Image//tile4_coin.tga"));
//		}
//	}
//	// Healths
//	if(HealthPos.size() != 0)
//	{
//		for(int i = coinPos.size(); i < HealthPos.size() + coinPos.size(); i++)
//		{
//			levelList[index]->theGoodiesList.push_back(new CGoodies);
//			levelList[index]->theGoodiesList[i] = theGoodiesFactory.Create(HEALTH);
//			levelList[index]->theGoodiesList[i]->SetPos(HealthPos[i - coinPos.size()].x * levelList[index]->m_cMap->GetTileSize(), HealthPos[i - coinPos.size()].y * levelList[index]->m_cMap->GetTileSize());
//			levelList[index]->theGoodiesList[i]->SetMesh(MeshBuilder::Generate2DMesh("GEO_TILE_HEALTH", Color(1, 1, 1), 0.f, 0.f, 32.f, 32.f));
//			levelList[index]->theGoodiesList[i]->SetTextureID(LoadTGA("Image//tile5_health.tga"));
//		}
//	}
//	}
//}
//void SceneMain::UpdateInputs(double dt)
//{
//
//	// For gameplay
//	{
//		// Check Collision of th hero before moving up
//		if(Application::IsKeyPressed('P'))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING)
//			{
//				gameState = PAUSE;
//			}
//		}
//		// Check Collision of th hero before moving up
//		if(Application::IsKeyPressed('W'))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && !this->theHero->GetSideView())
//			{
//				switch (this->theHero->CheckCollision(this->theHero->GetPos_x(), this->theHero->GetPos_y() + this->theHero->GetMovementSpeed() * dt, true, false, false, false, currentLevel->m_cMap))
//				{
//				case 0:
//					{
//						this->theHero->MoveUpDown( true, dt, currentLevel->m_cMap);
//					}
//					break;
//				}
//			}
//		}
//		// Check Collision of th hero before moving down
//		if(Application::IsKeyPressed('S'))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && !this->theHero->GetSideView())
//			{
//				switch (this->theHero->CheckCollision(this->theHero->GetPos_x(), this->theHero->GetPos_y() - this->theHero->GetMovementSpeed() * dt, false, true, false, false, currentLevel->m_cMap))
//				{
//				case 0:
//					this->theHero->MoveUpDown( false, dt, currentLevel->m_cMap);
//					break;
//				}
//			}
//		}
//		// Check Collision of the hero before jumping up
//		if(Application::IsKeyPressed(' '))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && this->theHero->GetSideView())
//			{
//				if(this->theHero->CheckCollision(this->theHero->GetPos_x(), this->theHero->GetPos_y() + 500 * dt, true, false, false, false,currentLevel->m_cMap) == 0
//					&& this->theHero->isOnGround())
//				{
//					this->theHero->SetToJumpUpwards(currentLevel->m_cMap);
//				}
//			}
//		}
//
//		// Check Collision of th hero before moving left
//		if(Application::IsKeyPressed('A'))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING)
//			{
//				switch (this->theHero->CheckCollision(this->theHero->GetPos_x() - this->theHero->GetMovementSpeed() * dt, this->theHero->GetPos_y(), false, false, true, false, currentLevel->m_cMap))
//				{
//				case 0:
//					this->theHero->MoveLeftRight( true, dt, currentLevel->m_cMap);
//					break;
//				}
//			}
//		}
//		// Check Collision of th hero before moving right
//		if(Application::IsKeyPressed('D'))
//		{
//			if(this->theHero->GetCurrentState() == this->theHero->PLAYING)
//			{
//				switch (this->theHero->CheckCollision(this->theHero->GetPos_x() + this->theHero->GetMovementSpeed() * dt, this->theHero->GetPos_y(), false, false, false, true, currentLevel->m_cMap))
//				{
//				case 0:
//					this->theHero->MoveLeftRight( false, dt, currentLevel->m_cMap );
//					break;
//				case 3:
//					{
//						int checkPosition_X = 1 + (int) ((this->theHero->GetMapOffset_x() + this->theHero->GetPos_x() + this->theHero->GetMovementSpeed() * dt) / currentLevel->m_cMap->GetTileSize());
//						this->theHero->SetPos_x(checkPosition_X * currentLevel->m_cMap->GetTileSize() - theHero->GetMapOffset_x());
//						this->theHero->SetCurrentState( this->theHero->EXITING );
//					}
//					break;
//				}
//			}
//		}
//	}
//	// Others
//	{
//		// Choose play
//		if(Application::IsKeyPressed(VK_UP))
//		{
//			if(gameState == PAUSE || gameState == MAINMENU)
//			{
//				if(choice != PLAY)
//				{
//					choice = PLAY;
//				}
//			}
//			
//		}
//		// Choose exit
//		else if(Application::IsKeyPressed(VK_DOWN))
//		{
//			if(gameState == PAUSE)
//			{
//				if(choice != QUIT)
//				{
//					choice = QUIT;
//				}
//			}
//			else if(gameState == MAINMENU)
//			{
//				if(choice != EXIT)
//				{
//					choice = EXIT;
//				}
//			}
//
//		}
//		// Confirm choice
//		else if(Application::IsKeyPressed(VK_RETURN))
//		{
//			if(gameState == PAUSE)
//			{
//				if(choice == PLAY)
//				{
//					gameState = PLAYING;
//				}
//				else if(choice == QUIT)
//				{
//					gameState = MAINMENU;
//					this->theHero->Reset();
//					this->theHero->SetNoOfCoins(0);
//					this->theHero->SetNoOfLives(3);
//					this->theHero->SetCurrentState(this->theHero->PLAYING);
//					for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//					{
//						CEnemy *enemy = (CEnemy *)*it;
//						enemy->SetPos_x(enemy->GetInitialPos_x());
//						enemy->SetPos_y(enemy->GetInitialPos_y());
//						if(enemy->GetHitHero())
//						{
//							enemy->SetHitHero(false);
//						}
//					}
//				}
//				choice = NONE;
//			}
//			else if(gameState == MAINMENU)
//			{
//				if(choice == PLAY)
//				{
//					choice = NONE;
//					gameState = PLAYING;
//					currentLevel = levelList[0];
//					theHero->SetPos_x(currentLevel->HeroStartPos.x, true);
//					theHero->SetPos_y(currentLevel->HeroStartPos.y, true);
//					theHero->SetSideView(currentLevel->sideView);
//				}
//			}
//			else if(gameState == GAMEOVER)
//			{
//				gameState = MAINMENU;
//				this->theHero->Reset();
//				this->theHero->SetNoOfCoins(0);
//				this->theHero->SetNoOfLives(3);
//				this->theHero->SetCurrentState(this->theHero->PLAYING);
//				for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//				{
//					CEnemy *enemy = (CEnemy *)*it;
//					enemy->SetPos_x(enemy->GetInitialPos_x());
//					enemy->SetPos_y(enemy->GetInitialPos_y());
//					if(enemy->GetHitHero())
//					{
//						enemy->SetHitHero(false);
//					}
//				}
//			}
//		}
//	}
//}
//
//void SceneMain::Update(double dt)
//{
//	UpdateInputs(dt);
//	
//	if(gameState == PLAYING)
//	{
//		if(this->theHero->GetCurrentState() != this->theHero->DYING)
//		{
//			switch (this->theHero->GetCurrentState())
//			{
//			case this->theHero->EXITING:
//				{
//					if(this->theHero->GetTimeElasped() >= 1.f)
//					{
//						for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//						{
//							CEnemy *enemy = (CEnemy *)*it;
//							enemy->SetPos_x(enemy->GetInitialPos_x());
//							enemy->SetPos_y(enemy->GetInitialPos_y());
//						}
//						for(int index = 0; index < 2; index++)
//						{
//							if(currentLevel == levelList[index])
//							{
//								if(index + 1 < 2)
//								{
//									currentLevel = levelList[index + 1];
//									theHero->SetPos_x(currentLevel->HeroStartPos.x, true);
//									theHero->SetPos_y(currentLevel->HeroStartPos.y, true);
//									theHero->SetSideView(currentLevel->sideView);
//									this->theHero->SetCurrentState(this->theHero->PLAYING);
//									this->theHero->SetTimeElasped( 0.f );
//									break;
//								}
//								else
//								{
//									gameState = GAMEOVER;
//									theHero->SetNoOfCoins(theHero->GetNoOfCoins() + theHero->GetNoOfLives() * 100);
//									break;
//								}
//							}
//						}
//					}
//					else
//						this->theHero->SetTimeElasped( this->theHero->GetTimeElasped() + dt );
//				}
//				break;
//			}
//
//			theHero->HeroUpdate(currentLevel->m_cMap, dt);
//
//			//Enemies
//			for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//			{
//				CEnemy *enemy = (CEnemy *)*it;
//				// if the hero enters the kill zone, then enemygoes into kill strategy mode
//				float Dist_x = (Vector3(enemy->GetPos_x(), 0, 0) - Vector3(theHero->GetPos_x() + theHero->GetMapOffset_x(), 0, 0)).Length();
//				float Dist_y = (Vector3(0, enemy->GetPos_y(), 0) - Vector3(0, theHero->GetPos_y() - theHero->GetMapOffset_y(), 0)).Length();
//				float radius = 4 * currentLevel->m_cMap->GetTileSize();
//				if( Dist_x <= radius - currentLevel->m_cMap->GetTileSize() * 0.5 && Dist_y < currentLevel->m_cMap->GetTileSize() * 0.5)
//				{
//					enemy->ChangeStrategy(new  CStrategy_Kill());
//					enemy->SetCurrentStrategy(enemy->KILL);
//				}
//				else
//				{
//					if(enemy->GetCurrentStrategy() == enemy->KILL)
//					{
//						enemy->ChangeStrategy(new CStrategy_Safe());
//						enemy->SetCurrentStrategy(enemy->SAFE);
//						enemy->SetDestination(enemy->GetInitialPos_x(), enemy->GetInitialPos_y());
//					}
//				}
//
//				//Update the enemies
//				Vector2 EnemyPrevPos;
//				EnemyPrevPos.x = enemy->GetPos_x();
//				EnemyPrevPos.y = enemy->GetPos_y();
//				switch (enemy->GetCurrentStrategy())
//				{
//				case enemy->KILL:
//					{
//						enemy->SetDestination(theHero->GetMapOffset_x() + theHero->GetPos_x(), theHero->GetPos_y() - theHero->GetMapOffset_y());
//						enemy->Update( currentLevel->m_cMap, dt );
//						if(this->theHero->CheckCollision(enemy->GetPos_x() - theHero->GetMapOffset_x(), enemy->GetPos_y(), false, false, true, true,currentLevel->m_cMap, false) == 1)
//						{
//							enemy->SetPos_x(EnemyPrevPos.x);
//							enemy->SetPos_y(EnemyPrevPos.y);
//						}
//						else
//						{
//							if(enemy->GetDestination_x() < EnemyPrevPos.x )
//							{
//								enemy->SetAnimationInvert(true);
//								enemy->SetAnimationCounter(enemy->GetAnimationCounter() - 0.5f);
//								if(enemy->GetAnimationCounter() < 1.0f)
//									enemy->SetAnimationCounter(4.0f);
//							}
//							else if(enemy->GetDestination_x() > EnemyPrevPos.x )
//							{
//								enemy->SetAnimationInvert(false);
//								enemy->SetAnimationCounter(enemy->GetAnimationCounter() + 0.5f);
//								if(enemy->GetAnimationCounter() > 4.0f)
//									enemy->SetAnimationCounter(1.0f);
//							}
//						}
//					}
//					break;
//				case enemy->SAFE:
//					{
//						enemy->Update( currentLevel->m_cMap, dt );
//						if(enemy->GetDestination_x() < EnemyPrevPos.x )
//						{
//							enemy->SetAnimationInvert(true);
//							enemy->SetAnimationCounter(enemy->GetAnimationCounter() - 0.5f);
//							if(enemy->GetAnimationCounter() < 1.0f)
//								enemy->SetAnimationCounter(4.0f);
//
//							if(enemy->GetDestination_x() >= enemy->GetPos_x())
//							{
//								if(enemy->GetDestination_x() == enemy->GetInitialPos_x())
//								{
//									enemy->SetPos_x(enemy->GetInitialPos_x());
//									enemy->SetDestination(enemy->GetFinalPos_x(), enemy->GetFinalPos_y());
//								}
//								else
//								{
//									enemy->SetPos_x(enemy->GetFinalPos_x());
//									enemy->SetDestination(enemy->GetInitialPos_x(), enemy->GetInitialPos_y());
//								}
//							}
//						}
//						else if(enemy->GetDestination_x() > EnemyPrevPos.x )
//						{
//							enemy->SetAnimationInvert(false);
//							enemy->SetAnimationCounter(enemy->GetAnimationCounter() + 0.5f);
//							if(enemy->GetAnimationCounter() > 4.0f)
//								enemy->SetAnimationCounter(1.0f);
//
//
//							if(enemy->GetDestination_x() <= enemy->GetPos_x())
//							{
//								if(enemy->GetDestination_x() == enemy->GetInitialPos_x())
//								{
//									enemy->SetPos_x(enemy->GetInitialPos_x());
//									enemy->SetDestination(enemy->GetFinalPos_x(), enemy->GetFinalPos_y());
//								}
//								else
//								{
//									enemy->SetPos_x(enemy->GetFinalPos_x());
//									enemy->SetDestination(enemy->GetInitialPos_x(), enemy->GetInitialPos_y());
//								}
//							}
//						}
//					}
//					break;
//				}
//				if(enemy->GetHitHero())
//				{
//					this->theHero->SetCurrentState(this->theHero->DYING);
//					break;
//				}
//			}
//
//			// Goodies
//			for(vector<CGoodies *>::iterator it = currentLevel->theGoodiesList.begin(); it != currentLevel->theGoodiesList.end(); ++it)
//			{
//				CGoodies *goodies = (CGoodies *)*it;
//				if(!goodies->interacted)
//				{
//					float Dist = (Vector3(goodies->GetPos_x(), goodies->GetPos_y(), 0) - Vector3(theHero->GetPos_x() + theHero->GetMapOffset_x(), theHero->GetPos_y() - theHero->GetMapOffset_y(), 0)).Length();
//					if( Dist <= currentLevel->m_cMap->GetTileSize())
//					{
//						if(goodies->GetMesh()->name == "GEO_TILE_COIN")
//						{
//							theHero->SetNoOfCoins(theHero->GetNoOfCoins() + 1);
//							goodies->interacted = true;
//							break;
//						}
//						else
//						{
//							theHero->SetNoOfLives(theHero->GetNoOfLives() + 1);
//							goodies->interacted = true;
//							break;
//						}
//					}
//				}
//			}
//
//			//Recalulate the tile offsets
//			tileOffset_x = (int) (theHero->GetMapOffset_x() / currentLevel->m_cMap->GetTileSize());
//			if(tileOffset_x + currentLevel->m_cMap->GetNumOfTiles_Width() > currentLevel->m_cMap->getNumOfTiles_MapWidth())
//				tileOffset_x = currentLevel->m_cMap->getNumOfTiles_MapWidth() - currentLevel->m_cMap->GetNumOfTiles_Width();
//
//			tileOffset_y = (int) (theHero->GetMapOffset_y() / currentLevel->m_cMap->GetTileSize());
//			if(tileOffset_y + currentLevel->m_cMap->GetNumOfTiles_Height() > currentLevel->m_cMap->getNumOfTiles_MapHeight())
//				tileOffset_y = currentLevel->m_cMap->getNumOfTiles_MapHeight() + currentLevel->m_cMap->GetNumOfTiles_Height();
//
//		}
//		else
//		{
//			// Falling animation till out of screen
//			if(theHero->GetPos_y() > 0.f - currentLevel->m_cMap->GetTileSize())
//				theHero->SetPos_y(theHero->GetPos_y() - 400 * dt);
//			else
//			{
//				theHero->SetNoOfLives(theHero->GetNoOfLives() - 1);
//				if(theHero->GetNoOfLives() > 0)
//				{
//					// Reset informations
//					theHero->Reset();
//					this->theHero->SetCurrentState(this->theHero->PLAYING);
//					for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//					{
//						CEnemy *enemy = (CEnemy *)*it;
//						enemy->SetPos_x(enemy->GetInitialPos_x());
//						enemy->SetPos_y(enemy->GetInitialPos_y());
//						if(enemy->GetHitHero())
//						{
//							enemy->SetHitHero(false);
//							break;
//						}
//					}
//				}
//				else
//				{
//					// Gameover
//					gameState = GAMEOVER;
//				}
//			}
//		}
//		// Highscore
//		if(highscore < theHero->GetNoOfCoins())
//		{
//			highscore = theHero->GetNoOfCoins();
//		}
//	}
//}
//
//void SceneMain::RenderBackground()
//{
//	// Render the crosshair
//	Render2DMesh(currentLevel->background, false, 1.0f);
//}
//
//void SceneMain::Render()
//{
//	SceneBase::Render();
//
//	glDisable(GL_DEPTH_TEST);
//	switch(gameState)
//	{
//	case MAINMENU:
//		{
//			Render2DMesh(meshList[GEO_MAINMENU], false);
//			
//			//On screen text
//			RenderTextOnScreen(meshList[GEO_TEXT], "START GAME", Color(1, 1, 1), 5, 25, 15);
//			RenderTextOnScreen(meshList[GEO_TEXT], "EXIT", Color(1, 1, 1), 5, 25, 10);
//			if(choice == PLAY)
//			{
//				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 15);
//			}
//			else if(choice == EXIT)
//			{
//				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 10);
//			}
//		}
//		break;
//	case PAUSE:
//		{
//			Render2DMesh(meshList[GEO_PAUSE], false);
//			
//			//On screen text
//			RenderTextOnScreen(meshList[GEO_TEXT], "1.CONTINUE", Color(1, 1, 1), 5, 25, 15);
//			RenderTextOnScreen(meshList[GEO_TEXT], "2.QUIT", Color(1, 1, 1), 5, 25, 10);
//			if(choice == PLAY)
//			{
//				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 15);
//			}
//			else if(choice == QUIT)
//			{
//				RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(1, 1, 1), 5, 15, 10);
//			}
//		}
//		break;
//	case GAMEOVER:
//		{
//			Render2DMesh(meshList[GEO_GAMEOVER], false);
//
//			//On screen text
//			std::ostringstream ss;
//			ss.str(std::string());
//			ss.precision(4);
//			ss << theHero->GetNoOfCoins();
//			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.8, 0.8, 0.8), 8, 28, 25);
//
//			ss.str(std::string());
//			ss.precision(4);
//			ss << highscore;
//			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.8, 0.8, 0.8), 4, 34, 12);
//
//			RenderTextOnScreen(meshList[GEO_TEXT], "Press enter to return", Color(1, 1, 1), 2.5, 13, 5);
//		}
//		break;
//	default:
//		{
//			// Render the background image
//			RenderBackground();
//
//			modelStack.PushMatrix();
//			modelStack.Translate(0, currentLevel->m_cMap->GetTileSize(), 0);
//			// Render the rear tile map
//			RenderRearTileMap();
//			// Render the tile map
//			RenderTileMap();
//			modelStack.PopMatrix();
//
//			// Render the goodies
//			RenderGoodies();
//
//			Render2DMesh(meshList[GEO_LIVE], false, 1.0f, 0, 800 - 32);
//			//On screen text
//			std::ostringstream ss;
//			ss.precision(3);
//			ss << "X" << theHero->GetNoOfLives();
//			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3, 3, 57);
//
//			ss.str(std::string());
//			ss.precision(4);
//			ss << theHero->GetNoOfCoins();
//			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0.8, 0.8, 0.8), 3, 71, 57);
//
//			ss.str(std::string());
//			ss.precision(4);
//			ss << highscore;
//			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 0), 2.5, 71, 54);
//		}
//		break;
//	}
//}
//
//void SceneMain::Exit()
//{
//	delete theHero;
//}
//
///********************************************************************************
//Render the tile map. This is a private function for use in this class only
//********************************************************************************/
//void SceneMain::RenderTileMap()
//{
//	int m = 0;
//	int j = 0;
//	for(int i = 0; i < currentLevel->m_cMap->GetNumOfTiles_Height(); i ++)
//	{
//		for(int k = 0; k < currentLevel->m_cMap->GetNumOfTiles_Width() + 1; k ++)
//		{
//			m = tileOffset_x + k;
//			j = i + tileOffset_y;
//			// If we have reached the right side of the Map, then do not display the extra column of tiles.
//			if((tileOffset_x+k) >= currentLevel->m_cMap->getNumOfTiles_MapWidth())
//				break;
//			if (currentLevel->m_cMap->theScreenMap[j][m] == 1)
//				Render2DMesh(meshList[GEO_TILEGROUND], false, 1.0f, k*currentLevel->m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 768 -(i-1)*currentLevel->m_cMap->GetTileSize() + theHero->GetMapFineOffset_y());
//			else if (currentLevel->m_cMap->theScreenMap[j][m] == 2)
//				Render2DMesh(meshList[GEO_MAGMA], false, 1.0f, k*currentLevel->m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 768 -(i-1)*currentLevel->m_cMap->GetTileSize() + theHero->GetMapFineOffset_y());
//			else if (currentLevel->m_cMap->theScreenMap[j][m] == 3)
//				Render2DMesh(meshList[GEO_DOOR], false, 1.0f, k*currentLevel->m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 768 -(i-1)*currentLevel->m_cMap->GetTileSize() + theHero->GetMapFineOffset_y());
//			/*else if (currentLevel->m_cMap->theScreenMap[j][m] == 10)
//				Render2DMesh(meshList[GEO_TILE_KILLZONE], false, 1.0f, k*currentLevel->m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 768 -(i-1)*currentLevel->m_cMap->GetTileSize() + theHero->GetMapFineOffset_y());
//			else if (currentLevel->m_cMap->theScreenMap[j][m] == 11)
//				Render2DMesh(meshList[GEO_TILE_SAFEZONE], false, 1.0f, k*currentLevel->m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 768 -(i-1)*currentLevel->m_cMap->GetTileSize() + theHero->GetMapFineOffset_y());
//		*/}
//	}
//
//	switch (this->theHero->GetCurrentState())
//	{
//	case this->theHero->PLAYING:
//		{
//			if(theHero->GetAnimationDirection() == theHero->DOWN)
//			{
//				Render2DMesh(meshList[GEO_TILEHERO_FRAME0_FRONT + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
//			}
//			else if(theHero->GetAnimationDirection() == theHero->UP)
//			{
//				Render2DMesh(meshList[GEO_TILEHERO_FRAME0_BACK + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
//			}
//			else
//			{
//				// Hero move right
//				if(theHero->GetAnimationInvert() == false)
//				{
//					Render2DMesh(meshList[GEO_TILEHERO_FRAME0 + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
//				}
//				// Hero move left
//				else
//				{
//					
//					Render2DMesh(meshList[GEO_TILEHERO_FRAME0 + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
//				}
//			}
//		}
//		break;
//	case this->theHero->EXITING:
//		{
//			Render2DMesh(meshList[GEO_TILEHERO_FRAME0_BACK], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
//		}
//		break;
//	case this->theHero->DYING:
//		{
//			Render2DMesh(meshList[GEO_TILEHERO_FRAME0_FRONT], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
//		}
//		break;
//	}
//
//	// Render the enemies
//	for(vector<CEnemy *>::iterator it = currentLevel->theEnemy.begin(); it != currentLevel->theEnemy.end(); ++it)
//	{
//		CEnemy *enemy = (CEnemy *)*it;
//		int enemy_x = enemy->GetPos_x() - theHero->GetMapOffset_x();
//		int enemy_y = enemy->GetPos_y() + theHero->GetMapOffset_y();
//		if( ((enemy_x >= 0) && (enemy_x < 1024)) &&
//			((enemy_y >= 0) && (enemy_y < 800)) )
//		{
//
//			if(enemy->GetAnimationInvert() == false)
//			{
//				// Enemy move right
//				if((int)enemy->GetAnimationCounter() == 0)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 1)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME1], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 2)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME2], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 3)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME3], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 4)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME4], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 5)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME5], false, 1.0f, enemy_x, enemy_y);
//				else if((int)enemy->GetAnimationCounter() == 6)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME6], false, 1.0f, enemy_x, enemy_y);
//				else
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y);
//
//			}
//			else
//			{
//				// Enemy move left
//				if((int)enemy->GetAnimationCounter() == 0)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 1)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME1], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 2)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME2], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 3)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME3], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 4)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME4], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 5)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME5], false, 1.0f, enemy_x, enemy_y, true);
//				else if((int)enemy->GetAnimationCounter() == 6)
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME6], false, 1.0f, enemy_x, enemy_y, true);
//				else
//					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y, true);
//			}
//			//Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_ATTACK_RANGE], false, 1.0f, enemy_x - currentLevel->m_cMap->GetTileSize() * 0.5, enemy_y + currentLevel->m_cMap->GetTileSize() * 0.5, true);
//			//Render2DMesh(meshList[GEO_NORMAL_ZOMBIE_REPEL_RANGE], false, 1.0f, enemy_x - currentLevel->m_cMap->GetTileSize() * 0.5, enemy_y + currentLevel->m_cMap->GetTileSize() * 0.5, true);
//		}
//	}
//}
//
///********************************************************************************
//Render the rear tile map. This is a private function for use in this class only
//********************************************************************************/
//void SceneMain::RenderRearTileMap()
//{
//	if(currentLevel->m_cRearMap != NULL)
//	{
//		rearWallOffset_x = (int)(theHero->GetMapOffset_x() / 2);
//		rearWallTileOffset_x = (int)(rearWallOffset_x / currentLevel->m_cRearMap->GetTileSize());
//		if(rearWallTileOffset_x + currentLevel->m_cRearMap->GetNumOfTiles_Width() > currentLevel->m_cRearMap->getNumOfTiles_MapWidth())
//			rearWallTileOffset_x = currentLevel->m_cRearMap->getNumOfTiles_MapWidth() - currentLevel->m_cRearMap->GetNumOfTiles_Width();
//		rearWallFineOffset_x = rearWallOffset_x % currentLevel->m_cRearMap->GetTileSize();
//
//		rearWallOffset_y = (int)(theHero->GetMapOffset_y() / 2);
//		rearWallTileOffset_y = (int)(rearWallOffset_y / currentLevel->m_cRearMap->GetTileSize());
//		if(rearWallTileOffset_y + currentLevel->m_cRearMap->GetNumOfTiles_Height() > currentLevel->m_cRearMap->getNumOfTiles_MapHeight())
//			rearWallTileOffset_y = currentLevel->m_cRearMap->getNumOfTiles_MapHeight() + currentLevel->m_cRearMap->GetNumOfTiles_Height();
//		rearWallFineOffset_y = rearWallOffset_y % currentLevel->m_cRearMap->GetTileSize();
//
//		int m = 0;
//		int j = 0;
//		for(int i = 0; i < currentLevel->m_cRearMap->GetNumOfTiles_Height(); i ++)
//		{
//			for(int k = 0; k < currentLevel->m_cRearMap->GetNumOfTiles_Width() + 1; k ++)
//			{
//				m = rearWallTileOffset_x + k;
//				j = i + rearWallTileOffset_y;
//				// If we have reached the right side of the Map, then do not display the extra column of tiles.
//				if((rearWallTileOffset_x + k) >= currentLevel->m_cRearMap->getNumOfTiles_MapWidth())
//					break;
//				if (currentLevel->m_cRearMap->theScreenMap[j][m] == 1)
//				{
//					Render2DMesh(meshList[GEO_LADDER], false, 1.0f, k*currentLevel->m_cRearMap->GetTileSize() - rearWallFineOffset_x, 768 -(i-1)*currentLevel->m_cRearMap->GetTileSize() + rearWallFineOffset_y);
//				}
//			}
//		}
//	}
//}
//
///********************************************************************************
//Render the goodies. This is a private function for use in this class only
//********************************************************************************/
//void SceneMain::RenderGoodies(void)
//{
//	// Render the goodies
//	for(vector<CGoodies *>::iterator it = currentLevel->theGoodiesList.begin(); it != currentLevel->theGoodiesList.end(); ++it)
//	{
//		CGoodies *goodies = (CGoodies *)*it;
//		if(!goodies->interacted)
//		{
//			int pos_x = goodies->GetPos_x() - theHero->GetMapOffset_x();
//			int pos_y = goodies->GetPos_y() + theHero->GetMapOffset_y();
//			Render2DMesh(goodies->GetMesh(), false, 1.0f, pos_x, pos_y);
//		}
//	}
//}