#ifndef GameLayer_h__
#define GameLayer_h__
#include "cocos2d.h"
#include "OptionLayer.h"
#include <vector>

class SpriteBird;
class cocos2d::Sprite;


const int UP_PIP = 21;

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/**
 * The radius of the bird
 */
const int BIRD_RADIUS = 15;

/**
 * The number of pip pairs display in the screen in the same time
 */
const int PIP_COUNT = 2;

/**
 * The height of the pips
 */
const int PIP_HEIGHT = 320;

/**
 * The width of the pips
 */
const int PIP_WIDTH = 52;

/**
 * The distance between the down pip and up pip
 */
const int PIP_DISTANCE = 100;

/**
 * The distance between the pips vertical
 */
const int PIP_INTERVAL = 180;

/**
 * The distance that the pip will display in the screen, for player to ready
 */
const int WAIT_DISTANCE = 100;


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

/**
* Define the game status
* GAME_STATUS_READY game is not start, just ready for payer to start.
* GAME_STATUS_START the game is started, and payer is paying this game.
* GAME_STATUS_OVER the player is lose this game, the game is over.
*/
typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

class GameLayer : public cocos2d::Layer, public OptionDelegate
{
public:
	GameLayer();

	~GameLayer();

	bool init();

	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	void onTouch();

	void setPhyWorld(cocos2d::PhysicsWorld* __world) {this->physics_world_ = __world; }

	void scrollLand(float __dt);

	bool onContactBegin( cocos2d::PhysicsContact& __contact);

	void createPipes();

	int getRandomHeight();
	
	void update(float __delta);

	void rotateBird();

	void checkHit();

	void gameOver();

	void birdSpriteFadeOut();

	void birdSpriteRemove();

private:
	SpriteBird* bird_;

	GameStatus	game_status_;

	int			scores_;

	int			best_scores_;

	Node*		ground_node_;

	cocos2d::Sprite*		land1_;
	cocos2d::Sprite*		land2_;
	cocos2d::SEL_SCHEDULE	shift_Land_;

	cocos2d::PhysicsWorld*	physics_world_;

	std::vector<Node*> pipes_;

};
#endif // GameLayer_h__
