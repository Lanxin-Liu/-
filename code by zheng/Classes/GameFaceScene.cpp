#include "GameFaceScene.h"
#include "SpriteLayer.h"

USING_NS_CC;

Scene* GameFace::createScene()
{
	//�����������һ��������
	GameFace* scene = new GameFace();
	scene->init();
	return scene;
}

bool GameFace::init()
{
	if (!Scene::init())
	{
		return false;
	}

	MyMap *_map = MyMap::create();
	MySprite *_mysprite = MySprite::create();

	addChild(_map, 10);
	addChild(_mysprite, 1);

	//ͨ��ָ�������һ����
	_mysprite->maplayer = _map;

	Player* localPlayer = Player::createPlayer();
	Manager* manager = Manager::createManager(_map,_mysprite);
	manager->push_back(localPlayer);
	auto* menu1 = SoldierMenu::createSoldierMenu(Point(500, 120), Point(200, 100), american,_map);
	auto* menu2 = SoldierMenu::createSoldierMenu(Point(600, 120), Point(200, 100), dog,_map);
	auto* menu3 = SoldierMenu::createSoldierMenu(Point(700, 120), Point(200, 100), tank, _map);
	auto* menu4 = ConstructionMenu::createConstructionMenu(Point(1000, 100), power,_map);
	auto* menu5 = ConstructionMenu::createConstructionMenu(Point(1000, 300), miner,_map);
	auto* menu6 = ConstructionMenu::createConstructionMenu(Point(1000, 500), armycamp, _map);
	auto* menu7 = ConstructionMenu::createConstructionMenu(Point(1000, 700), tankfac, _map);
	auto* menu8 = ConstructionMenu::createConstructionMenu(Point(1000, 900), base, _map);
	addChild(menu1, 10);
	addChild(menu2, 10);
	addChild(menu3, 10);
	addChild(menu4, 10);
	addChild(menu5, 10);
	addChild(menu6, 10);
	addChild(menu7, 10);
	addChild(menu8, 10);
	_map->addChild(localPlayer, 9);
	_map->addChild(manager, 5);//ע�����ȼ����ܱ�

	return true;
}


