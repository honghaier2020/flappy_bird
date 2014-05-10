#ifndef SpriteBird_h__
#define SpriteBird_h__
#include "cocos2d.h"
#include <string>

static const int BIRD_SPRITE_TAG = 10003;

typedef enum
{
	ACTION_STATE_IDLE,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
}ActionState;
class SpriteBird : public cocos2d::Sprite{
public:
	SpriteBird();

	~SpriteBird();

	bool virtual init();

	static SpriteBird* getInstance();

	bool createBird();

	bool changeState(ActionState __state);

	void idle();

	void fly();

	void die();

protected:
	cocos2d::Animation* createAnimation(const char* __fmt, int __count, float __fps);

	void createBirdByRandom();

private:
	static SpriteBird* inst_;

	unsigned int is_first_time_;

	std::string bird_name_;
	std::string bird_name_format_;

	cocos2d::Action* idle_action_;

	cocos2d::Action* swing_action_;

	ActionState currentStatus_;
};

#endif // SpriteBird_h__
