#include "Sound.h"
ISoundEngine * engine;

Sound::Sound()
{
}

Sound::~Sound()
{
}

//int Sound::soundInit()
//{
//	engine = createIrrKlangDevice();
//	if(!engine)
//		return 0;
//	return 0;
//}

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

