#ifndef WelcomeLayer_h__
#define WelcomeLayer_h__
#include "cocos2d.h"

class SpriteBird;

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer();

	~WelcomeLayer();

	bool init();
	
	CREATE_FUNC(WelcomeLayer);

private:
	void scrollLand(float __dt);

	void menuStartCallback(Ref* __sender);


private:
	cocos2d::Sprite* land1_;
	cocos2d::Sprite* land2_;

	SpriteBird* bird_;
};

#endif // WelcomeLayer_h__
