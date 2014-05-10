#ifndef WelcomeScene_h__
#define WelcomeScene_h__
#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene{
public:
	WelcomeScene();

	~WelcomeScene();

	bool init();

	CREATE_FUNC(WelcomeScene);
};
#endif // WelcomeScene_h__
