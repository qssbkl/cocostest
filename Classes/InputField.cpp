#include "InputField.h"

USING_NS_CC;

InputField* InputField::create(const char* title,
	const char* placeholder,
	int minValue,
	int maxValue,
	int defaultValue)
{
	auto inputField = InputField::create();
	inputField->_title = title;
	inputField->_placeholder = placeholder;
	inputField->_minValue = minValue;
	inputField->_maxValue = maxValue;
	inputField->_defaultValue = defaultValue;
	inputField->_currentValue = defaultValue;
	inputField->constuct();
	return inputField;
}

bool InputField::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void InputField::constuct()
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
		auto inputField = ui::TextField::create(_placeholder, "Arial", 26);
		inputField->setAnchorPoint(Vec2(0, 0));
		inputField->setContentSize(Size(112, 28));
		inputField->setPosition(Vec2(8, 2));
		inputField->setTextColor(Color4B(100, 100, 100, 255));
		inputField->setMaxLength(8);
		inputField->setMaxLengthEnabled(true);
		inputField->setTouchAreaEnabled(true);
		inputField->setTouchSize(Size(112, 28));
		inputField->setText(std::to_string(_defaultValue));
		inputField->addEventListener(CC_CALLBACK_2(InputField::inputEvent, this));
		panel->addChild(inputField);
	this->addChild(panel);
}

void InputField::inputEvent(Ref* pSender, ui::TextField::EventType type)
{
	auto textField = static_cast<ui::TextField*>(pSender);
	switch (type)
	{
	case ui::TextField::EventType::ATTACH_WITH_IME:
		textField->setTextColor(Color4B(0, 0, 0, 255));
		break;
	case ui::TextField::EventType::DETACH_WITH_IME:
		textField->setTextColor(Color4B(100, 100, 100, 255));
		textField->setText(std::to_string(_currentValue));
		break;
	case ui::TextField::EventType::INSERT_TEXT: 
	{
		auto input = static_cast<int>(std::strtol(textField->getString().c_str(), nullptr, 10));
		if (input < _minValue)
			input = _minValue;
		if (input > _maxValue)
			input = _maxValue;
		_currentValue = input;
		break;
	}
	case ui::TextField::EventType::DELETE_BACKWARD:
	{
		auto input = static_cast<int>(std::strtol(textField->getString().c_str(), nullptr, 10));
		if (input < _minValue)
			input = _minValue;
		if (input > _maxValue)
			input = _maxValue;
		_currentValue = input;
		break;
	}
	}
}
