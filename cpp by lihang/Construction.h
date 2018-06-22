#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__
#include "cocos2d.h"
#include"SoldierSprite.h"
#include<list>
USING_NS_CC;
enum cons_type
{
	power, miner, base, armycamp, tankfac
};
class Construction :public cocos2d::Sprite
{
public:
	static Construction* createConstruction(Point position, cons_type construction_type);/*��position��point�Ͳ�����������һ��С��*/
	void initConstruction(Point position, cons_type construction_type);
	CREATE_FUNC(Construction);

	void update(float dt);
	void updateattack(float dt);
	std::list<Soldier*> attackers;
	std::list<Soldier*>::iterator attacker;
	void push_back_attacker(Soldier*);

	Sprite* character;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	bool isSelected;

	int cost_money;
	int cost_power;
	int produce_power;
	int hp;
};

#endif

