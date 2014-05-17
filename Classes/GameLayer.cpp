#include "GameLayer.h"
#include "SpriteBird.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y)) 
#define max(X,Y) ((X) > (Y) ? (X) : (Y)) 

GameLayer::GameLayer()
{
	bird_ = NULL;
	game_status_ = GAME_STATUS_READY;
	scores_ = 0;
	best_scores_ = 0;
	ground_node_ = NULL;
	land1_ = NULL;
	land2_ = NULL;
	physics_world_ = NULL;
	pipes_.clear();
}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if(Layer::init())
	{
		Size __visibile_size = Director::getInstance()->getVisibleSize();
		Point __origin = Director::getInstance()->getVisibleOrigin();
		
		//	add bird
		bird_ = SpriteBird::getInstance();
		bird_->createBird();
		auto __physics_body_bird = PhysicsBody::create();
		__physics_body_bird->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
		__physics_body_bird->setDynamic(true);
		__physics_body_bird->setLinearDamping(0.0f);
		__physics_body_bird->setGravityEnable(false);
		bird_->setPhysicsBody(__physics_body_bird);
		bird_->setPosition(Point(__origin.x + __visibile_size.width/3 - 5,__origin.y + __visibile_size.height/2 + 5));
		bird_->idle();
		this->addChild(bird_);
		
		//	add ground
		ground_node_ = Node::create();
		float __land_height = BackgroundLayer::getLandHeight();
		auto __physics_body_ground = PhysicsBody::create();
		__physics_body_ground->addShape(PhysicsShapeBox::create(Size(288, __land_height)));
		__physics_body_ground->setDynamic(false);
		__physics_body_ground->setLinearDamping(0.0f);
		ground_node_->setPhysicsBody(__physics_body_ground);
		ground_node_->setPosition(144,__land_height/2);
		this->addChild(ground_node_);

		//	add land
		land1_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		land1_->setAnchorPoint(Point::ZERO);
		land1_->setPosition(Point::ZERO);
		this->addChild(land1_,30);
		land2_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		land2_->setAnchorPoint(Point::ZERO);
		land2_->setPosition(land1_->getContentSize().width-2.0f,0);
		this->addChild(land2_,30);

		shift_Land_ = schedule_selector(GameLayer::scrollLand);
		this->schedule(shift_Land_, 0.01f);
		this->scheduleUpdate();
		
		auto __contact_sistener = EventListenerPhysicsContact::create();
		__contact_sistener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(__contact_sistener, this);
		return true;
	}
	return false;
}

void GameLayer::onTouch()
{
	if(game_status_ == GAME_STATUS_OVER)
	{
		return;
	}

	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(GAME_STATUS_READY == game_status_)
	{
		this->delegator->onGameStart();
		bird_->fly();
		game_status_ = GAME_STATUS_START;
		createPipes();
	}
	else if (GAME_STATUS_START == game_status_)
	{
		bird_->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::scrollLand( float __dt )
{
	land1_->setPositionX(land1_->getPositionX() - 2.0f);
	land2_->setPositionX(land1_->getPositionX() + land1_->getContentSize().width - 2.0f);
	if(land2_->getPositionX() == 0)
	{
		land1_->setPositionX(0);
	}

	// move the pips
	for (auto __singlePip : this->pipes_) {
		__singlePip->setPositionX(__singlePip->getPositionX() - 2);
		if(__singlePip->getPositionX() < -PIP_WIDTH) {
			__singlePip->setTag(PIP_NEW);
			Size __visible_size = Director::getInstance()->getVisibleSize();
			__singlePip->setPositionX(__visible_size.width);
			__singlePip->setPositionY(this->getRandomHeight());
		}
	}
}

bool GameLayer::onContactBegin( PhysicsContact& __contact )
{
	this->gameOver();
	return true;
}

void GameLayer::createPipes()
{
	Size __visible_size = Director::getInstance()->getVisibleSize();
	for(int __i = 0; __i < PIP_COUNT; ++__i)
	{
		Sprite* __pipe_up = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite* __pipe_down = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		if(__pipe_up && __pipe_down)
		{
			Node* __single_pipe = Node::create();

			// bind to pair
			__pipe_down->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
			__single_pipe->addChild(__pipe_down, 0, DOWN_PIP);
			__single_pipe->addChild(__pipe_up, 0, UP_PIP);
			__single_pipe->setPosition(__visible_size.width + __i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
			auto __body = PhysicsBody::create();
			auto __shapeBoxDown = PhysicsShapeBox::create(__pipe_down->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
			__body->addShape(__shapeBoxDown);
			__body->addShape(PhysicsShapeBox::create(__pipe_up->getContentSize()));
			__body->setDynamic(false);
			__single_pipe->setPhysicsBody(__body);
			__single_pipe->setTag(PIP_NEW);

			this->addChild(__single_pipe);
			pipes_.push_back(__single_pipe);
		}
	}
}


int GameLayer::getRandomHeight() {
	Size __visible_size = Director::getInstance()->getVisibleSize();
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - __visible_size.height);
}

void GameLayer::update( float __delta )
{
	if(GAME_STATUS_START == game_status_)
	{
		this->rotateBird();
		this->checkHit();
	}
}

void GameLayer::rotateBird()
{
	float __vertical_speed = bird_->getPhysicsBody()->getVelocity().y;
	bird_->setRotation(min(max(-90, (__vertical_speed*0.2 + 60)), 30));
}

void GameLayer::checkHit()
{
	for(auto __pipe : pipes_) {
		if (__pipe->getTag() == PIP_NEW) {
			if (__pipe->getPositionX() < bird_->getPositionX()) {
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->scores_ ++;
				this->delegator->onGamePlaying(scores_);
				__pipe->setTag(PIP_PASS);
			}
		}
	}
}

void GameLayer::gameOver()
{
	if(game_status_ == GAME_STATUS_OVER) {
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
	
	if(this->scores_ > best_scores_){
		best_scores_ = scores_;
	}

	this->delegator->onGameEnd(scores_, best_scores_);
	this->unschedule(shift_Land_);

	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");

	bird_->die();
	bird_->setRotation(-90);
	birdSpriteFadeOut();
	game_status_ = GAME_STATUS_OVER;

}

void GameLayer::birdSpriteFadeOut()
{
	FadeOut* __animation = FadeOut::create(1.5);
	CallFunc* __animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove,this));
	Sequence* __sequence = Sequence::createWithTwoActions(__animation,__animationDone);
	bird_->stopAllActions();
	bird_->runAction(__sequence);
}

void GameLayer::birdSpriteRemove()
{
	bird_->setRotation(0);
	this->removeChild(this->bird_);
}

