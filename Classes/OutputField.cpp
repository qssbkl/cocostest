#include "OutputField.h"

USING_NS_CC;

OutputField* OutputField::create(const char* title)
{
	auto outputField = OutputField::create();
	outputField->_title = title;
	outputField->constuct();
	return outputField;
}

bool OutputField::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void OutputField::constuct()
{
	auto label = Label::create(_title, "Arial", 28);
	label->setAnchorPoint(Vec2(0, 0));
	label->setContentSize(Size(128, 32));
	label->setPosition(Vec2(0, 0));
	label->setTextColor(Color4B(0, 0, 0, 255));
	this->addChild(label);

	auto panel = DrawNode::create();
	panel->setAnchorPoint(Vec2(0, 0));
	panel->setContentSize(Size(128, 32));
	panel->setPosition(Vec2(128, 0));
	panel->drawSolidRect(Vec2(0, 0), Vec2(128, 32), Color4F(1, 1, 1, 1));
		_outputField = Label::create("0", "Arial", 26);
		_outputField->setAnchorPoint(Vec2(0, 0));
		_outputField->setContentSize(Size(112, 28));
		_outputField->setPosition(Vec2(8, 2));
		_outputField->setTextColor(Color4B(0, 0, 0, 255));
		panel->addChild(_outputField);
	this->addChild(panel);
}

void OutputField::setValue(int value)
{
	_outputField->setString(std::to_string(value));
}
