#pragma once

#include "cocos2d.h";
#include "ui/CocosGUI.h";
#include <functional>;

class InputField : public cocos2d::Node
{
public:
	static InputField* create(const char* title,
		const char* placeholder,
		int minValue,
		int maxValue,
		int defaultValue);

	virtual bool init();

	int getValue() { return _currentValue; };

	CREATE_FUNC(InputField);
private:
	const char* _title;
	const char* _placeholder;
	int _minValue;
	int _maxValue;
	int _defaultValue;
	int _currentValue;

	void constuct();
	void inputEvent(Ref* pSender, cocos2d::ui::TextField::EventType type);
};
