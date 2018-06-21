#include "SoldierSprite.h"
int Soldier::n = 0;//������
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
	n++;//������
	switch (soldier_type)
	{
	case(american):
	  {
		hp = 50;
		atk = 10; 
		range = 2000;
		character = Sprite::create("soldier.jpg");
		selected = Sprite::create("selected.jpg");
	  }break;
	case(dog):
	  {
		hp = 20;
		atk = 15;
		range = 2000;
		character = Sprite::create("dog.png");
		selected = Sprite::create("dog_selected.png");
	  }break;
	}
	

	attackers = std::list<Soldier*>();

	
	character->setScale(1);
    character->setPosition(position);
	character->setPositionY(position.y + 80*n);//������
	this->addChild(character);//��ѡ��״̬ͼ


	auto characterSize = character->getContentSize();
	selected->setPosition(characterSize.width / 2, characterSize.height / 2);
	selected->setOpacity(0);
	character->addChild(selected);//ѡ��״̬ͼ

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//�����¼�������

	this->scheduleUpdate();//��ʱ����״̬
	this->schedule(schedule_selector(Soldier::updateattack), 1.0f, kRepeatForever, 0);//ִ�й���������ˢ��
}
void Soldier::update(float dt)
{
	std::list<Soldier*>::iterator tem_attacker;
	if (this->isActive)
	{
		selected->setOpacity(255);
	}
	else
	{
		selected->setOpacity(0);
	}//����ѡ��״̬
	for (attacker = attackers.begin(); attacker != attackers.end();)
	{
		if (((*attacker)->character->getPositionX())*((*attacker)->character->getPositionX())+
			((*attacker)->character->getPositionY())*((*attacker)->character->getPositionY())>
			((*attacker)->range)*((*attacker)->range))
		{
			tem_attacker = attacker;
			attacker++;
			(*tem_attacker)->_attacking = false;
			attackers.erase(tem_attacker);
		}
		else
		{
			attacker++;
		}
	}
	//���¹�������Ϣ
}

void Soldier::push_back_attacker(Soldier*attack)
{
	attackers.push_back(attack);
}//��ӹ�����
void Soldier::updateattack(float dt)
{
	for (attacker = attackers.begin(); attacker != attackers.end(); attacker++)
	{
		hp -= (*attacker)->atk;
	}
}//ִ�й�������

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 2 &&
		point.x<position.x + character->getContentSize().width / 2 &&
		point.y>position.y - character->getContentSize().height / 2 &&
		point.y < position.y + character->getContentSize().height / 2
		);      //�ı�״̬���������ѡ��ָ��


	if (isSelected)
	{                           
		this->isActive = !isActive;
	}
	

	return false;

}








