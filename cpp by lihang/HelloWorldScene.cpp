#include "HelloWorldScene.h"
#include "SettingScene.h"
#include "GameFaceScene.h"
#include "CinNameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	log("HelloWorld init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("background.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);
	addMenuItem();

    return true;
}

void HelloWorld::addMenuItem()
{
	//start sprite
	Sprite *startSpriteNormal = Sprite::create("menu/startnormal.png");
	Sprite *startSpriteSelected = Sprite::create("menu/startdown.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 500)));

	// set image menu
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"menu/settingsnormal.png",
		"menu/settingsdown.png",
		CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 621)));

	// help image menu
	//MenuItemImage *helpMenuItem = MenuItemImage::create(
	//	"help-up.png",
	//	"help-down.png",
	//	CC_CALLBACK_1(HelloWorld::menuItemHelpCallback, this));
	//helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(860, 480)));

	// create menu, it's an autorelease object
	auto menu = Menu::create(startMenuItem, settingMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
	auto sc = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::menuItemHelpCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Help %p", item);
}

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
	auto sc = CinName::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
	/*Director::getInstance()->pushScene(sc);*/
}
