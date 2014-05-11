#include "BackgroundLayer.h"
#include "AtlasLoader.h"
using namespace cocos2d;


BackgroundLayer::BackgroundLayer()
{

}

BackgroundLayer::~BackgroundLayer()
{

}

bool BackgroundLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	time_t __t = time(NULL);  
	tm* __lt = localtime(&__t);  
	int __hour = __lt->tm_hour;  
	Sprite* __background = NULL;
	if(__hour >= 6 && __hour<= 17)
	{
		__background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}
	else{
		__background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	__background->setAnchorPoint(Point::ZERO);
	__background->setPosition(Point::ZERO);
	this->addChild(__background);
	return true;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}
