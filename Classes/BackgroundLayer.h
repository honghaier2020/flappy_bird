#ifndef BackgroundLayer_h__
#define BackgroundLayer_h__
#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();

	bool init();

	CREATE_FUNC(BackgroundLayer);

	static float getLandHeight();
};
#endif // BackgroundLayer_h__
