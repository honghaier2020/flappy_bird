#ifndef GameScene_h__
#define GameScene_h__
#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene();

	~GameScene();

	bool init();

	void restart();

	CREATE_FUNC(GameScene);
};
#endif // GameScene_h__
