#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include<list>
#include"SoldierSprite.h"
#include"Construction.h"
USING_NS_CC;
class Player :public  cocos2d::Node
{
public:
	static Player* createPlayer();
	void initPlayer();
	void update(float dt);//��ʼ��

	static std::list<Soldier*> playerSoldier;/*����һ��list���洢���е�С������player�б���С����λ��ȷ�������������*/
	std::list<Soldier*>::iterator iter;

	static std::list<Construction*> playerConstruction;/*����һ��list���洢���е�С������player�б���С����λ��ȷ�������������*/
	std::list<Construction*>::iterator iter2;

	static int money;
	static int power_max;
	static int power_cost;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	bool no_soldier_Selected;
	bool no_construction_Selected;
	bool non_object_Selected;

	Soldier*getSelectedSoldier();//��ȡ��ѡ��С��
	Construction* getSelectedConstruction();//��ȡ��ѡ�н���

	CREATE_FUNC(Player);
};

class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer);/*��position��point�Ͳ�����������һ��������ť,����λ��ΪSoldierPosition*/
	void initSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer);
	CREATE_FUNC(SoldierMenu);

	void update(float dt);

	Point soldier_Position;
	sol_type soldier_Type;
	void create_Soldier();

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition, sol_type soldier_type);

	Sprite* soldier_menu;

	Layer* _layer;

	int cost;
	int cd_time;
	int waiting_soldier;


};

class ConstructionMenu : public cocos2d::Layer
{
public:
	static  ConstructionMenu* createConstructionMenu(Point position, cons_type construct_type);/*��position��point�Ͳ�����������һ��������ť,��ʽΪ�϶�*/
	void initConstructionMenu(Point position, cons_type construct_type);
	void update(float dt);

	Sprite* construction_menu;
	Sprite* construction;

	int _power_cost;
	int cd_time;

	bool create_begin;
	CREATE_FUNC(ConstructionMenu);

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchMoved(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchEnded(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
};
#endif

