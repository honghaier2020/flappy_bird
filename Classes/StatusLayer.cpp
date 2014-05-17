#include "StatusLayer.h"
#include "Number.h"

using namespace cocos2d;

StatusLayer::StatusLayer()
{
	best_scores_ = 0;
	current_scores_ = 0;
	new_record_ = false;
	score_sprite_ = NULL;
	getready_sprite_ = NULL;
	tutorial_sprite_ = NULL;
	white_sprite_ = NULL;
	blink_sprite_ = NULL;
}

StatusLayer::~StatusLayer()
{

}

bool StatusLayer::init()
{
	if(!Layer::init()){
		return false;
	}
	Number::getInstance()->loadNumber(NUMBER_FONT.c_str(), "font_0%02d", 48);
	Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(), "number_score_%02d");
	this->visible_size_ = Director::getInstance()->getVisibleSize();
	this->origin_point_ = Director::getInstance()->getVisibleOrigin();
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::onGameStart( void )
{
	showStartStatus();
}

void StatusLayer::onGamePlaying( int __score )
{
	this->removeChild(score_sprite_);
	score_sprite_ = (Sprite* )Number::getInstance()->convert(NUMBER_FONT.c_str(), __score);
	score_sprite_->setPosition(Point(origin_point_.x + visible_size_.width / 2,origin_point_.y + visible_size_.height *5/6));
	this->addChild(score_sprite_);
}

void StatusLayer::onGameEnd( int __cur_socre, int __best_score )
{
	showOverStatus(__cur_socre,__best_score);
}

void StatusLayer::showReadyStatus()
{
	score_sprite_ = (Sprite *)Number::getInstance()->convert(NUMBER_FONT.c_str(), 0);
	score_sprite_->setPosition(Point(origin_point_.x + visible_size_.width / 2,origin_point_.y + visible_size_.height *5/6));
	this->addChild(score_sprite_);

	getready_sprite_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	getready_sprite_->setPosition(Point(origin_point_.x + visible_size_.width / 2, origin_point_.y + visible_size_.height *2/3));
	this->addChild(getready_sprite_);

	tutorial_sprite_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	tutorial_sprite_->setPosition(Point(origin_point_.x + visible_size_.width / 2, origin_point_.y + visible_size_.height * 1/2));
	this->addChild(tutorial_sprite_);
}

void StatusLayer::loadWhiteSprite()
{
	//	this white sprite is used for blinking the screen for a short while
	white_sprite_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("white"));
	white_sprite_->setScale(100);
	white_sprite_->setOpacity(0);
	this->addChild(white_sprite_,WRITE_SPRITE_TAG);
}

void StatusLayer::showStartStatus()
{
	//	fade out for sprite of get ready and tutorial
	getready_sprite_->runAction(FadeOut::create(0.4f));
	tutorial_sprite_->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus( int __cur_socre, int __best_score )
{
	this->current_scores_ = __cur_socre;
	this->best_scores_ = __best_score;
	if(__cur_socre > __best_score){
		this->best_scores_ = __cur_socre;
		this->new_record_ = true;
	}else{
		this->new_record_ = false;
	}
	this->removeChild(score_sprite_);
	this->blinkFullScreen();
}

void StatusLayer::blinkFullScreen()
{

}

