
#include<iostream>
#include"InputNameScene.h"
#include <stdio.h>
#include"FindScene.h"
#include"OrderCode.h"
#include"cocos2d.h"
#include "RoomScene.h"


USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

/*PlayerData Player;*//*������������Ӧ�ö�����GameScene���������������ã���������������������*/
//std::string myname;


Scene*InputNameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = InputNameScene::create();
	scene->addChild(layer);
	return scene;
}

bool InputNameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite *bg = Sprite::create("background1.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);


	auto Name_Editbox = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("NAMEButtonNormal.png"));
	Name_Editbox->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 2));
	Name_Editbox->setFontColor(Color3B(255, 0, 0));//����������ɫ
	Name_Editbox->setPlaceHolder("Name:");//����Ԥ���ı� 
	Name_Editbox->setMaxLength(30);//������󳤶�
	Name_Editbox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//���������κΣ����ǲ���������
	Name_Editbox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//���������־λ
	Name_Editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//���÷�������
	Name_Editbox->setPlaceholderFontName("Arial");//��������
	this->addChild(Name_Editbox);

	auto create_button = Button::create("ButtonNormal.png");
	auto join_button = Button::create("ButtonNormal.png");
	bg->addChild(create_button);
	bg->addChild(join_button);
	create_button->setTitleText("create room");
	create_button->setTitleFontSize(20);
	join_button->setTitleText("join room");
	join_button->setTitleFontSize(20);
	float widthMargin = visibleSize.width / 2 - bg->getContentSize().width / 2;
	float heightMargin = visibleSize.height / 2 - bg->getContentSize().height / 2;

	create_button->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 3 * 2));

	join_button->setPosition(Vec2(bg->getContentSize().width / 2, bg->getContentSize().height / 3));


	join_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			auto client = Client::create(2);
			client->_with_server = false;
			auto transition = TransitionSlideInL::create(0.5, FindScene::createScene(client, _playerName));

			Director::getInstance()->pushScene(transition);
		}
	});

	create_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto server = LocalServer::create();
			this->addChild(server);
			auto client = Client::create(2);
			this->addChild(client);
			client->_filter_mode = true;
			client->order_type = _playerName;
			client->_with_server = true;

			auto transition = TransitionSlideInL::create(0.5, RoomScene::createScene(client, 2, _playerName));
			Director::getInstance()->pushScene(transition);

		}
	});
	return true;
}


void InputNameScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	_playerName = text;

}
void InputNameScene::editBoxReturn(cocos2d::extension::EditBox *editBox){}



