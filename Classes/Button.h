#pragma once

#include "cocos2d.h";
#include "ui/CocosGUI.h";

class Button : public cocos2d::Node
{
public:
	static Button* create(const char* title);

	virtual bool init();

	cocos2d::ui::Widget* getWidget() { return _widget; };

	CREATE_FUNC(Button);
private:
	const char* _title;

	cocos2d::ui::Widget* _widget;

	void construct();
};
