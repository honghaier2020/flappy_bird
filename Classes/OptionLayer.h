#ifndef OptionLayer_h__
#define OptionLayer_h__
#include "cocos2d.h"

class OptionDelegate
{
public:
	virtual void onTouch() = 0;
};

class OptionLayer : public cocos2d::Layer
{
public:
	OptionLayer();

	~OptionLayer();

	bool init();

	CREATE_FUNC(OptionLayer);
};
#endif // OptionLayer_h__
