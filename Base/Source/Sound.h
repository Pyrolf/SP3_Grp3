#pragma once
#include <irrKlang.h>

#pragma comment(lib,"irrKlang.lib")

using namespace irrklang;


class Sound
{
public:
	Sound();
	~Sound();
	ISoundEngine * engine;
	ISoundEngine * engine2;
	void soundInit();
	enum SOUND_TYPE
	{
		MENUCHOICE,
		MENU_ENTER,
		FALLINGENDING,
		PLAYER_DAMAGED,        //groan
		ZOMBIE_DAMAGED,
		HACK_SUCCESS,
		DOOR_OPEN,
		HACK_FAILURE,
		GAMEPLAYING,
		PLAYER_DYING,
		MAINMENU,
		FOOTSTEP,
		PLAYER_ATTACK,
		WATER_SPLASH,
		GAMEOVER
	};

	void playSound(SOUND_TYPE);
	void exiting();
};