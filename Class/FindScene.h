#ifndef FindScene_h
#define FindScene_h

#include <iostream>
#include "cocos2d.h"
#include"Server.h"
#include "Client.h"
#include <stdio.h>
#include "ui/CocosGUI.h"



USING_NS_CC;
using namespace ui;

/*�����������棬��ʾ�����б�ѡ�����ĳ������*/

class FindScene : public cocos2d:: Layer
{
private:

	Sprite * _room_list_bg;   //�б���
	std::string _player_name; //�������
	std::vector<Button*>   room_list;  //���淿�����

public:

	/*���������б���*/
	static cocos2d::Scene* createScene(Client* c, std::string name);

	/*��ʼ������*/
	virtual bool init();

	/*���º�������ʱ����*/

	void update(float delta);

	void menuNextCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(FindScene);

};

#endif /*FindScene_h*/
