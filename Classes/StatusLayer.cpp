#include "StatusLayer.h"
#include "Number.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

StatusLayer::StatusLayer()
{
	best_scores_ = 0;
	current_scores_ = 0;
	tmp_scores_ = 0;
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
	//display a flash blink
	auto __fade_out = FadeOut::create(0.1f);
	auto __fade_in = FadeIn::create(0.1f);
	auto __blink_action = Sequence::create(__fade_in,__fade_out,NULL);
	CallFunc* __action_done = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(__blink_action, __action_done);
	white_sprite_->stopAllActions();
	white_sprite_->runAction(sequence);
}

void StatusLayer::fadeInGameOver()
{
	// create the game over panel
	Sprite* gameover_sprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameover_sprite->setPosition(Point(origin_point_.x + visible_size_.width / 2, origin_point_.y + visible_size_.height *2/3));
	this->addChild(gameover_sprite);
	auto gameover_fade_in = FadeIn::create(0.5f);
	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameover_fade_in, actionDone);
	gameover_sprite->stopAllActions();
	gameover_sprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel()
{
	// create the score panel
	Sprite* __scorepanel_sprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	__scorepanel_sprite->setPosition(Point(origin_point_.x + visible_size_.width / 2, origin_point_.y - __scorepanel_sprite->getContentSize().height));
	this->addChild(__scorepanel_sprite);

	//display the  best score on the score panel
	auto best_score_sprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), best_scores_, Gravity::GRAVITY_RIGHT);
	best_score_sprite->setAnchorPoint(Point(1, 1));
	best_score_sprite->setPosition(__scorepanel_sprite->getContentSize().width - 28 ,
		50);
	__scorepanel_sprite->addChild(best_score_sprite);


	string __medals_name = this->getMedalsName(current_scores_);
	if(__medals_name != "") {
		Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(__medals_name));
		medalsSprite->addChild(blink_sprite_);
		medalsSprite->setPosition(54, 58);
		__scorepanel_sprite->addChild(medalsSprite);
	}

	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if(this->new_record_){
		Sprite* new_tag_sprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("new"));
		new_tag_sprite->setPosition(-16, 12);
		best_score_sprite->addChild(new_tag_sprite);
	}

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(origin_point_.x + visible_size_.width / 2,origin_point_.y + visible_size_.height/2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* __sine_in = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc* __action_done = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(__sine_in, __action_done);
	__scorepanel_sprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	__scorepanel_sprite->runAction(sequence);
}

std::string StatusLayer::getMedalsName( int __score )
{
	this->setBlinkSprite();

	//display the golden silver or bronze iron
	string __medals_name = "";
	if(this->current_scores_ >=1 && this->current_scores_ < 2){//iron medals
		__medals_name = "medals_0";
	}else if(this->current_scores_ >= 2 && current_scores_ < 3){//bronze medals
		__medals_name = "medals_1";
	}else if(current_scores_ >=3 && current_scores_ < 5){//silver medals
		__medals_name = "medals_2";
	}else if(current_scores_ >=5){//golden medals
		__medals_name = "medals_3";
	}
	return __medals_name;
}

void StatusLayer::fadeInRestartBtn()
{
	Node * tmpNode = Node::create();

	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin_point_.x + visible_size_.width / 2 - restartBtn->getContentSize().width / 2, origin_point_.y + visible_size_.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(origin_point_.x + visible_size_.width / 2 + rateBtn->getContentSize().width / 2, this->origin_point_.y + visible_size_.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);

	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::setBlinkSprite()
{
	blink_sprite_ = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("blink_00"));
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	blink_sprite_->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction()
{
	if(blink_sprite_ && blink_sprite_->getParent()) {
		Size activeSize = blink_sprite_->getParent()->getContentSize();
		blink_sprite_->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}

void StatusLayer::refreshScoreCallback()
{
	tmp_scores_ = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}

void StatusLayer::menuRestartCallback( cocos2d::Ref* __sender )
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void StatusLayer::refreshScoreExecutor( float __dt )
{
	if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
		this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	score_sprite_ = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), tmp_scores_, Gravity::GRAVITY_RIGHT);
	score_sprite_->setAnchorPoint(Point(1,0));
	score_sprite_->setPosition(Point(origin_point_.x + visible_size_.width * 3 / 4 + 20.0f, origin_point_.y + visible_size_.height *  1 / 2));
	score_sprite_->setTag(CURRENT_SCORE_SPRITE_TAG);
	this->addChild(score_sprite_,1000);
	tmp_scores_++;
	if(tmp_scores_ > current_scores_){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

