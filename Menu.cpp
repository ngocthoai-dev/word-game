#include "Menu.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* menu::createScene()
{
	auto scene = Scene::create();

	auto layer = menu::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in menuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool menu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("./sound/themeSong.mp3", true);

	LayerColor *_bgColor = LayerColor::create(Color4B(200, 200, 200, 255));
	addChild(_bgColor, -10);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto playImg = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(menu::onClickMenuItem, this));
	auto exitImg = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(menu::menuCloseCallback, this));

	auto menuItem = Menu::create(playImg, exitImg, nullptr);
	menuItem->setPosition(visibleSize / 2);
	menuItem->alignItemsVertically();
	addChild(menuItem);

	return true;
}

void menu::onClickMenuItem(cocos2d::Ref *sender) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void menu::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
