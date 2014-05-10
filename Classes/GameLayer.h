#ifndef GameLayer_h__
#define GameLayer_h__
#include "cocos2d.h"
#include "OptionLayer.h"

class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart(void) = 0;

	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying(int __score) = 0;

	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd(int __cur_socre, int __best_score) = 0;
};

class GameLayer : public cocos2d::Layer, public OptionDelegate
{
public:
	GameLayer();

	~GameLayer();

	bool init();

	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	void onTouch();

	void setPhyWorld(cocos2d::PhysicsWorld* __world);
};
#endif // GameLayer_h__
