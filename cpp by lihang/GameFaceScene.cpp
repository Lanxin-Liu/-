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
	
	//ͨ��ָ�������һ����
	/*_map->spritelayer = _mysprite;*/

	addChild(_map, 0);
	addChild(_mysprite, 1);
	return true;
}


