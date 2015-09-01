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
	void soundInit();
	enum SOUND_TYPE
	{
		MENUCHOICE,
		MENU_ENTER,
		MENUMUSIC,
		PLAYER_DAMAGED,        //groan
		ZOMBIE_DAMAGED,
		HACK_SUCCESS,
		DOOR_OPEN,
		HACK_FAILURE,
		GAMEPLAYING,
		PLAYER_ATTACK,
		WATER_SPLASH,
		GAMEOVER
	};

	void playSound(SOUND_TYPE);
	void exiting();
};