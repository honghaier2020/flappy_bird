#include "AppDelegate.h"
#include "LoadingScene.h"
#include <vector>
#include <string>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("flappy bird");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(288,512, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(288,512);


	this->setResourceSearchResolution();
	
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();

	auto scene = LoadingScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

}

void AppDelegate::setResourceSearchResolution()
{
	std::vector<std::string> __search_path;
	__search_path.push_back("fonts");
	__search_path.push_back("image");
	__search_path.push_back("sounds");
	FileUtils::getInstance()->setSearchResolutionsOrder(__search_path);
}
