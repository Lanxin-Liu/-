#include "SoldierSprite.h"
int Soldier::n = 0;//������
Soldier* Soldier::createSoldier(Point position)
{
	Soldier* soldier = Soldier::create();
	if (soldier)
	{
		soldier->initSoldier(position);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return NULL;
}

void Soldier::initSoldier(Point position)
{
	this->isActive = false;
	n++;//������

	hp = 50;
	atk = 10;

	character = Sprite::create("soldier.jpg");
	character->setScale(0.5);
    character->setPosition(position);
	character->setPositionY(position.y + 80*n);//������
	this->addChild(character);//��ѡ��״̬ͼ

	selected = Sprite::create("selected.jpg");
	auto characterSize = character->getContentSize();
	selected->setPosition(characterSize.width / 2, characterSize.height / 2);
	selected->setOpacity(0);
	character->addChild(selected);//ѡ��״̬ͼ

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//�����¼�������
}

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 4 &&
		point.x<position.x + character->getContentSize().width / 4 &&
		point.y>position.y - character->getContentSize().height / 4 &&
		point.y < position.y + character->getContentSize().height / 4
		);      //�ı�״̬���������ѡ��ָ��



	if (
		isSelected
		)
	{                           
		
		this->isActive = !isActive;
		if (this->isActive)
		{
			selected->setOpacity(255);
		}
		else
		{
			selected->setOpacity(0);
		}
	}
	
	return false;

}








