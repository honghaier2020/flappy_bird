#include "WelcomeLayer.h"
#include "AtlasLoader.h"
#include "SpriteBird.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

WelcomeLayer::WelcomeLayer()
{
	land1_ = NULL;
	land2_ = NULL;
	bird_ = NULL;
}

WelcomeLayer::~WelcomeLayer()
{

}

bool WelcomeLayer::init()
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

	Size __visibile_size = Director::getInstance()->getVisibleSize();
	Point __origin = Director::getInstance()->getVisibleOrigin();
	//	add game title
	Sprite* __title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	if(__title)
	{
		__title->setPosition(__origin.x + __visibile_size.width/2,__origin.y + __visibile_size.height*5/7);
		this->addChild(__title);
	}
	//	add start menu
	Sprite* __start_menu = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* __active_start_menu = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	if(__start_menu && __active_start_menu)
	{
		__active_start_menu->setPositionY(5);
		auto __menu_item = MenuItemSprite::create(__start_menu,__active_start_menu,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallback,this));
		__menu_item->setPosition(Point(__origin.x + __visibile_size.width/2,__origin.y + __visibile_size.height*2/5));

		auto __menu = Menu::create(__menu_item,NULL);
		__menu->setPosition(Point(__origin.x ,__origin.y));
		this->addChild(__menu,1);
	}
	//	create bird
	if(1){
		bird_ = SpriteBird::getInstance();
		bird_->createBird();
		bird_->setTag(BIRD_SPRITE_TAG);
		bird_->setPosition(Point(__origin.x + __visibile_size.width/2,__origin.y + __visibile_size.height*3/5 - 10));
		bird_->idle();
		this->addChild(bird_);
	}

	//	add land
	land1_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	land1_->setAnchorPoint(Point::ZERO);
	land1_->setPosition(Point::ZERO);
	this->addChild(land1_);
	land2_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	land2_->setAnchorPoint(Point::ZERO);
	land2_->setPosition(Point::ZERO);
	this->addChild(land2_);

	this->schedule(schedule_selector(WelcomeLayer::scrollLand),0.01f);

	Sprite* __copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	if(__copyright)
	{
		__copyright->setPosition(Point(__origin.x + __visibile_size.width/2,__origin.y + __visibile_size.height/6));
		this->addChild(__copyright);
	}
	return true;
}

void WelcomeLayer::menuStartCallback(Ref* __sender)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto __scene = GameScene::create();
	TransitionScene* __transtition = TransitionFade::create(1,__scene);
	Director::getInstance()->replaceScene(__transtition);
}

void WelcomeLayer::scrollLand( float __dt )
{
	this->land1_->setPositionX(this->land1_->getPositionX() - 2.0f);
	this->land2_->setPositionX(this->land1_->getPositionX() + this->getContentSize().width - 2.0f);
	if(0 == this->land2_->getPositionX())
	{
		this->land1_->setPositionX(0);
	}
}
