#pragma once

#include "cocos2d.h";
#include <functional>;

class OutputField : public cocos2d::Node
{
public:
	static OutputField* create(const char* title);

	virtual bool init();

	void setValue(int value);

	CREATE_FUNC(OutputField);
private:
	const char* _title;
	cocos2d::Label* _outputField;

	void constuct();
};
