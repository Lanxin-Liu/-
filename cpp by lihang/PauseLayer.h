#pragma once
#ifndef __Gamepause__H__  
#define __Gamepause__H__ 

#include "cocos2d.h" 

USING_NS_CC;

class GamePause : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr);

	//������Ϸ  
	void menuContinueCallback(Object* pSender);

	CREATE_FUNC(GamePause);
};

#endif 