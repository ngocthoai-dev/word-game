#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "Menu.h"
#include <string>

USING_NS_CC;

bool compareLength(std::string str1, std::string str2);

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
	if (!Scene::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./sound/themeSong.mp3", true);

	LayerColor *_bgColor = LayerColor::create(Color4B(200, 200, 200, 255));
	addChild(_bgColor, -10);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//std::ifstream inFile;
	//inFile.open("text.txt");
	//CCLOG("%s", s.c_str());

	std::string s = FileUtils::getInstance()->getStringFromFile("text.txt");
	std::istringstream tempStr(s);
	for (int i = 0; i < 10000; i++) {
		getline(tempStr, str[i], '\n');
		str[i] = str[i].substr(0, str[i].length()-1);
	}
	std::sort(str, str + 10000, compareLength);

	//for (int i = 0; i < 100; i++) {
	//	CCLOG("%d", i);
	//	CCLOG("%s", str[i].c_str());
	//}

	//if (!inFile) {
	//	wordLabel = Label::createWithSystemFont("Cannot open", "Arial", 20);
	//	wordLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.9));
	//	wordLabel->setColor(Color3B::RED);
	//	addChild(wordLabel);
	//}

	//if (inFile.is_open()) {
	//	for (int i = 0; getline(inFile, str[i]) && i < 10000; i++);
	//	inFile.close();
	//}


	srand(time(NULL));
	random = rand() % sizeof(str) / sizeof(str[0]);

	wordLabel = Label::createWithSystemFont(str[random].c_str(), "Arial", 20);
	wordLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.9));
	wordLabel->setColor(Color3B::RED);
	addChild(wordLabel);

	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithSystemFont(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height*0.1);
	scoreLabel->setPosition(Vec2(visibleSize.width*0.95, visibleSize.height*0.95));
	scoreLabel->setColor(Color3B::RED);
	addChild(scoreLabel);

	loading = cocos2d::Sprite::create("loadingTornado.png");
	addChild(loading);

	HelloWorld::wordInit();

	return true;
}

