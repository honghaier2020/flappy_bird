#include "WelcomeScene.h"
#include "WelcomeLayer.h"
WelcomeScene::WelcomeScene()
{

}

WelcomeScene::~WelcomeScene()
{

}

bool WelcomeScene::init()
{
	Scene::init();
	auto __welcome_layer = WelcomeLayer::create();
	this->addChild(__welcome_layer);
	return true;
}
