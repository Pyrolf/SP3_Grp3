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
		PAUSE,
		MOVING,
		GAMEPLAYING,
		PLAYER_ATTACK,
		STOPPLAY
	};

	void playSound(SOUND_TYPE);
	void exiting();
};