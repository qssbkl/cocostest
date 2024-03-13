#include "Button.h"

USING_NS_CC;

Button* Button::create(const char* title)
{
	auto button = Button::create();
	button->_title = title;
	button->construct();
	return button;
}

bool Button::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Button::construct()
{
    auto panel = DrawNode::create();
    panel->setAnchorPoint(Vec2(0, 0));
    panel->setContentSize(Size(128, 32));
    panel->setPosition(Vec2(0, 0));
    panel->drawSolidRect(Vec2(0, 0), Vec2(128, 32), Color4F(1, 1, 1, 1));
        _widget = ui::Widget::create();
        _widget->setAnchorPoint(Vec2(0, 0));
        _widget->setContentSize(Size(128, 32));
        _widget->setPosition(Vec2(0, 0));
        _widget->setTouchEnabled(true);
            auto title = Label::create(_title, "Arial", 26);
            title->setAnchorPoint(Vec2(0.5, 0.5));
            title->setContentSize(Size(128, 32));
            title->setPosition(Vec2(64, 16));
            title->setTextColor(Color4B(0, 0, 0, 255));
            _widget->addChild(title);
        panel->addChild(_widget);
    this->addChild(panel);
}
