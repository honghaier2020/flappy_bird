#include "SpriteBird.h"
#include "AtlasLoader.h"
using namespace cocos2d;

SpriteBird* SpriteBird::inst_ = nullptr;

SpriteBird::SpriteBird()
{
	if(0)
	{
		is_first_time_ = 0;
		idle_action_ = NULL;
		swing_action_ = NULL;
		currentStatus_ = ACTION_STATE_IDLE;
	}
}

SpriteBird::~SpriteBird()
{

}

SpriteBird* SpriteBird::getInstance()
{
	if(!inst_)
	{
		inst_ = new SpriteBird();
		if(!inst_->init())
		{
			delete(inst_);
			inst_ = NULL;
			CCLOG("ERROR: Could not init inst_");
		}
	}
	return inst_;
}

bool SpriteBird::init()
{
	is_first_time_ = 3;
	return true;

}

bool SpriteBird::createBird()
{
	createBirdByRandom();
	if(Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(bird_name_)))
	{
		Animation* __animation = createAnimation(bird_name_format_.c_str(),3,10);
		Animate* __animate = Animate::create(__animation);
		idle_action_ = RepeatForever::create(__animate);

		ActionInterval* __up = CCMoveBy::create(0.4f,Point(0,8));
		ActionInterval* __up_back = __up->reverse();
		swing_action_ = RepeatForever::create(Sequence::create(__up,__up_back,NULL));
		return true;
	}
	return false;
}

void SpriteBird::idle()
{
	if (changeState(ACTION_STATE_IDLE)) {
		this->runAction(idle_action_);
		this->runAction(swing_action_);
	}
}

void SpriteBird::createBirdByRandom()
{
	if(this->is_first_time_ & 1)
	{
		this->is_first_time_ &= 2;
	}
	else if(this->is_first_time_ & 2)
	{
		this->is_first_time_ &= 1;
		return ;
	}
	srand((unsigned)time(NULL));
	int type = ((int)rand())% 3;
	switch (type)
	{
	case 0:
		this->bird_name_ = "bird0_0";
		this->bird_name_format_ = "bird0_%d";
		break;
	case 1:
		this->bird_name_ = "bird1_0";
		this->bird_name_format_ = "bird1_%d";
		break;
	case 2:
		this->bird_name_ = "bird2_0";
		this->bird_name_format_ = "bird2_%d";
		break;
	default:
		this->bird_name_ = "bird2_0";
		this->bird_name_format_ = "bird2_%d";
		break;
	}
}

cocos2d::Animation* SpriteBird::createAnimation( const char* __fmt, int __count, float __fps )
{
	Animation* __animation = Animation::create();
	if(__animation)
	{
		__animation->setDelayPerUnit(1/__fps);
		for(int i = 0; i < __count; ++i)
		{
			const char* __frame_name = String::createWithFormat(__fmt,i)->getCString();
			SpriteFrame* __sprite_Frame = AtlasLoader::getInstance()->getSpriteFrameByName(__frame_name);
			__animation->addSpriteFrame(__sprite_Frame);
		}
	}
	return __animation;
}

bool SpriteBird::changeState( ActionState __state )
{
	currentStatus_ = __state;
	return true;
}

void SpriteBird::fly()
{
	if(changeState(ACTION_STATE_FLY)) {
		this->stopAction(swing_action_);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void SpriteBird::die()
{
	if(changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
	}
}


