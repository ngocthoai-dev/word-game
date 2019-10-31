#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

int finalScore;
Scene* GameOver::createScene(int score)
{
	finalScore = score;
	auto scene = Scene::create();

	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	__String *tempScore = __String::createWithFormat("Your Score : %i", finalScore);
	auto label = Label::createWithTTF(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
	label->setColor(Color3B::RED);
	addChild(label);

	auto playImg = MenuItemImage::create("Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1(GameOver::onClickMenuItem, this));
	auto exitImg = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameOver::menuCloseCallback, this));

	auto menuItem = Menu::create(playImg, exitImg, nullptr);
	menuItem->setPosition(visibleSize / 2);
	menuItem->alignItemsVertically();
	addChild(menuItem);

	return true;
}

void GameOver::onClickMenuItem(cocos2d::Ref *sender) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}
