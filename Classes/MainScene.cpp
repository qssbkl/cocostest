#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!LayerColor::initWithColor(Color4B(56, 75, 115, 255)))
    {
        return false;
    }
    auto windowSize = Director::getInstance()->getWinSize();
    _gameSize = Size(windowSize.width - 256, windowSize.height - 256);

    _gameMenu = GameMenu::create([&](int _0, int _1, int _2) { startGame(_0, _1, _2); });
    _gameMenu->setPosition(0, windowSize.height - 48);
    this->addChild(_gameMenu);

    auto gameScreen = Node::create();
    gameScreen->setAnchorPoint(Vec2(0, 0));
    gameScreen->setContentSize(Size(_gameSize.width, _gameSize.height));
    gameScreen->setPosition(128, 128);
        _playField = DrawNode::create();
        _playField->setAnchorPoint(Vec2(0, 0));
        _playField->setContentSize(Size(_gameSize.width, _gameSize.height));
        _playField->setPosition(Vec2(0, 0));
        _playField->drawSolidRect(Vec2(0, 0), Vec2(_gameSize.width, _gameSize.height), Color4F(0.02745, 0.04314, 0.04314, 1));
        gameScreen->addChild(_playField);
    this->addChild(gameScreen);

    _gameoverLabel = Label::create("", "Arial", 32);
    _gameoverLabel->setAnchorPoint(Vec2(0.5, 0.5));
    _gameoverLabel->setContentSize(Size(128, 48));
    _gameoverLabel->setPosition(Vec2(windowSize.width / 2, 64));
    _gameoverLabel->setTextColor(Color4B::RED);
    this->addChild(_gameoverLabel);
    _gameoverLabel->setVisible(false);

    return true;
}

void MainScene::startGame(int width, int height, int colors)
{
    if (!_canClick)
        return;

    restart();

    _width = width;
    _height = height;
    _colorCount = colors;
    _canClick = true;
    _score = 0;
    _gameMenu->setScore(_score);
    setUpPlayField();
    createMap();
    createTiles();
    checkForGameover();
}

void MainScene::setUpPlayField()
{
    auto gameScreenRatio = _gameSize.height / _gameSize.width;
    auto playFieldRatio = static_cast<float>(_height) / _width;
    auto playFieldSize = playFieldRatio < gameScreenRatio
        ? Size(_gameSize.width, _gameSize.width * playFieldRatio)
        : Size(_gameSize.height / playFieldRatio, _gameSize.height);
    auto playFieldPos = playFieldRatio < gameScreenRatio
        ? Vec2(0, (_gameSize.height - playFieldSize.height) / 2)
        : Vec2((_gameSize.width - playFieldSize.width) / 2, 0);
    _playField->setContentSize(playFieldSize);
    _playField->setPosition(playFieldPos);
    _playField->clear();
    _playField->drawSolidRect(Vec2(0, 0), Vec2(playFieldSize.width, playFieldSize.height), Color4F(0.02745, 0.04314, 0.04314, 1));
}

void MainScene::createMap()
{
    _map.clear();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, _colorCount - 1);
    auto length = _width * _height;
    for (int i = 0; i < length; i++)
    {
        _map.push_back(dist(rng));
    }
}

void MainScene::createTiles()
{
    auto tileSize = _playField->getContentSize().width / _width;
    auto length = _width * _height;
    for (int i = 0, x = 0, y = 0; i < length; i++, x++)
    {
        if (x == _width)
        {
            x = 0;
            y++;
        }
        auto tile = getTile();
        tile->setUp(x, y, tileSize, getColorByIndex(_map[i]));
    }
}

void MainScene::onTilePressed(GameTile* tile)
{
    if (!_canClick)
        return;
    getConnectedTiles(tile);
    if (_closed.size() < 3)
        return;
    for (auto t : _closed)
    {
        removeTile(t);
    }
    addScore();
    fallCeiling();
    checkForGameover();
}

void MainScene::getConnectedTiles(GameTile* tile)
{
    auto targetColor = _map[getFlattenIndex(tile->getX(), tile->getY())];
    _open.clear();
    _closed.clear();
    _ceil.clear();
    _open.insert(tile);
    while (!_open.empty())
    {
        auto it = _open.begin();
        tile = *it;
        _open.erase(it);
        auto x = tile->getX();
        auto y = tile->getY();

        checkNeighbour(x + 1, y, targetColor);
        checkNeighbour(x - 1, y, targetColor);
        checkNeighbour(x, y + 1, targetColor, true);
        checkNeighbour(x, y - 1, targetColor);

        _closed.insert(tile);
    }
}

