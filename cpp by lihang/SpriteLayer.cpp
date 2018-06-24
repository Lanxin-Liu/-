#include "SpriteLayer.h"
#include "PauseLayer.h"

USING_NS_CC;

bool MySprite::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initSpritebg();

	this->schedule(schedule_selector(MySprite::updateTime),1.0f, kRepeatForever,0);
	this->schedule(schedule_selector(MySprite::updateMoney), 1.0f, kRepeatForever, 0);
	updatePower();
	
	//��ͣ��ť
	auto pauseItem = MenuItemImage::create(
		"menu/pause.png",
		"menu/pauserelease.png",
		CC_CALLBACK_1(MySprite::menuPauseCallback, this));

	pauseItem->setPosition(Vec2(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
		origin.y + visibleSize.height - pauseItem->getContentSize().height / 2));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	maplayer = MyMap::create();

	//����������
	auto listener = EventListenerMouse::create();

	//�ַ�MouseMove�¼�
	listener->onMouseMove = CC_CALLBACK_1(MySprite::mousemove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _money);

	//������˵�
	Player* localPlayer = Player::createPlayer();
	Manager* manager = Manager::createManager();
	manager->push_back(localPlayer);
	auto* menu1 = SoldierMenu::createSoldierMenu(Point(500, 120), Point(200, 100), american);
	auto* menu4 = SoldierMenu::createSoldierMenu(Point(700, 120), Point(200, 100), dog);
	auto* menu2 = ConstructionMenu::createConstructionMenu(Point(100, 120), power);
	auto* menu3 = ConstructionMenu::createConstructionMenu(Point(300, 120), miner);
	addChild(menu1, 10);
	addChild(menu2, 10);
	addChild(menu3, 10);
	addChild(menu4, 10);
	addChild(localPlayer, 9);
	addChild(manager, 5);//ע�����ȼ����ܱ�

	return true;
}

//�����ͣ��Ұ�ƶ�
void MySprite::mousemove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	float x = e->getCursorX();
	float y = e->getCursorY();

	//��
	if (x >= 0 && x <= 25)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollLeft), 1.0f / 600, kRepeatForever, 0);
	}
	else if (x > 25 && x <= 50)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollLeft), 1.0f / 300, kRepeatForever, 0);
	}
	else
	{
		this->maplayer->unschedule(schedule_selector(MyMap::rollLeft));
	}

	//��
	if (x >= 1255 && x <= 1280)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollRight), 1.0f / 600, kRepeatForever, 0);
	}
	else if (x >= 1230 && x < 1255)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollRight), 1.0f / 300, kRepeatForever, 0);
	}
	else
	{
		this->maplayer->unschedule(schedule_selector(MyMap::rollRight));
	}

	//��
    if (y >= 0 && y <= 20)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollDown), 1.0f / 600, kRepeatForever, 0);
	}
	else if (y > 20 && y <= 40)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollDown), 1.0f / 300, kRepeatForever, 0);
	}
	else
	{
		this->maplayer->unschedule(schedule_selector(MyMap::rollDown));
	}

	//��
	if (y >= 940 && y <= 960)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollUp), 1.0f / 600, kRepeatForever, 0);
	}
	else if (y >= 920 && y < 940)
	{
		this->maplayer->schedule(schedule_selector(MyMap::rollUp), 1.0f / 300, kRepeatForever, 0);
	}
	else
	{
		this->maplayer->unschedule(schedule_selector(MyMap::rollUp));
	}
}

//��ͣ����
void MySprite::menuPauseCallback(cocos2d::Ref* pSender)
{
	//�õ����ڵĴ�С  
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	//������ǰ��������ӽڵ���Ϣ������renderTexture�С�  
	//�������ƽ�ͼ��  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����  
	Director::sharedDirector()->pushScene(GamePause::scene(renderTexture));
}

//��ʼ����Ǯ��������ʱ�䱳��
void MySprite::initSpritebg()
{
	_money = Sprite::create("money.png");
	_money->setPosition(Vec2(1106, 937));
	addChild(_money);
	_power = Sprite::create("power.png");
	_power->setPosition(Vec2(911, 932));
	addChild(_power);
	_time = Sprite::create("time.png");
	_time->setPosition(Vec2(100, 932));
	addChild(_time);
}

//��ʱ����½�Ǯ
void MySprite::updateMoney(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	money += 15;
	Node *n = this->getChildByTag(GameMoney);
	if (n)
	{
		this->removeChildByTag(GameMoney);
	}
	__String *money=__String::createWithFormat("%d", this->money);
	auto moneylable = Label::createWithTTF(money->getCString(),
		"fonts/Marker Felt.ttf", 18);
	moneylable->setPosition(Vec2(1126, 932));
	this->addChild(moneylable, 5, GameMoney);
}

//���µ���
void MySprite::updatePower()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node *n = this->getChildByTag(GamePower);
	if (n)
	{
		this->removeChildByTag(GamePower);
	}
	__String *power1 = __String::createWithFormat("%d / %d", this->usedpower, this->power1);
	auto powerlable = Label::createWithTTF(power1->getCString(),
		"fonts/Marker Felt.ttf", 18);
	powerlable->setPosition(Vec2(926, 932));
	this->addChild(powerlable, 5, GamePower);
}

//��ʱ
void MySprite::updateTime(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	nSecond++;
	if (nSecond == 60) {
		nSecond = 0;
		nMinute++;
		if (nMinute == 60) {
			nMinute = 0;
			nHour++;
			if (nHour == 24) {
				nHour = 0;
			}
		}
	}
	Node *n = this->getChildByTag(GameTime);
	if (n)
	{
		this->removeChildByTag(GameTime);
	}
	__String *time = __String::createWithFormat("%d/ %d/ %d", this->nHour, this->nMinute, this->nSecond);
	auto timelable = Label::createWithTTF(time->getCString(),
		"fonts/Marker Felt.ttf", 18);
	timelable->setPosition(Vec2(100, 932));
	this->addChild(timelable, 5, GameTime);
}
