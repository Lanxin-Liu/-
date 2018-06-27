#include "MapLayer.h"

USING_NS_CC;

bool MyMap::init()
{
	if (!Layer::init())
	{
		return false;
	}

	log("Setting init");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initTiledmap();

	setTouchEnabled(true);

	return true;
}

//��ʼ����ͼ
void MyMap::initTiledmap()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = experimental::TMXTiledMap::create("map/Map1.tmx");
	this->addChild(_tileMap, 0, 1);

	_decoration = _tileMap->getLayer("decoration");
	_decoration->setVisible(true);
}

//ʹλ����Ұ����
void MyMap::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);
	log("Ŀ��λ�� (%f ,%f) ", pointB.x, pointB.y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);
}

//��ͼ���ƣ���Ұ����
void MyMap::rollRight(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.x <= 0 && pos.x >= -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1180)
	{
		pos.x -= 1;
		if (pos.x <= 0 && pos.x >= -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1180)
		{
		    this->setPosition(pos);
		}
	}
}

//��ͼ���ƣ���Ұ����
void MyMap::rollLeft(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.x <= 0 && pos.x >=  -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1180)
	{
		pos.x += 1;
		if (pos.x <= 0 && pos.x >=  -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1180)
		{
			this->setPosition(pos);
		}
	}
}

//��ͼ���ƣ���Ұ����
void MyMap::rollDown(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+885)
	{
		pos.y += 1;
		if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+885)
		{
			this->setPosition(pos);
		}
	}
}

//��ͼ���ƣ���Ұ����
void MyMap::rollUp(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+885)
	{
		pos.y -= 1;
		if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+885)
		{
			this->setPosition(pos);
		}
	}
}