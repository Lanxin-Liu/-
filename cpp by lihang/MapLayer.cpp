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

	initSprite();

	setTouchEnabled(true);

	return true;
}

//��ʼ����ͼ������
void MyMap::initTiledmap()
{
	_tileMap = experimental::TMXTiledMap::create("map/Map1.tmx");
	this->addChild(_tileMap, 0, 1);

	_decoration = _tileMap->getLayer("decoration");
	_decoration->setVisible(true);
}

void MyMap::initSprite()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	addChild(_player, 2, 200);
}

bool MyMap::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return false;
}

//drag the map
void MyMap::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto diff = touches[0]->getDelta();
	auto node = getChildByTag(200);
	auto currentPos = node->getPosition();
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	node->setPosition(currentPos - diff);
	this->setViewpointCenter(_player->getPosition());
}

void MyMap::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	return;
}

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

//��ui����ת��Ϊ��Ƭ����
//Vec2 MyMap::tileCoordFromPosition(Vec2 pos)
//{
//	int x = pos.x / _tileMap->getTileSize().width;
//	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
//	return Vec2(x, y);
//}
