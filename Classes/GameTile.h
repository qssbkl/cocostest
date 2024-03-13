#include "cocos2d.h";
#include "ui/CocosGUI.h";
#include <functional>;

class GameTile : public cocos2d::Node
{
public:
	static GameTile* create(std::function<void(GameTile*)> onPressAction);

	virtual bool init();

	void setUp(int x, int y, float size, cocos2d::Color4F color);
	void fall(int distance);

	int getX() { return _x; };
	int getY() { return _y; };

	CREATE_FUNC(GameTile);
private:
	int _x;
	int _y;
	cocos2d::DrawNode* _rect;
	cocos2d::ui::Widget* _widget;
	std::function<void(GameTile*)> _onPressAction;
	void construct();
	void onTilePressed(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};
