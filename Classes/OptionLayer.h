#ifndef OptionLayer_h__
#define OptionLayer_h__
#include "cocos2d.h"
#include <vector>

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

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& __touches, cocos2d::Event* __events);

	CREATE_FUNC(OptionLayer);

	CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};
#endif // OptionLayer_h__
