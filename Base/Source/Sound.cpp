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
	case GAMEPLAYING:
		engine->play2D("../media/playingbg.mp3", true);
		break;
	case WATER_SPLASH:
		engine->play2D("../media/splash.wav");
		break;
	case HACK_FAILURE:
		engine->play2D("../media/windowserror.mp3");
		break;
	case HACK_SUCCESS:
		engine->play2D("../media/hacksuccess.mp3");		
		break;
	case DOOR_OPEN:
		engine->play2D("../media/Unlock.mp3");
		break;
	case GAMEOVER:
		engine->play2D("../media/gameover4me.mp3");
		break;
	case ZOMBIE_DAMAGED:
		engine->play2D("../media/zombie_attack.mp3");
		break;
	case PLAYER_DAMAGED:
		engine->play2D("../media/grunt.wav");
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

