#include "Object2DFactory.h"

Object2DFactory::Object2DFactory()
	:
objs(NULL),
objEnd(NULL)
{
	const unsigned size = 1000;

	objs = new Object2D*[size];
	objEnd = objs + size;

	for(Object2D** objPointer = objs; objPointer != objEnd; ++objPointer)
	{
		*objPointer = NULL;
	}
}

Object2DFactory::~Object2DFactory()
{
	if(objs)
	{
		for(Object2D** it = objs; it != objEnd; ++it)
		{
			Object2D* obj = *it;
			if(obj)
			{
				delete obj;
			}
		}
		delete [] objs;
		objs = NULL;
	}
}

void Object2DFactory::IncreaseSize()
{
	const unsigned increase = 100;
	const unsigned size = objEnd - objs;
	const unsigned newSize = size + increase;

	Object2D** newObjs = new Object2D*[newSize];

	if(objs)
	{
		memcpy(newObjs, objs, size * sizeof(Object2D*));

		delete objs;
		objs = NULL;
		objEnd = NULL;

		Object2D** end = newObjs + newSize;
		for(Object2D** objPointer = newObjs + size; objPointer != end; ++objPointer)
		{
			*objPointer = NULL;
		}
	}

	objs = newObjs;
	objEnd = objs + newSize;

	newObjs = NULL;
}