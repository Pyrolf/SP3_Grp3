#include "Sound.h"



Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::soundInit()
{
	engine = createIrrKlangDevice();
	if(!engine)
		return;
	return;
}

void Sound::playSound(SOUND_TYPE sound_type)
{
	switch(sound_type)
	{
	case PLAYER_ATTACK:
		engine->play2D("../media/attack.wav");
		break;
	case MENUCHOICE:
		engine->play2D("../media/soundeff1.wav");
		break;
	case MENU_ENTER:
		engine->play2D("../media/select.mp3");
		break;
	case MENUMUSIC:
		engine->play2D("../media/mainmenu.mp3",true);
		break;
	case PAUSE:
		engine->play2D("../media/S_SDI_00006.wav");
		break;
	case GAMEPLAYING:
		engine->play2D("../media/playingsound.mp3", true);
		break;
	case MOVING:
		engine->play2D("../media/");
		break;
	case STOPPLAY:
		engine->stopAllSounds();
		break;
	}
}

void Sound::exiting()
{
	engine->stopAllSounds();
	if(engine)
	{
		delete engine;
		engine = NULL;
	}

}
/*
ISoundEngine * engine = createIrrKlangDevice();
if(!engine)

engine->play2D("../../media/getout.ogg", true);

extern ISoundEngine * engine; add this to respective classes

eg. while(i != 'q')
{
engine->play2D("../../media/...");
}

put code in exit
engine->stopAllSounds();

*/

