#include "SoldierSprite.h"
int Soldier::n = 0;//测试用
Soldier* Soldier::createSoldier(Point position, sol_type soldier_type)
{
	Soldier* soldier = Soldier::create();
	if (soldier)
	{
		soldier->initSoldier(position, soldier_type);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return NULL;
}

void Soldier::initSoldier(Point position, sol_type soldier_type)
{
	this->isActive = false;
	n++;//测试用
	switch (soldier_type)
	{
	case(american):
	  {
		hp = 50;
		atk = 10; 
		character = Sprite::create("soldier.jpg");
		selected = Sprite::create("selected.jpg");
	  }break;
	case(dog):
	  {
		hp = 20;
		atk = 15;
		character = Sprite::create("dog.png");
		selected = Sprite::create("dog_selected.png");
	  }break;
	}
	

	attackers = std::list<Soldier*>();

	
	character->setScale(1);
    character->setPosition(position);
	character->setPositionY(position.y + 80*n);//测试用
	this->addChild(character);//非选中状态图


	auto characterSize = character->getContentSize();
	selected->setPosition(characterSize.width / 2, characterSize.height / 2);
	selected->setOpacity(0);
	character->addChild(selected);//选中状态图

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//触摸事件监听器

	this->scheduleUpdate();//随时更新状态
	this->schedule(schedule_selector(Soldier::updateattack), 1.0f, kRepeatForever, 0);//执行攻击函数的刷新
}
void Soldier::update(float dt)
{
	if (this->isActive)
	{
		selected->setOpacity(255);
	}
	else
	{
		selected->setOpacity(0);
	}
}//更新选中状态

void Soldier::push_back_attacker(Soldier*attack)
{
	attackers.push_back(attack);
}//添加攻击者
void Soldier::updateattack(float dt)
{
	for (attacker = attackers.begin(); attacker != attackers.end(); attacker++)
	{
		hp -= (*attacker)->atk;
	}
}//执行攻击函数

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 2 &&
		point.x<position.x + character->getContentSize().width / 2 &&
		point.y>position.y - character->getContentSize().height / 2 &&
		point.y < position.y + character->getContentSize().height / 2
		);      //改变活动状态，传递鼠标选中指针


	if (isSelected)
	{                           
		this->isActive = !isActive;
	}
	

	return false;

}








