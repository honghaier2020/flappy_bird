#ifndef StatusLayer_h__
#define StatusLayer_h__
#include "cocos2d.h"
#include "GameLayer.h"

class StatusLayer : public cocos2d::Layer, public StatusDelegate
{
public:
	StatusLayer();

	~StatusLayer();

	bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart(void);

	void onGamePlaying(int __score) ;

	void onGameEnd(int __cur_socre, int __best_score);

};
#endif // StatusLayer_h__
