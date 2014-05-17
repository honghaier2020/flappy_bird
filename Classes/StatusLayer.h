#ifndef StatusLayer_h__
#define StatusLayer_h__
#include "cocos2d.h"
#include "GameLayer.h"
#include <string>

const std::string NUMBER_SCORE = "number_score";
const std::string NUMBER_FONT = "font";
const int CURRENT_SCORE_SPRITE_TAG = 10001;
const int WRITE_SPRITE_TAG = 10000;

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

	void showReadyStatus();

	void loadWhiteSprite();

	void showStartStatus();

	void showOverStatus(int __cur_socre, int __best_score);

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	std::string getMedalsName(int __score);

	void setBlinkSprite();

	void fadeInRestartBtn();

	void blinkAction();

	void refreshScoreCallback();

	void refreshScoreExecutor(float __dt);

	void menuRestartCallback(cocos2d::Ref* __sender);

private:
	int		best_scores_;
	int		current_scores_;
	int		tmp_scores_;
	bool	new_record_;
	cocos2d::Size	visible_size_;
	cocos2d::Point	origin_point_;
	cocos2d::Sprite* score_sprite_;
	cocos2d::Sprite* getready_sprite_;
	cocos2d::Sprite* tutorial_sprite_;
	cocos2d::Sprite* white_sprite_;
	cocos2d::Sprite* blink_sprite_;

};
#endif // StatusLayer_h__
