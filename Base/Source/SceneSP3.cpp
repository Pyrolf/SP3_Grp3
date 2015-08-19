#include "SceneSP3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

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

	// Initialise the hero's position
	theHero = new CPlayerInfo();

	// Initialise and load the tile map
	levelList.push_back(new Level);
	levelList[0]->m_cMap = new CMap();
	levelList[0]->m_cMap->Init( 832, 1024, 26, 32, 832, 1024);
	levelList[0]->m_cMap->LoadMap( "Image//MapDesignLv1.csv" );
	levelList[0]->background = meshList[GEO_GROUND_BACKGROUND];
	levelList[0]->sideView = false;

	levelList[0]->gameObjectsManager = new GameObjectFactory;
	levelList[0]->gameObjectsManager->generateGO(levelList[0]->m_cMap);

	levelList[0]->AI_Manager = new CAIManager;
	levelList[0]->AI_Manager->generateEnemies(levelList[0]->m_cMap);

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
void SceneSP3::UpdateInputs(double dt)
{
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
		// Check Collision of th hero before moving up
		if(Application::IsKeyPressed('W'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && gameState == PLAYING)
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y() + this->theHero->GetMovementSpeed() * dt));

				HeroColision(goCollidedWith, true, true, dt);
			}
		}
		// Check Collision of th hero before moving down
		if(Application::IsKeyPressed('S'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && gameState == PLAYING)
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x(), this->theHero->GetPos_y() - this->theHero->GetMovementSpeed() * dt));

				HeroColision(goCollidedWith, true, false, dt);
			}
		}

		// Check Collision of th hero before moving left
		if(Application::IsKeyPressed('A'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && gameState == PLAYING)
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x() - this->theHero->GetMovementSpeed() * dt, this->theHero->GetPos_y()));

				HeroColision(goCollidedWith, false, true, dt);
			}
		}
		// Check Collision of th hero before moving right
		if(Application::IsKeyPressed('D'))
		{
			if(this->theHero->GetCurrentState() == this->theHero->PLAYING && gameState == PLAYING)
			{
				GameObject* goCollidedWith = currentLevel->gameObjectsManager->CheckColision(Vector3(this->theHero->GetPos_x() + this->theHero->GetMovementSpeed() * dt, this->theHero->GetPos_y()));

				HeroColision(goCollidedWith, false, false, dt);
			}
		}
	}
	// Others
	{
		// Choose play
		if(Application::IsKeyPressed(VK_UP))
		{
			if(gameState == PAUSE || gameState == MAINMENU)
			{
				if(choice != PLAY)
				{
					choice = PLAY;
				}
			}

		}
		// Choose exit
		else if(Application::IsKeyPressed(VK_DOWN))
		{
			if(gameState == PAUSE)
			{
				if(choice != QUIT)
				{
					choice = QUIT;
				}
			}
			else if(gameState == MAINMENU)
			{
				if(choice != EXIT)
				{
					choice = EXIT;
				}
			}

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

			theHero->HeroUpdate(currentLevel->m_cMap, dt);

			//Enemies
			for(vector<CEnemy *>::iterator it = currentLevel->AI_Manager->enemiesList.begin(); it != currentLevel->AI_Manager->enemiesList.end(); ++it)
			{
				CEnemy *enemy = (CEnemy *)*it;
				enemy->Update(currentLevel->gameObjectsManager, dt, Vector3(theHero->GetPos_x(), theHero->GetPos_y()));
				if(enemy->GetHitHero())
				{
					this->theHero->SetCurrentState(this->theHero->DYING);
					enemy->SetHitHero(false);
					break;
				}
				CEnemy *enemyCollided = currentLevel->AI_Manager->CheckColisionBetweenEnemies(enemy, currentLevel->gameObjectsManager->tileSize);
				if(enemyCollided)
				{
					enemy->SetPos_x(enemy->GetPos_x() - enemyCollided->GetPos_x());
					enemy->SetPos_y(enemy->GetPos_y() - enemyCollided->GetPos_y());
					enemyCollided->SetPos_x(enemyCollided->GetPos_x() - enemy->GetPos_x());
					enemyCollided->SetPos_y(enemyCollided->GetPos_y() - enemy->GetPos_y());
				}
			}
		}
		else
		{
			// Falling animation till out of screen
			if(theHero->GetPos_y() > 0.f - currentLevel->m_cMap->GetTileSize())
				theHero->SetPos_y(theHero->GetPos_y() - 400 * dt);
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
	Render2DMesh(currentLevel->background, false, 1.0f);
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

			modelStack.Translate( currentLevel->m_cMap->GetNumOfTiles_Width() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos_x(),  currentLevel->m_cMap->GetNumOfTiles_Height() * currentLevel->m_cMap->GetTileSize() * 0.5 - theHero->GetPos_y(), 0);

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
			if(theHero->GetAnimationDirection() == theHero->DOWN)
			{
				Render2DMesh(meshList[GEO_TILEHERO_FRAME0_FRONT + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
			}
			else if(theHero->GetAnimationDirection() == theHero->UP)
			{
				Render2DMesh(meshList[GEO_TILEHERO_FRAME0_BACK + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
			}
			else
			{
				// Hero move right
				if(theHero->GetAnimationInvert() == false)
				{
					Render2DMesh(meshList[GEO_TILEHERO_FRAME0 + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y());
				}
				// Hero move left
				else
				{

					Render2DMesh(meshList[GEO_TILEHERO_FRAME0 + (int)theHero->GetAnimationCounter()], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
				}
			}
		}
		break;
	case this->theHero->EXITING:
		{
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0_BACK], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
		}
		break;
	case this->theHero->DYING:
		{
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0_FRONT], false, 1.0f, theHero->GetPos_x(), theHero->GetPos_y(), true);
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
		int enemy_x = enemy->GetPos_x();
		int enemy_y = enemy->GetPos_y();
		if( ((enemy_x >= 0) && (enemy_x < 1024)) &&
			((enemy_y >= 0) && (enemy_y < 800)) )
		{

			if(enemy->GetAnimationInvert() == false)
			{
				// Enemy move right
				if((int)enemy->GetAnimationCounter() == 0)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y);
				else if((int)enemy->GetAnimationCounter() == 1)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME1], false, 1.0f, enemy_x, enemy_y);
				else if((int)enemy->GetAnimationCounter() == 2)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME2], false, 1.0f, enemy_x, enemy_y);
				else if((int)enemy->GetAnimationCounter() == 3)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME3], false, 1.0f, enemy_x, enemy_y);
				else
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y);

			}
			else
			{
				// Enemy move left
				if((int)enemy->GetAnimationCounter() == 0)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y, true);
				else if((int)enemy->GetAnimationCounter() == 1)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME1], false, 1.0f, enemy_x, enemy_y, true);
				else if((int)enemy->GetAnimationCounter() == 2)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME2], false, 1.0f, enemy_x, enemy_y, true);
				else if((int)enemy->GetAnimationCounter() == 3)
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME3], false, 1.0f, enemy_x, enemy_y, true);
				else
					Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1.0f, enemy_x, enemy_y, true);
			}
		}
	}
}

/********************************************************************************
Render the Enemies. This is a private function for use in this class only
********************************************************************************/
void SceneSP3::RenderGUI()
{
	RenderMeshIn2D(meshList[GEO_LIVE], false, 1.0f, -80, 75);
	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "X" << theHero->GetHealth();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3, 3, 57);
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