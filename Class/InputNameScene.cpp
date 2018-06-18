#include<cocos2d.h>
#include<iostream>
#include"InputNameScene.h"
#include"PlayerData.h"

USING_NS_CC;

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

	auto Name_Editbox = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("ButtonNormal.png"));
	Name_Editbox->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 2));
	Name_Editbox->setFontColor(Color3B(255, 0, 0));//����������ɫ
	Name_Editbox->setPlaceHolder("Name:");//����Ԥ���ı� 
	Name_Editbox->setMaxLength(30);//������󳤶�
	Name_Editbox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//���������κΣ����ǲ���������
	Name_Editbox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//���������־λ
	Name_Editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//���÷�������
	Name_Editbox->setPlaceholderFontName("Arial");//��������
	this->addChild(Name_Editbox);

	return true;
}


void InputNameScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	/*myname = text;*/
}
void InputNameScene::editBoxReturn(cocos2d::extension::EditBox *editBox){}

