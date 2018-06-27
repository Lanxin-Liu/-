#pragma once
#ifndef __SOLDIERSPRITE_H__
#define __SOLDIERSPRITE_H__
#include "cocos2d.h"
#include<list>
USING_NS_CC;
enum sol_type
{
	american,dog,tank
};
class Soldier : public cocos2d::Sprite
{
public:
	static Soldier* createSoldier(Point position,sol_type soldier_type,Layer* layer);/*��position��point�Ͳ�����������һ��С��*/
	void initSoldier(Point position, sol_type soldier_type, Layer* layer);
	CREATE_FUNC(Soldier);
	
	void update(float dt);
	void updateattack(float dt);
	std::list<Soldier*> attackers;
	std::list<Soldier*>::iterator attacker;
	void push_back_attacker(Soldier*);

	Sprite* character;
	Sprite* selected;
	Layer* _layer;
	sol_type this_type;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	bool isSelected;
	bool isActive;
	bool _attacking;
	bool isStop;

	//static int n;//������
	int atk ;
	int hp;

	int range;
	int speed;
};


#endif