void MainScene::checkNeighbour(int x, int y, int targetColor, bool isTop)
{
    if (!checkBounds(x, y))
        return;
    auto index = getFlattenIndex(x, y);
    auto neighbour = _gameTiles[index];
    if (!neighbour)
        return;
    if (_open.find(neighbour) != _open.end() ||
        _closed.find(neighbour) != _closed.end())
        return;
    auto color = _map[index];
    if (color != targetColor)
    {
        if (isTop)
        {
            _ceil.insert(neighbour);
        }
        return;
    }
    _open.insert(neighbour);
}

void MainScene::addScore()
{
    auto tileCount = _closed.size();
    auto value = (_colorCount - 2) * (tileCount - 2) * 100;
    _score += value;
    _gameMenu->setScore(_score);
}

void MainScene::fallCeiling()
{
    auto maxFallDistance = 0;
    for (auto tile : _ceil)
    {
        auto x = tile->getX();
        auto y = tile->getY();
        auto fallDistance = 0;
        for (int i = 1; i <= y; i++)
        {
            auto index = getFlattenIndex(x, y - i);
            if (_map[index] != -1)
                break;
            fallDistance++;
        }
        if (fallDistance > maxFallDistance)
        {
            maxFallDistance = fallDistance;
        }
        for (int i = y; i < _height; i++)
        {
            auto oldIndex = getFlattenIndex(x, i);
            auto newIndex = getFlattenIndex(x, i - fallDistance);
            auto color = _map[oldIndex];
            if (color == -1)
                break;
            auto ceil = _gameTiles[oldIndex];
            _map[oldIndex] = -1;
            _gameTiles[oldIndex] = nullptr;
            _map[newIndex] = color;
            _gameTiles[newIndex] = ceil;
            ceil->fall(fallDistance);
        }
    }
    _canClick = false;
    auto callback = CallFunc::create([&]() {
        _canClick = true;
    });
    auto action = DelayTime::create(maxFallDistance * 0.25);
    auto sequence = Sequence::create(action, callback, nullptr);
    this->runAction(sequence);
}

void MainScene::checkForGameover()
{
    auto hasConnections = false;
    auto hasTiles = false;
    auto length = _width * _height;
    for (int i = 0, x = 0, y = 0; i < length; i++, x++)
    {
        if (x == _width)
        {
            x = 0;
            y++;
        }
        auto color = _map[i];
        if (color == -1)
            continue;
        hasTiles = true;
        auto matches = 0;
        if (checkNeighbourForGameover(x + 1, y, color))
            matches++;
        if (checkNeighbourForGameover(x - 1, y, color))
            matches++;
        if (checkNeighbourForGameover(x, y + 1, color))
            matches++;
        if (checkNeighbourForGameover(x, y - 1, color))
            matches++;
        if (matches >= 2)
        {
            hasConnections = true;
            break;
        }
    }
    if (!hasConnections)
    {
        if (hasTiles)
        {
            displayLoseLabel();
        }
        else
        {
            displayWinLabel();
        }
    }
}

bool MainScene::checkNeighbourForGameover(int x, int y, int targetColor)
{
    if (!checkBounds(x, y))
        return false;
    auto index = getFlattenIndex(x, y);
    auto color = _map[index];
    return color == targetColor;
}

void MainScene::displayLoseLabel()
{
    _gameoverLabel->setString("Game Over!");
    _gameoverLabel->setTextColor(Color4B::RED);
    _gameoverLabel->setVisible(true);
}

void MainScene::displayWinLabel()
{
    _gameoverLabel->setString("Well Done!");
    _gameoverLabel->setTextColor(Color4B::GREEN);
    _gameoverLabel->setVisible(true);
}

void MainScene::removeTile(GameTile* tile)
{
    tile->setVisible(false);
    _tilePool.push(tile);
    auto index = getFlattenIndex(tile->getX(), tile->getY());
    _map[index] = -1;
    _gameTiles[index] = nullptr;
}

GameTile* MainScene::getTile()
{
    GameTile* tile;
    if (_tilePool.empty())
    {
        tile = GameTile::create([&](GameTile* _0) { onTilePressed(_0); });
        _playField->addChild(tile);
    }
    else
    {
        tile = _tilePool.front();
        _tilePool.pop();
        tile->setVisible(true);
    }
    _gameTiles.push_back(tile);
    return tile;
}

void MainScene::restart()
{
    for (auto tile : _gameTiles)
    {
        if (!tile)
            continue;
        removeTile(tile);
    }
    _gameTiles.clear();
    _gameoverLabel->setVisible(false);
}

cocos2d::Color4F MainScene::getColorByIndex(int index)
{
    return _colors[index];
}

int MainScene::getFlattenIndex(int x, int y)
{
    return x + _width * y;
}

bool MainScene::checkBounds(int x, int y)
{
    return (x >= 0) && (x < _width) &&
           (y >= 0) && (y < _height);
}
