#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include<list>
#include"SoldierSprite.h"
USING_NS_CC;
class Player :public  cocos2d::Node
{
public:
	static Player* createPlayer();
	void initPlayer();

	static std::list<Soldier*> playerSoldier;/*����һ��list���洢���е�С������player�б���С����λ��ȷ�������������*/
	std::list<Soldier*>::iterator iter;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	bool nonSelected;
	CREATE_FUNC(Player);
};

class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position, Point SoldierPosition);/*��position��point�Ͳ�����������һ��������ť,����λ��ΪSoldierPosition*/
	void initSoldierMenu(Point position, Point SoldierPosition);
	Sprite* soldiermenu;
	EventListenerTouchOneByOne* listener;
	int cost;
	CREATE_FUNC(SoldierMenu);
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition);
};
#endif

