#ifndef  _CHOOSENET_H
#define  _CHOOSENET_H
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Server.h"
#include "Client.h"
#include "RoomScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;

/*����ѡ����棬��ʱֻ�о���������*/
class NetMenu :public cocos2d::Layer,public EditBoxDelegate
{
protected:
	std::string _player_name;  // �������

	Button* _nameStartButton;  //ָ��������ָ��
	Button* _pleaseStartButton; //ָ��ȷ�������ָ��

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(NetMenu);

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
};

#endif // ! _CHOOSENET_H
