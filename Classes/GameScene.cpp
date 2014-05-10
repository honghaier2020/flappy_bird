#include "GameScene.h"
#include "BackgroundLayer.h"
#include "OptionLayer.h"
#include "GameLayer.h"
#include "StatusLayer.h"

using namespace cocos2d;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	if(Scene::initWithPhysics())
	{
		this->getPhysicsWorld()->setGravity(Vect(0, -900));

		//	add background layer
		auto __background_layer = BackgroundLayer::create();
		this->addChild(__background_layer);

		auto __status_layer = StatusLayer::create();
		
		auto __game_layer = GameLayer::create();
		__game_layer->setPhyWorld(this->getPhysicsWorld());
		__game_layer->setDelegator(__status_layer);
		this->addChild(__game_layer);

		this->addChild(__status_layer);

		auto __option_layer = OptionLayer::create();
		//__option_layer->setDelegator(__game_layer);
		this->addChild(__option_layer);
		return true;
	}
	return false;
}

void GameScene::restart()
{

}

