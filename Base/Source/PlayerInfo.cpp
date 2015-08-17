#include "PlayerInfo.h"
#include <iostream>

static float GRAVITY = 3000.f;

CPlayerInfo::CPlayerInfo(void)
	: hero_inMidAir_Up(false)
	, hero_inMidAir_Down(false)
	, jumpspeed(0)
	, heroAnimationDirection(DOWN)
	, heroAnimationCounter(0.0f)
	, heroAnimationInvert(false)
	, mapOffset_x(0)
	, mapOffset_y(0)
	, mapFineOffset_x(0)
	, mapFineOffset_y(0)
	, movementSpeed(400.0f)
	, mapOffset_yBeforeJump(0)
	, currentState(PLAYING)
	, timeElasped(0.f)
	, noOfCoins(0)
	, noOfLives(3)
	, sideView(false)
{
}


CPlayerInfo::~CPlayerInfo(void)
{
}

// Initialise this class instance
void CPlayerInfo::Init(void)
{
	theHeroPosition.Set(0, 0);
	theHeroInitialPosition.Set(0, 0);
}

// Returns true if the player is on ground
bool CPlayerInfo::isOnGround(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
		return true;
	return false;
}

// Returns true if the player is jumping upwards
bool CPlayerInfo::isJumpUpwards(void)
{
	if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
		return true;
	return false;
}

// Returns true if the player is on freefall
bool CPlayerInfo::isFreeFall(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
		return true;
	return false;
}

// Set the player's status to free fall mode
void CPlayerInfo::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CPlayerInfo::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		hero_inMidAir_Up = true;
		hero_inMidAir_Down = false;
		mapOffset_yBeforeJump = mapOffset_y;
		jumpspeed = 900;
	}
}

// Set position x of the player
void CPlayerInfo::SetPos_x(int pos_x, bool intial)
{
	theHeroPosition.x = pos_x;
	if(intial)
		theHeroInitialPosition.x = pos_x;
}

// Set position y of the player
void CPlayerInfo::SetPos_y(int pos_y, bool intial)
{
	theHeroPosition.y = pos_y;
	if(intial)
		theHeroInitialPosition.y = pos_y;
}

// Set Jumpspeed of the player
void CPlayerInfo::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void CPlayerInfo::SetToStop(void)
{
	hero_inMidAir_Up = false;
	hero_inMidAir_Down = false;
	jumpspeed = 0;
}

