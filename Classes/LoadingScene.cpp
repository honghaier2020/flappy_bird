#include "LoadingScene.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"


using namespace cocos2d;
using namespace CocosDenshion;

LoadingScene::LoadingScene()
{
	
}

LoadingScene::~LoadingScene()
{

}

void LoadingScene::loadingCallBack( cocos2d::Texture2D* __texture2d )
{
	AtlasLoader::getInstance()->loadAtlas("atlas.txt",__texture2d);
	//	pre load all sound

	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");

	auto __scene = WelcomeScene::create();
	TransitionScene* __transition = TransitionFade::create(1,__scene);
	Director::getInstance()->replaceScene(__transition);
}

void LoadingScene::onEnter()
{
	Size __visibile_size = Director::getInstance()->getVisibleSize();
	Point __origin = Director::getInstance()->getVisibleOrigin();
	Sprite* __background = Sprite::create("splash.png");
	__background->setPosition(__origin.x + __visibile_size.width/2,__origin.y + __visibile_size.height/2);
	this->addChild(__background);
	//	async load resources
	Director::getInstance()->getTextureCache()->addImageAsync("atlas.png",CC_CALLBACK_1(LoadingScene::loadingCallBack,this));
}

bool LoadingScene::init()
{
	return Scene::init();
}
