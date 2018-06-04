#pragma once
#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
class Soldier : public cocos2d::Layer
{
public:
	static Soldier* createSoldier(Point position);/*��position��point�Ͳ�����������һ��С��*/
	void initSoldier(Point position);
	Sprite* character;
	EventListenerTouchOneByOne* listener;
	static int n;
	int atk ;
	int range;
	int hp ;
	bool isSlected ;
	CREATE_FUNC(Soldier);
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};
class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position);
	void initSoldierMenu(Point position);/*��position��point�Ͳ�����������һ��������ť*/
	Sprite* soldiermenu;
	EventListenerTouchOneByOne* listener;
	int cost;
	CREATE_FUNC(SoldierMenu);
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
};

#endif