void HelloWorld::wordInit() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("./word/word_sheet.plist");

	//CCLOG("___________");
	int t;
	for (int i = 0; i < str[random].length(); i++) {
		//CCLOG("%s_____%d____%c__", str[random].c_str(), i, str[random].at(i));
		wordSprite.push_back(Sprite::createWithSpriteFrameName(returnWord(str[random].at(i), t)));
		if (str[random].at(i) == 'p' || str[random].at(i) == 'q' || str[random].at(i) == 'g' || str[random].at(i) == 'j' || str[random].at(i) == 'y' && i != 0) {
			wordSprite[i]->setAnchorPoint(Vec2(0.5, 0.5));
		}
		else {
			wordSprite[i]->setAnchorPoint(Vec2(0.5, 0));
		}
		wordSprite[i]->setPosition(Vec2(visibleSize.width / 2 - str[random].length() * 20 + i * 40 + 10, visibleSize.height / 2));
		wordSprite[i]->setScale(visibleSize.width / wordSprite[i]->getContentSize().width / 20, 0.5);
		addChild(wordSprite[i]);
	}
	loading->setPosition(Vec2(wordSprite[0]->getPositionX(), visibleSize.height*0.36));

	if (score < 10) {
		HelloWorld::timeLimit((float)(str[random].length()));
	}
	else if (score < 20) {
		HelloWorld::timeLimit((float)(str[random].length() / 1.5f));
	}
	else if (score < 40) {
		HelloWorld::timeLimit((float)(str[random].length() / 2));
	}
	else if (score < 50) {
		HelloWorld::timeLimit((float)(str[random].length() / 3));
	}
	else {
		HelloWorld::timeLimit((float)(str[random].length() / 4));
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string HelloWorld::returnWord(char c, int &k) {
	std::string fileSource;
	switch (c)
	{
	case 'a':
		fileSource = "word_sheet_1.png";
		k = 124;
		break;
	case 'b':
		fileSource = "word_sheet_2.png";
		k = 125;
		break;
	case 'c':
		fileSource = "word_sheet_3.png";
		k = 126;
		break;
	case 'd':
		fileSource = "word_sheet_4.png";
		k = 127;
		break;
	case 'e':
		fileSource = "word_sheet_5.png";
		k = 128;
		break;
	case 'f':
		fileSource = "word_sheet_6.png";
		k = 129;
		break;
	case 'g':
		fileSource = "word_sheet_7.png";
		k = 130;
		break;
	case 'h':
		fileSource = "word_sheet_8.png";
		k = 131;
		break;
	case 'i':
		fileSource = "word_sheet_9.png";
		k = 132;
		break;
	case 'j':
		fileSource = "word_sheet_10.png";
		k = 133;
		break;
	case 'k':
		fileSource = "word_sheet_11.png";
		k = 134;
		break;
	case 'l':
		fileSource = "word_sheet_12.png";
		k = 135;
		break;
	case 'm':
		fileSource = "word_sheet_13.png";
		k = 136;
		break;
	case 'n':
		fileSource = "word_sheet_14.png";
		k = 137;
		break;
	case 'o':
		fileSource = "word_sheet_15.png";
		k = 138;
		break;
	case 'p':
		fileSource = "word_sheet_16.png";
		k = 139;
		break;
	case 'q':
		fileSource = "word_sheet_17.png";
		k = 140;
		break;
	case 'r':
		fileSource = "word_sheet_18.png";
		k = 141;
		break;
	case 's':
		fileSource = "word_sheet_19.png";
		k = 142;
		break;
	case 't':
		fileSource = "word_sheet_20.png";
		k = 143;
		break;
	case 'u':
		fileSource = "word_sheet_21.png";
		k = 144;
		break;
	case 'v':
		fileSource = "word_sheet_22.png";
		k = 145;
		break;
	case 'w':
		fileSource = "word_sheet_23.png";
		k = 146;
		break;
	case 'x':
		fileSource = "word_sheet_24.png";
		k = 147;
		break;
	case 'y':
		fileSource = "word_sheet_25.png";
		k = 148;
		break;
	case 'z':
		fileSource = "word_sheet_26.png";
		k = 149;
		break;
	default:
		break;
	}
	return fileSource;
}

// Implementation of the keyboard event callback function prototype
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	//CCLOG("%i_____%i______%s", keyCode, currWord, str[random].c_str());
	if ((int)keyCode <= 149 && (int)keyCode >= 124 && currWord < str[random].length()) {
		int key;
		returnWord(str[random].at(currWord), key);
		if (key == (int)keyCode) {
			auto fadeOut = FadeOut::create(0.1f);
			wordSprite[currWord]->runAction(fadeOut);
			currWord++;
			//CCLOG("%i______%i_____%i_____%i____%i", keyCode, str[random].length(), currWord, random, key);
			if (currWord >= str[random].length()) {
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/hit.mp3");
				this->unschedule("timeLimit");
				for (int i = 0; i < currWord; i++) {
					wordSprite[i]->removeFromParent();
				}
				wordSprite.clear();

				score++;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				currWord = 0;

				srand(time(NULL));
				random = rand() % 10000;
				wordLabel->setString(str[random].c_str());

				HelloWorld::wordInit();
			}
		}
	}
}

void HelloWorld::timeLimit(float time) {
	float begin = (float)loading->getPositionX();
	float end = (float)wordSprite[(str[random].length() - 1)]->getPositionX();
	this->schedule([=](float) {
		loading->setPosition(Vec2(loading->getPositionX() + (float)(end - begin) / 100, loading->getPositionY()));
		//CCLOG("%f_____%f______%f___________%f", end, loading->getPositionX(), time, wordSprite[(str[random].length() - 1)]->getPositionX());
		if ((float)loading->getPositionX() >= end) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./sound/death.wav");
			auto scene = GameOver::createScene(score);
			Director::getInstance()->replaceScene(scene);
		}
	}, (float)(time / 100), "timeLimit");
}

bool compareLength(std::string str1, std::string str2) {
	return (str1.length() < str2.length());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
