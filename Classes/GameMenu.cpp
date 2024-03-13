#include "GameMenu.h"

USING_NS_CC;

GameMenu* GameMenu::create(std::function<void(int _0, int _1, int _2)> startAction)
{
	auto menu = GameMenu::create();
	menu->_startAction = startAction;
	menu->construct();
	return menu;
}

bool GameMenu::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void GameMenu::construct()
{
    auto windowSize = Director::getInstance()->getWinSize();

    this->setAnchorPoint(Vec2(0, 0));
    auto panel = DrawNode::create();
    panel->setAnchorPoint(Vec2(0, 0));
    panel->setContentSize(Size(windowSize.width, 48));
    panel->setPosition(0, 0);
    panel->drawSolidRect(Vec2(0, 0), Vec2(windowSize.width, 48), Color4F(0.61176, 0.64314, 0.71765, 1));
        _widthInputField = InputField::create("Width:", "width", 3, 64, 16);
        _widthInputField->setPosition(Vec2(16, 8));
        panel->addChild(_widthInputField);
        _heightInputField = InputField::create("Height:", "height", 3, 64, 10);
        _heightInputField->setPosition(Vec2(288, 8));
        panel->addChild(_heightInputField);
        _colorsInputField = InputField::create("Colors:", "colors", 2, 8, 3);
        _colorsInputField->setPosition(Vec2(560, 8));
        panel->addChild(_colorsInputField);
        _scoreOutput = OutputField::create("Score:");
        _scoreOutput->setPosition(Vec2(832, 8));
        panel->addChild(_scoreOutput);
        auto startButton = Button::create("Start");
        startButton->setPosition(Vec2(windowSize.width - 144, 8));
        startButton->getWidget()->addTouchEventListener(CC_CALLBACK_2(GameMenu::onStartButtonPressed, this));
        panel->addChild(startButton);
    this->addChild(panel);
}

void GameMenu::onStartButtonPressed(Ref* pSender, ui::Widget::TouchEventType type)
{
    if (type != ui::Widget::TouchEventType::BEGAN)
        return;

	auto width = _widthInputField->getValue();
	auto height = _heightInputField->getValue();
	auto colors = _colorsInputField->getValue();
	_startAction(width, height, colors);
}

void GameMenu::setScore(int value)
{
    _scoreOutput->setValue(value);
}
