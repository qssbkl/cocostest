#pragma once

#include "cocos2d.h";
#include "InputField.h";
#include "OutputField.h"
#include "Button.h";
#include <functional>;

class GameMenu : public cocos2d::Node
{
public:
	static GameMenu* create(std::function<void(int _0, int _1, int _2)> startAction);

	virtual bool init();

	void setScore(int value);

	CREATE_FUNC(GameMenu);
private:
	std::function<void(int _0, int _1, int _2)> _startAction;

	InputField* _widthInputField;
	InputField* _heightInputField;
	InputField* _colorsInputField;
	OutputField* _scoreOutput;

	void construct();
	void onStartButtonPressed(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};