/********************************************************************************
Hero Move Up Down
********************************************************************************/
void CPlayerInfo::MoveUpDown(const bool mode, const float timeDiff, CMap* m_cMap)
{
	if (mode)
	{
		theHeroPosition.y = theHeroPosition.y + (int) (movementSpeed * timeDiff);
		heroAnimationDirection = UP;
		heroAnimationInvert = false;
		heroAnimationCounter += 30 * timeDiff;
		if(heroAnimationCounter > 5.0f)
			heroAnimationCounter = 0.0f;
		if(mapOffset_y <= 0)
		{
			ConstrainHero(32, 992, 32, 768, timeDiff, m_cMap);
		}
		else
		{
			ConstrainHero(32, 992, 432, 768, timeDiff, m_cMap);
		}
	}
	else
	{
		theHeroPosition.y = theHeroPosition.y - (int) (movementSpeed * timeDiff);
		heroAnimationDirection = DOWN;
		heroAnimationInvert = false;
		heroAnimationCounter += 30 * timeDiff;
		if(heroAnimationCounter > 5.0f)
			heroAnimationCounter = 0.0f;
		if(mapOffset_y >= (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize())
		{
			ConstrainHero(32, 992, 32, 768, timeDiff, m_cMap);
		}
		else
		{
			ConstrainHero(32, 992, 32, 368, timeDiff, m_cMap);
		}
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void CPlayerInfo::MoveLeftRight(const bool mode, const float timeDiff, CMap* m_cMap)
{
	if (mode)
	{
		theHeroPosition.x = theHeroPosition.x - (int) (movementSpeed * timeDiff);
		heroAnimationDirection = LEFT;
		heroAnimationInvert = true;
		heroAnimationCounter -= 15 * timeDiff;
		if(heroAnimationCounter < 2.0f)
			heroAnimationCounter = 5.0f;
		if(mapOffset_x <= 0)
		{
			ConstrainHero(32, 992, 32, 768, timeDiff, m_cMap);
		}
		else
		{
			ConstrainHero(480, 992, 32, 768, timeDiff, m_cMap);
		}
	}
	else
	{
		theHeroPosition.x = theHeroPosition.x + (int) (movementSpeed * timeDiff);
		heroAnimationDirection = RIGHT;
		heroAnimationInvert = false;
		heroAnimationCounter += 15 * timeDiff;
		if(heroAnimationCounter > 5.0f)
			heroAnimationCounter = 2.0f;
		if(mapOffset_x >= (m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width()) * m_cMap->GetTileSize())
		{
			ConstrainHero(32, 992, 32, 768, timeDiff, m_cMap);
		}
		else
		{
			ConstrainHero(32, 544, 32, 768, timeDiff, m_cMap);
		}
	}
}

// Get position x of the player
int CPlayerInfo::GetPos_x(void)
{
	return theHeroPosition.x;
}

// Get position y of the player
int CPlayerInfo::GetPos_y(void)
{
	return theHeroPosition.y;
}

// Get Jumpspeed of the player
int CPlayerInfo::GetJumpspeed(void)
{
	return jumpspeed;
}

// Get mapOffset_x
int CPlayerInfo::GetMapOffset_x(void)
{
	return mapOffset_x;
}

// Get mapOffset_y
int CPlayerInfo::GetMapOffset_y(void)
{
	return mapOffset_y;
}

// Get mapFineOffset_x
int CPlayerInfo::GetMapFineOffset_x(void)
{
	return mapFineOffset_x;
}

// Get mapFineOffset_y
int CPlayerInfo::GetMapFineOffset_y(void)
{
	return mapFineOffset_y;
}

// Update Jump Upwards
void CPlayerInfo::UpdateJumpUpwards()
{
	theHeroPosition.y -= jumpspeed;
	jumpspeed -= 50;
	if (jumpspeed == 0)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
	}
}

// Update FreeFall
void CPlayerInfo::UpdateFreeFall()
{
	theHeroPosition.y += jumpspeed;
	jumpspeed += 9.8;
}

// Set Animation Direction status of the player
void CPlayerInfo::SetAnimationDirection(ANIMATION_DIRECTION heroAnimationDirection)
{
	this->heroAnimationDirection = heroAnimationDirection;
}

// Get Animation Direction status of the player
CPlayerInfo::ANIMATION_DIRECTION CPlayerInfo::GetAnimationDirection(void)
{
	return heroAnimationDirection;
}

// Set Animation Invert status of the player
void CPlayerInfo::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}

// Get Animation Invert status of the player
bool CPlayerInfo::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}

// Set Animation Counter of the player
void CPlayerInfo::SetAnimationCounter(int heroAnimationCounter)
{
	this->heroAnimationCounter = heroAnimationCounter;
}

// Get Animation Counter of the player
int CPlayerInfo::GetAnimationCounter(void)
{
	return heroAnimationCounter;
}

// Set Movement Speed of the player
void CPlayerInfo::SetMovementSpeed(float movementSpeed)
{
	this->movementSpeed = movementSpeed;
}

// Get Movement Speed of the player
float CPlayerInfo::GetMovementSpeed(void)
{
	return movementSpeed;
}

