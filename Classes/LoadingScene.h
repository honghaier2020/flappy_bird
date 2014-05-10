#ifndef loading_scene_h__
#define loading_scene_h__
#include "cocos2d.h"

class LoadingScene :public cocos2d::Scene
{
public:
	LoadingScene();

	~LoadingScene();

	bool init();

	void onEnter() override;

	CREATE_FUNC(LoadingScene);

private:
	//	callback function for async load texture
	void loadingCallBack(cocos2d::Texture2D* __texture2d);
};
#endif // loading_scene_h__
