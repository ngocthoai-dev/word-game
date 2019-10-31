#ifndef __MENU_H__
#define __MENU_H__

#include "cocos2d.h"

class menu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void onClickMenuItem(cocos2d::Ref *sender);
	void menuCloseCallback(Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(menu);
};

#endif // __HELLOWORLD_SCENE_H__