// Constrain the position of the Hero to within the border
void CPlayerInfo::ConstrainHero(const int leftBorder, const int rightBorder,
	const int topBorder, const int bottomBorder,
	float timeDiff, CMap* m_cMap)
{
	if (theHeroPosition.x < leftBorder)
	{
		theHeroPosition.x = leftBorder;
		mapOffset_x = mapOffset_x - (int) (movementSpeed * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (theHeroPosition.x > rightBorder)
	{
		theHeroPosition.x = rightBorder;
		mapOffset_x = mapOffset_x + (int) (movementSpeed * timeDiff);
		if (mapOffset_x > (m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width()) * m_cMap->GetTileSize()) // This must be changed to soft-coded
			mapOffset_x = (m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width()) * m_cMap->GetTileSize();
	}

	if(theHeroPosition.y < topBorder)
	{
		theHeroPosition.y = topBorder;
		mapOffset_y = mapOffset_y - (int) (jumpspeed * timeDiff);
		if(mapOffset_y > (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize())
			mapOffset_y = (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize();
	}
	else if(theHeroPosition.y > bottomBorder)
	{
		theHeroPosition.y = bottomBorder;
		mapOffset_y = mapOffset_y - (int) (movementSpeed * timeDiff);
		if(mapOffset_y < 0)
			mapOffset_y = 0;
	}
}

/********************************************************************************
Hero Update
********************************************************************************/
void CPlayerInfo::HeroUpdate(CMap* m_cMap, float timeDiff)
{
	// Update Hero's info
	// Don't jump
	if(sideView)
	{
		if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
		{
			// Fall
			if(CheckCollision(theHeroPosition.x, theHeroPosition.y, false, true, false, false, m_cMap) == 0)
			{
				SetOnFreeFall(true);
				mapOffset_yBeforeJump = mapOffset_y;
			}
		}
		else if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
		{
			// Check if the hero can move up into mid air...
			int checkPosition_X = (int) ((mapOffset_x + theHeroPosition.x) / m_cMap->GetTileSize());
			int checkPosition_Y = m_cMap->getNumOfTiles_MapHeight() - (int) ceil( (float) (theHeroPosition.y + (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize() - mapOffset_y - mapFineOffset_y + jumpspeed * timeDiff) / m_cMap->GetTileSize());

			if ( (m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X] == 1) ||
				(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X+1] == 1) )
			{
				// Since the new position does not allow the hero to move into, then go back to the old position
				//theHeroPosition.y = ((int) (theHeroPosition.y / m_cMap->GetTileSize())) * m_cMap->GetTileSize();
				int tileY = 768 -(checkPosition_Y)*m_cMap->GetTileSize() + mapOffset_y;
				if(mapOffset_yBeforeJump != mapOffset_y)
				{
					int diff = theHeroPosition.y - tileY - m_cMap->GetTileSize();
					theHeroPosition.y = 32 - mapFineOffset_y + tileY + m_cMap->GetTileSize();
					mapOffset_y += diff;
				}
				else
				{
					theHeroPosition.y = tileY + m_cMap->GetTileSize();
				}
				hero_inMidAir_Up = false;
				hero_inMidAir_Down = true;
				jumpspeed = 0;
			}
			else
			{
				theHeroPosition.y += jumpspeed * timeDiff;
				jumpspeed -= GRAVITY * timeDiff;;
				if (jumpspeed <= 0)
				{
					hero_inMidAir_Up = false;
					hero_inMidAir_Down = true;
				}
			}
		}
		else if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
		{
			// Check if the hero is still in mid air...
			int checkPosition_X = (int) ((mapOffset_x + theHeroPosition.x) / m_cMap->GetTileSize());
			if (checkPosition_X < 0)
				checkPosition_X = 0;
			if (checkPosition_X > m_cMap->getNumOfTiles_MapWidth())
				checkPosition_X = m_cMap->getNumOfTiles_MapWidth();

			int checkPosition_Y1 = m_cMap->getNumOfTiles_MapHeight() - (int) ceil( (float) (theHeroPosition.y + (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize() - mapOffset_y - mapFineOffset_y) / m_cMap->GetTileSize());
			if (checkPosition_Y1 < 0)
				checkPosition_Y1 = 0;
			if (checkPosition_Y1 > m_cMap->getNumOfTiles_MapHeight())
				checkPosition_Y1 = m_cMap->getNumOfTiles_MapHeight();

			// Check current frame
			if ( (m_cMap->theScreenMap[checkPosition_Y1][checkPosition_X] == 1) ||
				(m_cMap->theScreenMap[checkPosition_Y1][checkPosition_X+1] == 1) )
			{
				// Since the new position does not allow the hero to move into, then go back to the old position
				int i = 0;
				while(true)
				{
					if (m_cMap->theScreenMap[checkPosition_Y1 - 1 -i][checkPosition_X] == 1 ||
						(m_cMap->theScreenMap[checkPosition_Y1 - 1 - i][checkPosition_X+1] == 1) )
					{
						++i;
					}
					else
					{
						break;
					}
				}
				int tileY = 768 -(checkPosition_Y1 - 1 - i)*m_cMap->GetTileSize() + mapOffset_y;

				if(mapOffset_yBeforeJump != mapOffset_y)
				{
					int diff = theHeroPosition.y - tileY - m_cMap->GetTileSize();
					theHeroPosition.y = 32 - mapFineOffset_y + tileY + m_cMap->GetTileSize();
					mapOffset_y += diff;
				}
				else
				{
					theHeroPosition.y = tileY + m_cMap->GetTileSize();
				}
				hero_inMidAir_Down = false;
				jumpspeed = 0;
			}
			else if( (m_cMap->theScreenMap[checkPosition_Y1][checkPosition_X] == 2) ||
				(m_cMap->theScreenMap[checkPosition_Y1][checkPosition_X+1] == 2) )
			{
				if (m_cMap->theScreenMap[checkPosition_Y1 - 1][checkPosition_X] == 1 ||
					(m_cMap->theScreenMap[checkPosition_Y1 - 1][checkPosition_X+1] == 1))
				{
					int i = 0;
					while(true)
					{
						if (m_cMap->theScreenMap[checkPosition_Y1 - 1 -i][checkPosition_X] == 1 ||
							(m_cMap->theScreenMap[checkPosition_Y1 - 1 - i][checkPosition_X+1] == 1) )
						{
							++i;
						}
						else
						{
							break;
						}
					}
					int tileY = 768 -(checkPosition_Y1 - 1 - i)*m_cMap->GetTileSize() + mapOffset_y;

					if(mapOffset_yBeforeJump != mapOffset_y)
					{
						int diff = theHeroPosition.y - tileY - m_cMap->GetTileSize();
						theHeroPosition.y = 32 - mapFineOffset_y + tileY + m_cMap->GetTileSize();
						mapOffset_y += diff;
					}
					else
					{
						theHeroPosition.y = tileY + m_cMap->GetTileSize();
					}
				}
				else
				{
					currentState = DYING;
				}
				hero_inMidAir_Down = false;
				jumpspeed = 0;
			}
			else
			{
				// Check next frame
				int checkPosition_Y2 = m_cMap->getNumOfTiles_MapHeight() - (int) ceil( (float) (theHeroPosition.y + (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize() - mapOffset_y - mapFineOffset_y + jumpspeed * timeDiff) / m_cMap->GetTileSize());
				if (checkPosition_Y2 < 0)
					checkPosition_Y2 = 0;
				if (checkPosition_Y2 > m_cMap->getNumOfTiles_MapHeight())
					checkPosition_Y2 = m_cMap->getNumOfTiles_MapHeight();

				if ( (m_cMap->theScreenMap[checkPosition_Y2][checkPosition_X] == 1) ||
					(m_cMap->theScreenMap[checkPosition_Y2][checkPosition_X+1] == 1) )
				{
					// Since the new position does not allow the hero to move into, then go back to the old position
					int i = 0;
					while(true)
					{
						if (m_cMap->theScreenMap[checkPosition_Y2 - 1 -i][checkPosition_X] == 1 ||
							(m_cMap->theScreenMap[checkPosition_Y2 - 1 - i][checkPosition_X+1] == 1) )
						{
							++i;
						}
						else
						{
							break;
						}
					}
					int tileY = 768 -(checkPosition_Y2 - 1 - i)*m_cMap->GetTileSize() + mapOffset_y;

					if(mapOffset_yBeforeJump != mapOffset_y)
					{
						int diff = theHeroPosition.y - tileY - m_cMap->GetTileSize();
						theHeroPosition.y = 32 - mapFineOffset_y + tileY + m_cMap->GetTileSize();
						mapOffset_y += diff;
					}
					else
					{
						theHeroPosition.y = tileY + m_cMap->GetTileSize();
					}
					hero_inMidAir_Down = false;
					jumpspeed = 0;
				}
				else if( (m_cMap->theScreenMap[checkPosition_Y2][checkPosition_X] == 2) ||
					(m_cMap->theScreenMap[checkPosition_Y2][checkPosition_X+1] == 2) )
				{
					if (m_cMap->theScreenMap[checkPosition_Y2 - 1][checkPosition_X] == 1 ||
						(m_cMap->theScreenMap[checkPosition_Y2 - 1][checkPosition_X+1] == 1))
					{
						int i = 0;
						while(true)
						{
							if (m_cMap->theScreenMap[checkPosition_Y2 - 1 -i][checkPosition_X] == 1 ||
								(m_cMap->theScreenMap[checkPosition_Y2 - 1 - i][checkPosition_X+1] == 1) )
							{
								++i;
							}
							else
							{
								break;
							}
						}
						int tileY = 768 -(checkPosition_Y2 - 1 - i)*m_cMap->GetTileSize() + mapOffset_y;

						if(mapOffset_yBeforeJump != mapOffset_y)
						{
							int diff = theHeroPosition.y - tileY - m_cMap->GetTileSize();
							theHeroPosition.y = 32 - mapFineOffset_y + tileY + m_cMap->GetTileSize();
							mapOffset_y += diff;
						}
						else
						{
							theHeroPosition.y = tileY + m_cMap->GetTileSize();
						}
					}
					else
					{
						currentState = DYING;
					}
					hero_inMidAir_Down = false;
					jumpspeed = 0;
				}
				else
				{
					theHeroPosition.y += jumpspeed * timeDiff;
					jumpspeed -= GRAVITY * timeDiff;
				}
			}
		}
		if(mapOffset_y >= 1504)
			ConstrainHero(32, 992, 32, 768, timeDiff, m_cMap);
		else
			ConstrainHero(32, 992, 160, 768, timeDiff, m_cMap);
	}
	// Calculate the fine offset
	mapFineOffset_x = mapOffset_x % m_cMap->GetTileSize();
	mapFineOffset_y = mapOffset_y % m_cMap->GetTileSize();
}

// Check for collision of hero with obstacles in a certain place
int CPlayerInfo::CheckCollision(float pos_x, float pos_y,
	bool m_bCheckUpwards, bool m_bCheckDownwards,
	bool m_bCheckLeft, bool m_bCheckRight,CMap* m_cMap, bool isHero)
{
	// The pos_x and pos_y are the top left corner of the hero, so we find the tile which this position occupies.
	int checkPosition_X = (int) ((mapOffset_x + pos_x) / m_cMap->GetTileSize());
	int checkPosition_Y = m_cMap->getNumOfTiles_MapHeight() - (int) ceil( (float) (pos_y + (m_cMap->getNumOfTiles_MapHeight() - m_cMap->GetNumOfTiles_Height()) * m_cMap->GetTileSize() - mapOffset_y - mapFineOffset_y) / m_cMap->GetTileSize());

	if(m_bCheckLeft)
	{
		if(isHero)
		{
			if(!sideView)
			{
				if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X] == 1 ||
					m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
					return 1;
			}
		}
		if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X] == 1)
					return 1;
	}
	if(m_bCheckRight)
	{
		if(isHero)
		{
			if(!sideView)
			{
				if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X + 1] == 1||
					m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1)
					return 1;
				else if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X+1] == 3)
					return 3;
			}
		}
		if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X + 1] == 1)
			return 1;
		else if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X+1] == 3)
			return 3;
	}
	if(m_bCheckUpwards)
	{
		if(m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X] == 1 ||
			m_cMap->theScreenMap[checkPosition_Y-1][checkPosition_X+1] == 1)
			return 1;
	}
	if(m_bCheckDownwards)
	{
		if(m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1 ||
			m_cMap->theScreenMap[checkPosition_Y][checkPosition_X+1] == 1)
			return 1;
	}

	return 0;
}

