#include "GameTile.h"

USING_NS_CC;

GameTile* GameTile::create(std::function<void(GameTile*)> onPressAction)
{
	auto tile = GameTile::create();
	tile->_onPressAction = onPressAction;
	tile->construct();
	return tile;
}

bool GameTile::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void GameTile::construct()
{
	this->setAnchorPoint(Vec2(0, 0));
	_rect = DrawNode::create();
	_rect->setAnchorPoint(Vec2(0, 0));
	_rect->setContentSize(Size(0, 0));
	_rect->setPosition(Vec2(0, 0));
		_widget = ui::Widget::create();
		_widget->setAnchorPoint(Vec2(0, 0));
		_widget->setContentSize(Size(0, 0));
		_widget->setPosition(Vec2(0, 0));
		_widget->setTouchEnabled(true);
		_widget->addTouchEventListener(CC_CALLBACK_2(GameTile::onTilePressed, this));
		_rect->addChild(_widget);
	this->addChild(_rect);
}

void GameTile::setUp(int x, int y, float size, Color4F color)
{
	_x = x;
	_y = y;
	this->setContentSize(Size(size, size));
	_rect->setContentSize(Size(size, size));
	_widget->setContentSize(Size(size, size));
	this->setPosition(Vec2(_x * size, _y * size));
	_rect->clear();
	_rect->drawSolidRect(Vec2(0, 0), Vec2(size, size), color);
}

void GameTile::fall(int distance)
{
	_y -= distance;
	auto worldDistance = getContentSize().width * distance;
	auto action = MoveBy::create(0.25 * distance, Vec2(0, -worldDistance));
	this->runAction(action);
}

void GameTile::onTilePressed(Ref* pSender, ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::BEGAN)
		return;

	_onPressAction(this);
}
