#include "OptionLayer.h"
using namespace cocos2d;

OptionLayer::OptionLayer()
{

}

OptionLayer::~OptionLayer()
{

}

bool OptionLayer::init()
{
	if (Layer::init())
	{
		auto __event_dispatcher = Director::getInstance()->getEventDispatcher();
		auto __listener = EventListenerTouchAllAtOnce::create();
		__listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan,this);
		__event_dispatcher->addEventListenerWithSceneGraphPriority(__listener, this);  
		return true;
	}
	return false;
}

void OptionLayer::onTouchesBegan( const std::vector<cocos2d::Touch*>& __touches, cocos2d::Event* __events )
{
	this->delegator->onTouch();
}

