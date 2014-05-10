#include "GameLayer.h"
using namespace cocos2d;

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	return true;
}

void GameLayer::setPhyWorld( PhysicsWorld* __world )
{

}

void GameLayer::onTouch()
{

}
