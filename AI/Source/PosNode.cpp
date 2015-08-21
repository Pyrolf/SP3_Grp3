#include "PosNode.h"
#include <iostream>


CPosNode::CPosNode(void)
{
	pos = Vector3(0,0,0);
	posType = NONE;
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
}

CPosNode:: CPosNode(Vector3 newPos, int newPosType)
{
	pos = newPos;
	posType = newPosType;
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
}

CPosNode::~CPosNode(void)
{
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
}