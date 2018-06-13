#include "LoadingScene.h"
#include "SettingScene.h"
#include "GameFaceScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Loading::createScene()
{
    return Loading::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoadingScene.cpp\n");
}

bool Loading::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	log("Loading init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("background1.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	//start sprite
	Sprite *startSpriteNormal = Sprite::create("startnormal.png");
	Sprite *startSpriteSelected = Sprite::create("startdown.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(Loading::menuItemStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 450)));

	// set image menu
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"settingsnormal.png",
		"settingsdown.png",
		CC_CALLBACK_1(Loading::menuItemSettingCallback, this));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 571)));

	// help image menu
	//MenuItemImage *helpMenuItem = MenuItemImage::create(
	//	"help-up.png",
	//	"help-down.png",
	//	CC_CALLBACK_1(Loading::menuItemHelpCallback, this));
	//helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(860, 480)));

    // create menu, it's an autorelease object
    auto menu = Menu::create(startMenuItem, settingMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void Loading::menuItemSettingCallback(Ref* pSender)
{
	auto sc = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void Loading::menuItemHelpCallback(Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Help %p", item);
}

void Loading::menuItemStartCallback(Ref* pSender)
{
	auto sc = GameFace::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
	/*Director::getInstance()->pushScene(sc);*/
}