void CPlayerInfo::Reset(void)
{
	hero_inMidAir_Up = false;
	hero_inMidAir_Down = false;
	jumpspeed = 0;
	heroAnimationDirection = DOWN;
	heroAnimationCounter = 0.0f;
	heroAnimationInvert = false;
	mapOffset_x = 0;
	mapOffset_y = 0;
	mapFineOffset_x = 0;
	mapFineOffset_y = 0;
	mapOffset_yBeforeJump = 0;
	theHeroPosition = theHeroInitialPosition;
	timeElasped = 0.f;
	currentState = CPlayerInfo::PLAYING;
}

void CPlayerInfo::SetCurrentState(CPlayerInfo::CURRENT_STATE currentState)
{
	this->currentState = currentState;
}

CPlayerInfo::CURRENT_STATE CPlayerInfo::GetCurrentState(void)
{
	return currentState;
}

void CPlayerInfo::SetTimeElasped(float timeElasped)
{
	this->timeElasped = timeElasped;
}

float CPlayerInfo::GetTimeElasped(void)
{
	return timeElasped;
}

void CPlayerInfo::SetNoOfCoins(int noOfCoins)
{
	this->noOfCoins = noOfCoins;
}

int CPlayerInfo::GetNoOfCoins(void)
{
	return noOfCoins;
}

void CPlayerInfo::SetNoOfLives(int noOfLives)
{
	this->noOfLives = noOfLives;
}

int CPlayerInfo::GetNoOfLives(void)
{
	return noOfLives;
}

void CPlayerInfo::SetSideView(bool sideView)
{
	this->sideView = sideView;
}

bool CPlayerInfo::GetSideView(void)
{
	return sideView;
}