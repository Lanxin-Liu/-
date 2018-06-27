#ifndef _RoomScene_h_
#define _RoomScene_h_

#include <iostream>
#include "cocos2d.h"
#include"Server.h"
#include"Client.h"
#include"ui/CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;


class RoomScene :public cocos2d::Layer
{
protected:
	Vector<Sprite*>     _exist_player;             //Ŀǰ�������Player
	Sprite*             _room_ptr;                 //���䱳��
	std::string         _owner_player_name;        //����������
	Button*             _start_game_button;        //��ʼ��Ϸ��ť
	std::string         _chatString;               //������Ϣ
	TextField*          _chatWindow;               //���������
public:
	static cocos2d::Scene* createScene(Client* c, int mode, std::string _playerName);

	virtual bool init();

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

	void menuNextCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(RoomScene);
};

#endif/*_RoomScene_h_*/