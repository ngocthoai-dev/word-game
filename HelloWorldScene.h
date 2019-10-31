#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void wordInit();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void timeLimit(float time);
	std::string returnWord(char c, int &k);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	std::vector<cocos2d::Sprite*> wordSprite;
	cocos2d::Label *scoreLabel;
	cocos2d::Label *wordLabel;
	cocos2d::Sprite *loading;

	int currWord = 0;
	int score;
	int random;
	std::string str[10000];
};

#endif // __HELLOWORLD_SCENE_H__
