#include "Manager.h"
bool Manager::attack_mode = false;
Manager* Manager::createManager()
{
	Manager* manager = Manager::create();
	if (manager)
	{
		manager->initManager();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

void Manager::initManager()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Manager::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//�����������¼�

	key_listener = EventListenerKeyboard::create();
	key_listener->onKeyReleased = CC_CALLBACK_2(Manager::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);
}

bool Manager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	auto point = pTouch->getLocation();
	non_player_Selected = true;

	for (player = players.begin(); player != players.end(); player++)
	{
		if (!(*player)->non_object_Selected)
		{
			non_player_Selected = false;//���������ʱ���������˺���д������
		}
	}//����ȷ���Ƿ�����ҵĽ��������ֱ�ѡ�У����Ƿ���е��ǿյأ�


	if (non_player_Selected)
	{
		for (soldier = (players[0]->playerSoldier).begin(); soldier!=(players[0]->playerSoldier).end(); soldier++)
		{
			if ((*soldier)->isActive)
			{
				MoveTo* moveto = MoveTo::create(1.0f, point);
				(*soldier)->character->runAction(moveto);
			}
		}
	}
	else if (attack_mode)
	{
		for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		{
			if ((*soldier)->isActive&&!players[0]->no_soldier_Selected)
			{
				attack((*soldier), players[0]->getSelectedSoldier());
			}
			else if ((*soldier)->isActive && !players[0]->no_construction_Selected)
			{
				attack((*soldier), players[0]->getSelectedConstruction());
			}
		}
		attack_mode = false;
	}
	return false;
}

bool Manager::onKeyReleased(EventKeyboard::KeyCode keycode, Event* pEvent)
{
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	   {
		   for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		   {
				(*soldier)->isActive=true;
		   }
	   }  break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	  {
		  for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		  {
			  (*soldier)->isActive = false;
		  }
	  }    break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	  {
		  attack_mode = true;
	  }  break;
	}
	return false;
}



void Manager::attack(Soldier* attacker, Soldier* defender)
{
	defender->push_back_attacker(attacker);
}
void Manager::attack(Soldier* attacker, Construction* defender)
{
	defender->push_back_attacker(attacker);
}

void Manager::push_back(Player *player)
{
	players.push_back(player);
}//�����������Ҷ���