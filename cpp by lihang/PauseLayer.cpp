#include "PauseLayer.h"

USING_NS_CC;
  
//��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı���   

Scene* GamePause::scene(RenderTexture* sqr)
{

	Scene *scene = Scene::create();
	GamePause *layer = GamePause::create();
	scene->addChild(layer, 1);

	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite  
	//����Sprite��ӵ�GamePause��������  
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());

	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�  
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ  
	back_spr->setColor(Color3B(127.5, 127.5, 127.5)); //ͼƬ��ɫ���ɫ   

	scene->addChild(back_spr,0);
	return scene;
}

bool GamePause::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::sharedDirector()->getVisibleSize(); 
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	//������Ϸ��ť  
	MenuItemImage *pContinueItem = MenuItemImage::create(
		"menu/backnormal.png",
		"menu/backdown.png",
		this,
		menu_selector(GamePause::menuContinueCallback));

	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));

	Menu* pMenu = Menu::create(pContinueItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 3);

	return true;
}

void GamePause::menuContinueCallback(Object* pSender)
{
    Director::sharedDirector()->popScene();
}