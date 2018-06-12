#pragma once
#ifndef __SOLDIERSPRITE_H__
#define __SOLDIERSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
class Soldier : public cocos2d::Sprite
{
public:
	static Soldier* createSoldier(Point position);/*��position��point�Ͳ�����������һ��С��*/
	void initSoldier(Point position);
	CREATE_FUNC(Soldier);

	Sprite* character;
	Sprite* selected;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	bool isSelected;
	bool isActive;

	static int n;//������
	int atk ;
	int range;
	int hp ;
};


#endif